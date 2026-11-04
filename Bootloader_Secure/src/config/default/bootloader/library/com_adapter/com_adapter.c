/**
 * © 2025 Microchip Technology Inc. and its subsidiaries.
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms
 * applicable to your use of third party software (including open
 * source software) that may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,
 * MERCHANTABILITY, AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL,
 * PUNITIVE, INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE
 * OF ANY KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED,
 * EVEN IF MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE
 * DAMAGES ARE FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW,
 * MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY RELATED TO
 * THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY, THAT YOU
 * HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * @file    com_adapter.c
 * @brief   This is the implementation file for the communication adapter layer using UART.
 * @ingroup com_adapter
 */

/**@misradeviation{@advisory, 8.9} This cannot be followed since the value of the variables
 * must be saved until the next time the function is called. Declaring at block scope will
 * make managing the variable reset more difficult.
 */
/**@misradeviation{@advisory, 15.4} This will not be followed because it would require removing
 * code that is helpful for debugging making the code more difficult to work with.
 */

#include "com_adapter.h"
#include "peripheral/sercom/usart/plib_sercom1_usart.h"
#include <stdbool.h>
#include "../../../definitions.h"
/**
 * @ingroup com_adapter
 * @def START_OF_PACKET_BYTE
 * @brief Special character for identifying the start of the frame.
 */
#define START_OF_PACKET_BYTE    (0x56U)
/**
 * @ingroup com_adapter
 * @def END_OF_PACKET_BYTE
 * @brief Special character for identifying the end of the frame.
 */
#define END_OF_PACKET_BYTE      (0x9EU)
/**
 * @ingroup com_adapter
 * @def ESCAPE_BYTE
 * @brief Special character for identifying an escaped byte in the command data.
 *
 * @note For additional information about the framing operations used for Universal Asynchronous Receiver/Transmitter (UART), refer to the
 * MDFU protocol documentation for version 1.0.0.
 */
#define ESCAPE_BYTE             (0xCCU)

typedef struct
{
    uint8_t EscapeCharacter;
    uint8_t StartOfPacketCharacter;
    uint8_t EndOfPacketCharacter;
} ftp_special_characters_t;

static ftp_special_characters_t ftpSpecialCharacters = {
    .EscapeCharacter = ESCAPE_BYTE,
    .StartOfPacketCharacter = START_OF_PACKET_BYTE,
    .EndOfPacketCharacter = END_OF_PACKET_BYTE
};

/**
 * @ingroup com_adapter
 * @def MaxBufferLength
 * @brief Maximum reception size for each block of data.
 * @note This is set by the initialization function.
 */
static uint16_t MaxBufferLength = 0U;
/**
 * @ingroup com_adapter
 * @def isReceiveWindowOpen
 * @brief Static flag used to identify is the start of packet has been processed and bytes are being read into the buffer.
 */
static bool isReceiveWindowOpen = false;
/**
 * @ingroup com_adapter
 * @def isReceiveWindowOpen
 * @brief Static flag used to identify if the escape character has been seen and special action must be taken
 * on the next received byte.
 */
static bool isEscapedByte = false;
/**
 * @ingroup com_adapter
 * @brief Abstracted UART write function for sending a single byte.
 *
 * @param [in] data - Data byte to be transferred over UART
 * @return @ref COM_PASS - Data transfer did not encounter any errors \n
 * @return @ref COM_FAIL - Data transfer encounter an errors. The peripheral returned an error after attempting to transmit data \n
 */
static com_adapter_result_t DataSend(uint8_t data);

/**
 * @ingroup com_adapter
 * @brief Calculate the frame check on the given data buffer
 *
 * @note For additional information on the frame check used by the FTP refer to the MDFU protocol document version 1.0.0.
 *
 * @param [in] ftpData Data buffer to be used for the frame check calculation
 * @param [in] bufferLength Length of data objects in the buffer
 * @return Calculated frame check
 */
static uint16_t FrameCheckCalculate(uint8_t * ftpData, uint16_t bufferLength);

static uint16_t FrameCheckCalculate(uint8_t * ftpData, uint16_t bufferLength)
{
    uint16_t numBytesChecksummed = 0U;
    uint16_t checksum = 0U;

    while (numBytesChecksummed < (bufferLength))
    {
        if ((numBytesChecksummed % 2U) == 0U)
        {
            checksum += ((uint16_t) (ftpData[numBytesChecksummed]));
        }
        else
        {
            checksum += (uint16_t)(((uint16_t) (ftpData[numBytesChecksummed])) << 8U);
        }
        numBytesChecksummed++;
    }

    return ~checksum;
}

static com_adapter_result_t DataSend(uint8_t data)
{
    com_adapter_result_t status = COM_PASS;

    while (!SERCOM1_USART_TransmitterIsReady())
    {
        // Wait for TX to be ready
    };
    // Call to send the next byte
    SERCOM1_USART_WriteByte((int)data);
    if (0U != SERCOM1_USART_ErrorGet())
    {
        status = COM_FAIL;
    }

    while (!SERCOM1_USART_TransmitComplete())
    {
        // Block until last byte shifts out
    }

    return status;
}

com_adapter_result_t COM_FrameTransfer(uint8_t *receiveBufferPtr, uint16_t *receiveIndexPtr)
{
    uint8_t nextByte = 0U;
    com_adapter_result_t processResult = COM_FAIL;

    if ((NULL == receiveBufferPtr) || (NULL == receiveIndexPtr))
    {
        processResult = COM_INVALID_ARG;
    }
    else
    {
        if (true == SERCOM1_USART_ReceiverIsReady())
        {
            nextByte = (uint8_t)SERCOM1_USART_ReadByte();

            processResult = (0U == SERCOM1_USART_ErrorGet()) ? COM_PASS : COM_FAIL;
        }
    }

    if (COM_PASS == processResult)
    {
    	if (nextByte == ftpSpecialCharacters.StartOfPacketCharacter)
        {
            // Open the buffer window
            isReceiveWindowOpen = true;
            isEscapedByte = false;
            // Reset the buffer index
            *receiveIndexPtr = 0U;

            processResult = COM_BUSY;
        }
        else if (isReceiveWindowOpen)
        {
        	if (nextByte == ftpSpecialCharacters.EndOfPacketCharacter)
            {
                // Close the buffer window
                isReceiveWindowOpen = false;

                // Calculate the frame check here
                uint16_t fcs = FrameCheckCalculate(receiveBufferPtr, *receiveIndexPtr - FRAME_CHECK_SIZE);

                // Read FCS from the transfer buffer
                uint8_t *startOfWord = &receiveBufferPtr[*receiveIndexPtr - FRAME_CHECK_SIZE];
                uint16_t frameCheckSequence = 0x0000U;
                uint8_t * workPtr = startOfWord;
                uint8_t lowByte = *workPtr;
                workPtr++;
                uint8_t highByte = *workPtr;
                uint16_t shiftedHigh = (uint16_t)((uint16_t)highByte << 8U);
                frameCheckSequence = (uint16_t)(shiftedHigh | (uint16_t)lowByte);

                if (fcs == frameCheckSequence)
                {
                    // Set the status to execute the command
                    processResult = COM_PASS;
                }
                else
                {
                    // Set the status to execute the command
                    processResult = COM_TRANSPORT_FAILURE;
                }
            }
            else if (nextByte == ftpSpecialCharacters.EscapeCharacter)
            {
                isEscapedByte = true;
                processResult = COM_BUSY;
            }
            else
            {
                // If escape was flagged perform the bit flip to correct the byte
                if (isEscapedByte)
                {
                    nextByte = ~nextByte;
                    isEscapedByte = false;
                }

                // Route the byte into the transfer buffer
                if (*receiveIndexPtr < MaxBufferLength)
                {
                    receiveBufferPtr[*receiveIndexPtr] = nextByte;
                    (*receiveIndexPtr)++;
                    processResult = COM_BUSY;
                }
                else
                {
                    // Close the buffer window
                    isReceiveWindowOpen = false;
                    processResult = COM_BUFFER_ERROR;
                }
            }
        }
        else
        {
            processResult = COM_FAIL;
        }
    }
    else
    {
        processResult = COM_FAIL;
    }

    return processResult;
}

com_adapter_result_t COM_FrameSet(uint8_t *responseBufferPtr, uint16_t responseLength)
{
    com_adapter_result_t processResult = COM_FAIL;

    if ((NULL == responseBufferPtr) || (0U == responseLength))
    {
        processResult = COM_INVALID_ARG;
    }
    else
    {
        // Integrity Check
        uint16_t frameCheck = FrameCheckCalculate(responseBufferPtr, responseLength);

        processResult = DataSend(ftpSpecialCharacters.StartOfPacketCharacter);

        if (COM_PASS == processResult)
        {
            uint8_t nextByte;
            uint16_t sentByteCount = 0x00U;

            while (sentByteCount < (responseLength + FRAME_CHECK_SIZE))
            {
                if (sentByteCount == responseLength)
                {
                    // send the low byte first
                    nextByte = (uint8_t) (frameCheck & 0x00FFU);
                }
                else if (sentByteCount == (responseLength + 1U))
                {
                    // send the high byte first
                    nextByte = (uint8_t) (frameCheck >> 8);
                }
                else
                {
                    nextByte = responseBufferPtr[sentByteCount];
                }

                if ((START_OF_PACKET_BYTE == nextByte) || (END_OF_PACKET_BYTE == nextByte) || (ESCAPE_BYTE == nextByte))
                {
                    processResult = DataSend(ftpSpecialCharacters.EscapeCharacter);
                    if (COM_PASS != processResult)
                    {
                        // fail and stop sending
                        break;
                    }
                    nextByte = ~nextByte;
                }

                processResult = DataSend(nextByte);
                if (COM_PASS != processResult)
                {
                    // fail and stop sending
                    break;
                }

                sentByteCount++;
            }

            processResult = DataSend(ftpSpecialCharacters.EndOfPacketCharacter);
        }
        else
        {
            // fail with no other actions
        }
    }

    return processResult;
}

com_adapter_result_t COM_Initialize(uint16_t maximumBufferLength)
{
    com_adapter_result_t result = COM_FAIL;
    if (0U != maximumBufferLength)
    {
        MaxBufferLength = maximumBufferLength;
        isReceiveWindowOpen = false;
        isEscapedByte = false;
        
        result = COM_PASS;
    }
    else
    {
        result = COM_INVALID_ARG;
    }

    return result;
}