/**
 * © 2026 Microchip Technology Inc. and its subsidiaries.
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
 * @brief   This file contains the implementation of the communication adapter layer using Inter-Integrated Circuit (I2C).
 * @ingroup com_adapter_i2c
 */

#include "com_adapter.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "../../../peripheral/sercom/i2c_slave/plib_sercom_i2c_slave_common.h"
#include "../../../peripheral/sercom/i2c_slave/plib_sercom0_i2c_slave.h"

/**
 * @ingroup com_adapter_i2c
 * @def LENGTH_PREFIX_SIZE
 * Contains the size of the length prefix field.
 */
#define LENGTH_PREFIX_SIZE      (1U)

/**
 * @ingroup com_adapter_i2c
 * @def RESPONSE_PREFIX_SIZE
 * Contains the size of the response prefix field.
 */
#define RESPONSE_PREFIX_SIZE    (1U)

/**
 * @ingroup com_adapter_i2c
 * @def LENGTH_FIELD_SIZE
 * Contains the size of the length data field.
 */
#define LENGTH_FIELD_SIZE (2U)

/**
 * @ingroup com_adapter_i2c
 * @def MAX_RESPONSE_DATA_FIELD
 * Contains the maximum size of a response.
 */
#define MAX_RESPONSE_DATA_FIELD (25U)

/**
 * @ingroup com_adapter_i2c
 * @def RESPONSE_OFFSET
 * Contains the offset of the response data buffer where actual client response starts after the length, checksum and prefix fields.
 */
#define RESPONSE_OFFSET (uint16_t)(LENGTH_PREFIX_SIZE + LENGTH_FIELD_SIZE + FRAME_CHECK_SIZE + RESPONSE_PREFIX_SIZE)

/**
 * @ingroup com_adapter_i2c
 * @enum com_transfer_state_t
 * @brief Contains codes for the return values for the transfer state of the bootloader communication adapter layer.
 * @var com_transfer_state_t: NOTHING_TO_SEND
 * 0U - com_adapter has nothing to send
 * @var com_transfer_state_t: SENDING_LENGTH
 * 1U - com_adapter is ready to send the response length
 * @var com_transfer_state_t: SENDING_RESPONSE
 * 2U - com_adapter is ready to send the response data
 */
typedef enum {
    NOTHING_TO_SEND  = 0U, 
    SENDING_LENGTH   = 1U,
    SENDING_RESPONSE = 2U,
} com_transfer_state_t;

static volatile com_transfer_state_t comResponseTransferState = NOTHING_TO_SEND;
static volatile bool isCommandReadyToProcess = false;
static volatile bool areTooManyBytesInCommand = false;

static volatile uint16_t maxBufferLength = 0; 
static volatile uint16_t comResponseBufferIndex = 0U;
static uint8_t comResponseBuffer[MAX_RESPONSE_DATA_FIELD + RESPONSE_OFFSET];
static uint8_t *comReceiveBuffer = NULL;
static uint16_t *comReceiveBufferIndex = NULL;  
static volatile com_adapter_result_t comStatus;

static bool SERCOM_EventHandler(SERCOM_I2C_SLAVE_TRANSFER_EVENT event, uintptr_t contextHandle);

com_adapter_result_t COM_Initialize(uint16_t maximumBufferLength)
{
    com_adapter_result_t result = COM_FAIL;

    if (0U != maximumBufferLength)
    {
        maxBufferLength = maximumBufferLength;
        SERCOM0_I2C_CallbackRegister(&SERCOM_EventHandler, 0U);
        result = COM_PASS;
    }
    else
    {
        result = COM_INVALID_ARG;
    }

    return result;
}

static bool SERCOM_EventHandler(SERCOM_I2C_SLAVE_TRANSFER_EVENT event, uintptr_t contextHandle)
{
    (void)contextHandle;
    bool result = false;
    uint8_t nextByte = 0U;
    SERCOM_I2C_SLAVE_ERROR errorState = SERCOM_I2C_SLAVE_INTFLAG_PREC;
    static volatile SERCOM_I2C_SLAVE_TRANSFER_DIR transferDirection;
    static volatile bool wasTransactionAcknowledged;    
    
    switch(event)
    {
    case SERCOM_I2C_SLAVE_TRANSFER_EVENT_ADDR_MATCH:
        
        transferDirection = SERCOM0_I2C_TransferDirGet(); 
        
        // NAK all incoming transactions if the com_adapter is busy processing a previous command
        if (false == isCommandReadyToProcess) 
        {
            if (SERCOM_I2C_SLAVE_TRANSFER_DIR_WRITE == transferDirection) 
            {
                result = true;
                wasTransactionAcknowledged = true;
                *comReceiveBufferIndex = 0x00U;
                areTooManyBytesInCommand = false;
            }
            else
            {
                if (NOTHING_TO_SEND == comResponseTransferState) 
                {
                    result = true;
                    wasTransactionAcknowledged = false; 
                }
                else 
                { 
                    result = true;
                    wasTransactionAcknowledged = true;
                }
            }
        }
        else
        {
            result = false;
            wasTransactionAcknowledged = false;
        }  
        break;

    case SERCOM_I2C_SLAVE_TRANSFER_EVENT_RX_READY:

        nextByte = SERCOM0_I2C_ReadByte();
        result = true; 
 
        if (!isCommandReadyToProcess) 
        {
            // Add byte to the buffer if there is space in the buffer
            if (*comReceiveBufferIndex < maxBufferLength)
            {
                comReceiveBuffer[*comReceiveBufferIndex] = nextByte;
                (*comReceiveBufferIndex)++;   
            }
            else
            { 
                areTooManyBytesInCommand = true;  
            }
        }
        break;

    case SERCOM_I2C_SLAVE_TRANSFER_EVENT_TX_READY:
        {
            result = true; 
            uint8_t data_to_write = comResponseBuffer[comResponseBufferIndex];
            comResponseBufferIndex = comResponseBufferIndex+1U;
            SERCOM0_I2C_WriteByte(data_to_write);
            break;
        }

    case SERCOM_I2C_SLAVE_TRANSFER_EVENT_STOP_BIT_RECEIVED:
        if(wasTransactionAcknowledged) 
        {
            // Set the com response state to nothing if the transfer direction is host write
            if (SERCOM_I2C_SLAVE_TRANSFER_DIR_WRITE == transferDirection)
            {              
                isCommandReadyToProcess = true;                
                comResponseTransferState = NOTHING_TO_SEND;
            }
            else 
            { 
                if (SENDING_LENGTH == comResponseTransferState)
                {
                    comResponseTransferState = SENDING_RESPONSE;
                }
                else if (SENDING_RESPONSE == comResponseTransferState)
                {
                    comResponseTransferState = NOTHING_TO_SEND; 
                    comStatus = COM_SEND_COMPLETE;
                }
                else
                {
                    //do nothing
                }
            } 
        }
        else
        {
            // do nothing
        }
        break;

    case SERCOM_I2C_SLAVE_TRANSFER_EVENT_ERROR:
        errorState = SERCOM0_I2C_ErrorGet();
        if(errorState>0U)
        {
            comStatus = COM_FAIL;
        }
        else
        {
            //do nothing
        }
        break;
    default:
        // Default case
        break;
    }
    return result;
}

static uint16_t FrameChecksumCalculate(uint8_t * ftpData,uint16_t bufferLength)
{
    uint16_t numBytesChecksummed = 0x0000U;
    uint16_t checksum = 0x0000U;

    while (numBytesChecksummed < (bufferLength))
    {
        if ((numBytesChecksummed % 2U) == 0U)
        {
            checksum += ((uint16_t)(ftpData[numBytesChecksummed]));
        }
        else
        {
            checksum += (uint16_t)(((uint16_t)(ftpData[numBytesChecksummed])) << 8);
        }
        numBytesChecksummed++;
    }

    return (uint16_t )(~checksum);
}

com_adapter_result_t COM_FrameTransfer(uint8_t *receiveBufferPtr,uint16_t *receiveIndexPtr)
{
    com_adapter_result_t result = COM_FAIL;
    comReceiveBuffer = receiveBufferPtr;
    comReceiveBufferIndex = receiveIndexPtr;

    if ((NULL == receiveBufferPtr) || (NULL == receiveIndexPtr))
    {
        result = COM_INVALID_ARG;
    }
    else
    {
        if (isCommandReadyToProcess == true)
        {
            // Set the status to buffer error when the received data length exceeds the max buffer size
            if (areTooManyBytesInCommand) 
            { 
                areTooManyBytesInCommand = false;
                result = COM_BUFFER_ERROR;
            }
            else 
            {

                // Calculate the frame check sequence on the received packet 
                uint16_t calcuatedFrameChecksum = FrameChecksumCalculate(receiveBufferPtr,*receiveIndexPtr - FRAME_CHECK_SIZE); 

                // Extract the last two bytes from the packet
                uint8_t *startOfWord = &receiveBufferPtr[*receiveIndexPtr - FRAME_CHECK_SIZE];
                uint16_t frameCheckSequence = 0x0000U;

                uint8_t *workPtr = startOfWord;
                uint8_t lowByte = *workPtr;
                workPtr++;
                uint8_t highByte = *workPtr;
                frameCheckSequence = (uint16_t)((uint16_t)((uint16_t)highByte << 8) | lowByte);

                // Check if calculated checksum and received checksum are equal
                if (calcuatedFrameChecksum == frameCheckSequence)
                {
                    result = COM_PASS;
                }
                else
                {
                    // Set the status to transport failure if checksum mismatch occurs
                    result = COM_TRANSPORT_FAILURE;
                }
            } 
        } 
        else
        {
            result = comStatus;
        }
    }

    return result;
}

com_adapter_result_t COM_FrameSet(uint8_t *responseBufferPtr, uint16_t responseLength)
{
    com_adapter_result_t result = COM_FAIL;

    uint16_t sendingLength = responseLength + FRAME_CHECK_SIZE;
    uint16_t sendingLengthChecksum;
    uint16_t dataChecksum;

    if ((NULL == responseBufferPtr) || (0U == responseLength))
    {
        result = COM_INVALID_ARG;
    }
    else
    {
        sendingLengthChecksum = FrameChecksumCalculate((uint8_t *) & sendingLength, 2U);
        dataChecksum = FrameChecksumCalculate(&(responseBufferPtr[0]),responseLength);
        
        // Copy the length prefix
        comResponseBuffer[0] = (uint8_t)'L';

        // Copy sending length into the response buffer
        comResponseBuffer[1] = (uint8_t)sendingLength & 0x00FFU;

        // Copy the checksum on sending length into the response buffer
        comResponseBuffer[2] = (uint8_t)(sendingLength >> 8);

        // Copy the data into the response buffer
        comResponseBuffer[3] = (uint8_t)sendingLengthChecksum & 0x00FFU;

        // Copy the checksum on the data into the response buffer
        comResponseBuffer[4] = (uint8_t)(sendingLengthChecksum >> 8);

        // Copy the response prefix
        comResponseBuffer[5] = (uint8_t)'R';
        
        // Copy the response into the COM static buffer and set length
        uint16_t limit = (uint16_t)responseLength + (uint16_t)RESPONSE_OFFSET;
        for (uint16_t i = RESPONSE_OFFSET; i < limit; i++)
        {
            comResponseBuffer[i] = responseBufferPtr[i - RESPONSE_OFFSET];
        }
        
        comResponseBuffer[responseLength + RESPONSE_OFFSET] = (uint8_t)dataChecksum & 0x00FFU;
        
        uint16_t highByte = (uint16_t)((uint32_t)responseLength + (uint32_t)RESPONSE_OFFSET + 1U);
        
        comResponseBuffer[highByte] = (uint8_t)(dataChecksum >> 8);
        
        comResponseBufferIndex = 0U;
        result = COM_PASS;
    }
    // Set the state to sending length when the comResponseBuffer is ready
    comResponseTransferState = SENDING_LENGTH;
    isCommandReadyToProcess = false;
    
    return result;
}
