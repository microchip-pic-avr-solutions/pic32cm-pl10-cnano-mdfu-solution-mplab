/**
 * � 2026 Microchip Technology Inc. and its subsidiaries.
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
 * @brief   This is the implementation file for the communication adapter layer using SPI.
 * @ingroup com_adapter_spi
 */

#include "com_adapter.h"
#include "peripheral/sercom/spi_slave/plib_sercom0_spi_slave.h"
#include "peripheral/sercom/spi_slave/plib_sercom_spi_slave_common.h"
#include "../../../definitions.h"
#include <stdbool.h>

/**
 * @ingroup com_adapter_spi
 * @def LENGTH_FIELD_SIZE
 * Holds the size of the length data field.
 */
#define LENGTH_FIELD_SIZE (2U)

/**
 * @ingroup com_adapter_spi
 * @def SOP_SEQUENCE_LENGTH
 * Holds the number of bytes that need to be held in the data buffer for each start of frame sequence.
 */
#define SOP_SEQUENCE_LENGTH (4U)

/**
 * @ingroup com_adapter_spi
 * @def MAX_RESPONSE_DATA_FIELD
 * Holds the maximum size of a response.
 */
#define MAX_RESPONSE_DATA_FIELD (25U)

/**
 * @ingroup com_adapter_spi
 * @def RESPONSE_PACKET_SIZE
 * Holds the size of the response packet.
 */
#define RESPONSE_PACKET_SIZE (SOP_SEQUENCE_LENGTH + MAX_RESPONSE_DATA_FIELD + FRAME_CHECK_SIZE)

/**
 * @ingroup com_adapter_spi
 * @def LENGTH_PACKET_SIZE
 * Holds the size of the length packet.
 */
#define LENGTH_PACKET_SIZE (SOP_SEQUENCE_LENGTH + LENGTH_FIELD_SIZE + FRAME_CHECK_SIZE)

/* cppcheck-suppress misra-c2012-2.3 */
typedef enum
{ /* cppcheck-suppress misra-c2012-2.4 */
    HOST_READ_CODE = 0x55U,
    HOST_WRITE_CODE = 0x11U,
} host_command_code_t;

typedef enum
{
    NO_ACTION = 0x00,
    SEND_LENGTH,
    SEND_RESPONSE,
    READ_COMMAND
} com_adapter_state_t;

static uint8_t sendBuffer[LENGTH_PACKET_SIZE + RESPONSE_PACKET_SIZE];
static uint16_t maxBufferLength = 0U;
static uint16_t calculatedFrameCheck = 0x0000U;
static uint16_t sendLength = 0U;
static com_adapter_state_t comState = NO_ACTION;

static uint16_t FrameCheckCalculate(const uint8_t * ftpData, uint16_t bufferLength);

static uint16_t FrameCheckCalculate(const uint8_t * ftpData, uint16_t bufferLength)
{
    uint16_t numBytesChecksummed = 0x0000U;
    uint16_t checksum = 0x0000U;

    while (numBytesChecksummed < (bufferLength))
    {
        if ((numBytesChecksummed % 2U) == 0U)
        {
            checksum += ((uint16_t) (ftpData[numBytesChecksummed]));
        }
        else
        {
            checksum += (uint16_t)(((uint16_t)ftpData[numBytesChecksummed]) << 8);
        }
        numBytesChecksummed++;
    }

    return (uint16_t)(~checksum);
}

bool SERCOM0_Open(void)
{
    bool enabled = false;
    SERCOM0_REGS->SPI.SERCOM_CTRLA |= SERCOM_SPI_CTRLA_ENABLE_Msk;
     // Wait for synchronization
    while (SERCOM0_REGS->SPI.SERCOM_SYNCBUSY != 0U)
    {
        // Do nothing
    }
    enabled = true;

    return enabled;
}

// Read a byte from SPI (blocking until RX is ready)
uint8_t SERCOM0_ByteRead(void)
{
    while (((uint32_t)SERCOM0_REGS->SPI.SERCOM_INTFLAG & (uint32_t)SERCOM_SPI_INTFLAG_RXC_Msk) == 0U)
    {
        // Wait for RX ready
    }
    return (uint8_t)SERCOM0_REGS->SPI.SERCOM_DATA;
}

// Write a byte to SPI (blocking until TX data register is empty)
void SERCOM0_ByteWrite(uint8_t data)
{
    while (((uint32_t)SERCOM0_REGS->SPI.SERCOM_INTFLAG & (uint32_t)SERCOM_SPI_INTFLAG_DRE_Msk) == 0U)
    {
        // Wait for TX register empty
    }
    SERCOM0_REGS->SPI.SERCOM_DATA = data;
}

// Returns 1 if TX is busy (data register not empty), 0 if ready
uint8_t SERCOM0_IsTxReady(void)
{
    return (((uint32_t)SERCOM0_REGS->SPI.SERCOM_INTFLAG & (uint32_t)SERCOM_SPI_INTFLAG_DRE_Msk) == 0U) ? 1U : 0U;
}

// Returns 1 if RX has data available, 0 if not
uint8_t SERCOM0_IsRxReady(void)
{
    return (((uint32_t)SERCOM0_REGS->SPI.SERCOM_INTFLAG & (uint32_t)SERCOM_SPI_INTFLAG_RXC_Msk) != 0U) ? 1U : 0U;
}

com_adapter_result_t COM_FrameTransfer(uint8_t *receiveBufferPtr, uint16_t * receiveIndexPtr)
{
    uint8_t nextByte;
    uint16_t readByteCount = 0U;
    /* cppcheck-suppress misra-c2012-8.9 */
    static uint16_t bytesSent = 0U;

    com_adapter_result_t processResult = COM_FAIL;

    if ((receiveBufferPtr == NULL) || (receiveIndexPtr == NULL))
    {
        processResult = COM_INVALID_ARG;
    }
    else
    {
        processResult = COM_BUSY;

        // Waiting for chip select to transition from low to high
        /* cppcheck-suppress premium-misra-c-2025-17.3 */
        while (CHIP_SELECT_Get() == 0U)
        {
            // Waiting
        }
        // Waiting for chip select to transition from high to low
        /* cppcheck-suppress premium-misra-c-2025-17.3 */
        while (CHIP_SELECT_Get() != 0U)
        {
            // Waiting
        }

        // Loading the first byte
        SERCOM0_ByteWrite(sendBuffer[bytesSent]);
        bytesSent += 1U;

        // Waiting for the initial read to occur
        while (false == (bool)SERCOM0_IsRxReady())
        {
            // Waiting
        }

        nextByte = (uint8_t)SERCOM0_ByteRead();

        // Sets the state of the read command if needed
        if (nextByte == (uint8_t) HOST_WRITE_CODE)
        {
            comState = READ_COMMAND;
        }

        switch (comState)
        {
        case SEND_LENGTH:
            /* cppcheck-suppress premium-misra-c-2025-17.3 */
            while (0U == CHIP_SELECT_Get())
            {
                // Performs an exchange on the length packet bytes
                if (true == (bool)SERCOM0_IsTxReady())
                {
                    if (bytesSent < LENGTH_PACKET_SIZE)
                    {
                        SERCOM0_ByteWrite(sendBuffer[bytesSent]);
                        bytesSent += 1U;
                    }
                }
            }

            // Sets the current state to expect a response send on the next cycle
            comState = SEND_RESPONSE;
            break;
        case SEND_RESPONSE:
            /* cppcheck-suppress premium-misra-c-2025-17.3 */
            while (0U == CHIP_SELECT_Get())
            {
                // Performs an exchange on the response packet bytes
                if (true == (bool)SERCOM0_IsTxReady())
                {
                    if (bytesSent != sendLength)
                    {
                        (void)SERCOM0_ByteWrite(sendBuffer[bytesSent]);
                        bytesSent += 1U;
                    }
                }
            }

            // Reset the rx buffer
            while (true == (bool)SERCOM0_IsRxReady())
            {
                (void) SERCOM0_ByteRead();
            }

            // Sets the state back to NO_ACTION to wait for next command
            comState = NO_ACTION;
            bytesSent = 0U;

            // Sets the completed status to notify the FTP code.
            processResult = COM_SEND_COMPLETE;
            break;
        case READ_COMMAND:
            /* cppcheck-suppress premium-misra-c-2025-17.3 */
            while (0U == CHIP_SELECT_Get())
            {
                // Puts a byte into the receive buffer if there is space left
                if (true == (bool)SERCOM0_IsRxReady())
                {
                    nextByte = SERCOM0_ByteRead();

                    if (readByteCount < maxBufferLength)
                    {
                        receiveBufferPtr[readByteCount] = nextByte;
                        readByteCount += 1U;
                    }
                    else
                    {
                        processResult = COM_BUFFER_ERROR;
                        comState = NO_ACTION;
                    }
                }
            }

            // Performs one additional read if needed due to CS de-assertion occurring too quickly
            if (true == (bool)SERCOM0_IsRxReady())
            {
                nextByte = SERCOM0_ByteRead();

                if (readByteCount < maxBufferLength)
                {
                    receiveBufferPtr[readByteCount] = nextByte;
                    readByteCount += 1U;
                }
                else
                {
                    processResult = COM_BUFFER_ERROR;
                    comState = NO_ACTION;
                }
            }

            // Reset the rx buffer
            while (true == (bool)SERCOM0_IsRxReady())
            {
                (void) SERCOM0_ByteRead();
            }

            // Resets the sending logic
            sendLength = 0U;
            bytesSent = 0U;
            break;
        default:
            //Do Nothing
            break;
        }

        // Sets the new read index for the FTP code.
        *receiveIndexPtr = readByteCount;

        // Validates a received command
        if (READ_COMMAND == comState)
        {
            calculatedFrameCheck = FrameCheckCalculate(&(receiveBufferPtr[0U]), (readByteCount - FRAME_CHECK_SIZE));

            // Reads FCS from the receive buffer
            uint8_t *startOfWord = &receiveBufferPtr[readByteCount - FRAME_CHECK_SIZE];
            uint16_t frameCheckSequence = 0x0000U;

            const uint8_t * workPtr = startOfWord;
            uint8_t lowByte = *workPtr;
            workPtr++;
            uint8_t highByte = *workPtr;
            frameCheckSequence = (uint16_t)((uint16_t)((uint16_t)highByte << 8) | lowByte);
            if (calculatedFrameCheck == frameCheckSequence)
            {
                // Set the status to execute the command
                processResult = COM_PASS;
            }
            else
            {
                // Set the error status to craft a retry response
                processResult = COM_TRANSPORT_FAILURE;
            }
            comState = NO_ACTION;
        }
    }

    return processResult;
}

com_adapter_result_t COM_FrameSet(const uint8_t *responseBufferPtr, uint16_t responseLength)
{
    com_adapter_result_t status = COM_FAIL;

    // SOP for length and response
    static const uint8_t responseStartSequence[SOP_SEQUENCE_LENGTH] = {0x00U, (uint8_t)'R', (uint8_t)'S', (uint8_t)'P'};
    static const uint8_t lengthStartSequence[SOP_SEQUENCE_LENGTH] = {0x00U, (uint8_t)'L', (uint8_t)'E', (uint8_t)'N'};

    if ((responseBufferPtr == NULL) || (responseLength == 0U))
    {
        status = COM_INVALID_ARG;
    }
    else
    {
        // Initializes the transfer logic
        sendLength = 0U;

        // Calculates the data size that the host is required to read
        uint16_t hostReadLength = responseLength + FRAME_CHECK_SIZE;
        uint8_t hostReadLengthBytes[2];
        hostReadLengthBytes[0] = (uint8_t)(hostReadLength & 0x00FFU);
        hostReadLengthBytes[1] = (uint8_t)((uint8_t)(hostReadLength >> 8) & 0xFFU);        
        
        calculatedFrameCheck = FrameCheckCalculate(hostReadLengthBytes, 2U);
        
        // Loads up the buffer with the length packet data
        for (uint8_t i = 0U; i < SOP_SEQUENCE_LENGTH; i++)
        {
            sendBuffer[sendLength] = lengthStartSequence[i];
            sendLength += 1U;
        }
        sendBuffer[sendLength] = hostReadLengthBytes[0];
        sendLength += 1U;
        sendBuffer[sendLength] = hostReadLengthBytes[1];
        sendLength += 1U;
        sendBuffer[sendLength] = (uint8_t) calculatedFrameCheck & 0x00FFU;
        sendLength += 1U;
        sendBuffer[sendLength] = (uint8_t) (calculatedFrameCheck >> 8);
        sendLength += 1U;

        // Loads up the buffer with the response packet data
        for (uint8_t i = 0U; i < SOP_SEQUENCE_LENGTH; i++)
        {
            sendBuffer[sendLength] = responseStartSequence[i];
            sendLength += 1U;
        }
        // Copies the response data into the COM static buffer starting at the length response offset
        for (uint8_t i = 0U; i < responseLength; i++)
        {
            sendBuffer[sendLength] = responseBufferPtr[i];
            sendLength += 1U;
        }

        // Calculates and sets the FCS of the response data
        calculatedFrameCheck = FrameCheckCalculate(&responseBufferPtr[0], responseLength);
        sendBuffer[sendLength] = (uint8_t) calculatedFrameCheck & 0x00FFU;
        sendLength += 1U;
        sendBuffer[sendLength] = (uint8_t) (calculatedFrameCheck >> 8);
        sendLength += 1U;

        status = COM_PASS;
        comState = SEND_LENGTH;
    }
    return status;
}

com_adapter_result_t COM_Initialize(uint16_t maximumBufferLength)
{
    com_adapter_result_t result = COM_FAIL;
    comState = NO_ACTION;

    if (maximumBufferLength != 0U)
    {
        // Enables SPI
        bool isValid = SERCOM0_Open();

        if (true == isValid)
        {
            // Sets the static max size of the communication logic
            maxBufferLength = maximumBufferLength;

            result = COM_PASS;
        }
        else
        {
            maxBufferLength = 0U;

            result = COM_FAIL;
        }
    }
    else
    {
        result = COM_INVALID_ARG;
    }

    return result;
}