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
 * @file        bl_ftp.c
 * @ingroup     mdfu_client_ftp
 * @brief       This file is the implementation file of the file transfer protocol layer.
 */

/** @misradeviation{@advisory, 2.4} 
* This rule will not be followed for the code clarity.
*/

/** @misradeviation{@advisory, 2.3}
* This rule will not be followed for the code clarity.
*/

/** @misradeviation{@advisory, 4.6}
* This rule will not be followed as the API demands a constant value.
*/

/** @misradeviation{@advisory, 4.9}
* This rule will not be followed as the definition of the RESET() macro is device architecture dependent.
*/

/** @misradeviation{@required, 10.3}
* Essential type of operand does not affect functionality of the switch case.
*/

/** @misradeviation{@required, 10.4}
* This rule will not be followed as the definition of the delay macro is out of the scope for this module.
*/

#include "bl_ftp.h"
#include "../bl_core.h"
#include "../../com_adapter/com_adapter.h"
#include "../bl_app_verify.h"
#include "../../../../peripheral/systick/plib_systick.h"

/**
 * @ingroup mdfu_client_ftp
 * @def COMMAND_DATA_SIZE
 * @brief Length of the command data field in bytes.
 */
#define COMMAND_DATA_SIZE       (1U)
/**
 * @ingroup mdfu_client_ftp
 * @def SEQUENCE_DATA_SIZE
 * @brief Length of the sequence data field in bytes.
 */
#define SEQUENCE_DATA_SIZE      (1U)
/**
 * @ingroup mdfu_client_ftp
 * @def MAX_RESPONSE_SIZE
 * @brief Length of the largest possible response in bytes.
 */
#define MAX_RESPONSE_SIZE       (25U)
/**
 * @ingroup mdfu_client_ftp
 * @def TLV_HEADER_SIZE
 * @brief Length of a TLV object header in bytes.
 */
#define TLV_HEADER_SIZE         (2U)
/**
 * @ingroup mdfu_client_ftp
 * @def MAX_TRANSFER_SIZE
 * @brief Length of the largest possible data transfer in bytes.
 */
#define MAX_TRANSFER_SIZE       (BL_MAX_BUFFER_SIZE + SEQUENCE_DATA_SIZE + COMMAND_DATA_SIZE + COM_FRAME_BYTE_COUNT)
/**
 * @ingroup mdfu_client_ftp
 * @def MIN_TRANSFER_SIZE
 * @brief Length of the smallest possible transfer in bytes.
 */
#define MIN_TRANSFER_SIZE       (2U)
/**
 * @ingroup mdfu_client_ftp
 * @def PACKET_BUFFER_COUNT
 * @brief Number of buffers supported for reception.
 */
#define PACKET_BUFFER_COUNT     (1U)
/**
 * @ingroup mdfu_client_ftp
 * @def RETRY_TRANSFER_bm
 * @brief Mask of the Retry bit.
 */
#define RETRY_TRANSFER_bm       (0x40U)
/**
 * @ingroup mdfu_client_ftp
 * @def SYNC_TRANSFER_bm
 * @brief Mask of the Sync bit.
 */
#define SYNC_TRANSFER_bm        (0x80U)
/**
 * @ingroup mdfu_client_ftp
 * @def SEQUENCE_NUMBER_bm
 * @brief Mask of the sequence number field.
 */
#define SEQUENCE_NUMBER_bm      (0x3FU)
/**
 * @ingroup mdfu_client_ftp
 * @def MAX_SEQUENCE_VALUE
 * @brief Maximum value of the sequence field.
 */
#define MAX_SEQUENCE_VALUE      (31U)
/**
 * @ingroup mdfu_client_ftp
 * @def FTP_BYTE_INDEX
 * @brief Index of the status or command byte in the receive buffer.
 * @note This index is valid for both the command byte of the receive buffer and the status byte of the response buffer.
 */
#define FTP_BYTE_INDEX          (1U)
/**
 * @ingroup mdfu_client_ftp
 * @def SEQUENCE_BYTE_INDEX
 * @brief Index of the sequence byte in the receive buffer.
 */
#define SEQUENCE_BYTE_INDEX     (0U)
/**
 * @ingroup mdfu_client_ftp
 * @def FILE_DATA_INDEX
 * @brief Index of the start of the file transfer data in the receive buffer.
 */
#define FILE_DATA_INDEX         (COMMAND_DATA_SIZE + SEQUENCE_DATA_SIZE)

/**
 * @ingroup mdfu_client_ftp
 * @enum ftp_command_t
 * @brief Enumeration of the file transfer command codes defined by the MDFU protocol.
 */
typedef enum
{
    FTP_GET_CLIENT_INFO = 0x01U,
    FTP_START_TRANSFER = 0x02U,
    FTP_WRITE_CHUNK = 0x03U,
    FTP_GET_IMAGE_STATE = 0x04U,
    FTP_END_TRANSFER = 0x05U
} ftp_command_t;

/**
 * @ingroup mdfu_client_ftp
 * @enum ftp_response_status_t
 * @brief Enumeration of the file transfer status codes defined by the MDFU protocol.
 */
typedef enum
{
    FTP_COMMAND_SUCCESS = 0x01U,
    FTP_COMMAND_NOT_SUPPORTED = 0x02U,
    FTP_COMMAND_NOT_AUTHORIZED = 0x03U,
    FTP_COMMAND_NOT_EXECUTED = 0x04U,
    FTP_ABORT_TRANSFER = 0x05U
} ftp_response_status_t;

/**
 * @ingroup mdfu_client_ftp
 * @enum ftp_abort_code_t
 * @brief Enumeration of the response codes used to communicate the client abort cause defined by the MDFU protocol.
 */
typedef enum
{
    FTP_GENERIC_ERROR = 0x00U,
    FTP_INVALID_FILE_ERROR = 0x01U,
    FTP_INVALID_DEVICE_ID_ERROR = 0x02U,
    FTP_ADDRESS_ERROR = 0x03U,
    FTP_ERASE_ERROR = 0x04U,
    FTP_WRITE_ERROR = 0x05U,
    FTP_READ_ERROR = 0x06U,
    FTP_APP_VERSION_ERROR = 0x07U,
} ftp_abort_code_t;

/**
 * @ingroup mdfu_client_ftp
 * @enum ftp_transport_failure_code_t
 * @brief Enumeration of the response codes used to communicate the client transport failure cause defined by the MDFU protocol.
 */
typedef enum
{
    FTP_INTEGRITY_CHECK_ERROR = 0x00U,
    FTP_COMMAND_TOO_LONG_ERROR = 0x01U,
    FTP_COMMAND_TOO_SHORT_ERROR = 0x02U,
    FTP_INVALID_SEQUENCE_NUMBER_ERROR = 0x03U,
} ftp_transport_failure_code_t;

/**
 * @ingroup mdfu_client_ftp
 * @enum ftp_image_state_t
 * @brief Enumeration of the get image state response codes.
 */
typedef enum
{
    FTP_IMAGE_VALID = 0x01U,
    FTP_IMAGE_INVALID = 0x02U
} ftp_image_state_t;

/**
 * @ingroup mdfu_client_ftp
 * @enum tlv_type_code_t
 * @brief Enumeration of the discovery data type codes.
 */
typedef enum
{
    FTP_PROTOCOL_VERSION = 0x01U,
    FTP_TRANSFER_PARAMETERS = 0x02U,
    FTP_TIMEOUT_INFO = 0x03U,
    FTP_MIN_INTER_MESSAGE_DELAY_INFO = 0x04U,
} tlv_type_code_t;

/**
 * @ingroup mdfu_client_ftp
 * @struct ftp_parser_helper_t
 * @brief A structure to help manage the reception of the commands, sending responses, and frame validation logic of the FTP Handler.
 *
 * This structure is used to manage indexes and track the various sequence numbers involved in FTP
 * command/response logic, maintain the flags indicating whether a response or resend is required
 * as well as maintain any additional data flags needed.
 */
typedef struct
{
    uint8_t lastSequenceNumber; /**< The last sequence number processed */
    uint8_t currentSequenceNumber; /**< The current sequence number being processed */
    uint8_t nextSequenceNumber; /**< The next expected sequence number */
    bool responseRequired; /**< Flag indicating if a response is required */
    bool resendRequired; /**< Flag indicating if a resend is required */    
} ftp_parser_helper_t;

/**
 * @ingroup mdfu_client_ftp
 * @struct ftp_tlv_t
 * @brief A structure to help manage the Type-Length-Value (TLV) data payloads used during the Get Client Info stage.
 *
 * This structure is used to manage the definition of the TLV data in the
 * Get Client Info response. This type is also used as an input to a function that helps
 * append new data to the response buffer in a more dynamic way.
 */
typedef struct
{
    uint8_t dataType; /**< The type of data held in the data buffer */
    uint8_t dataLength; /**< The length of data held in the data buffer */
    uint8_t * valueBuffer; /**< The data buffer to be transferred to the host */
} ftp_tlv_t;

/**
 * @ingroup mdfu_client_ftp
 * @brief Buffer for receiving FTP data.
 *
 * This buffer is used to store incoming FTP data packets.
 * The size of the buffer is defined by MAX_TRANSFER_SIZE which is based on the
 * bootloader's write size.
 */
static uint8_t FTP_RECEIVE_BUFFER[MAX_TRANSFER_SIZE];

/**
 * @ingroup mdfu_client_ftp
 * @brief Buffer for storing FTP response data.
 *
 * This buffer holds the data that will be sent as a response frame
 * to each FTP command. The size of the buffer is defined by MAX_RESPONSE_SIZE.
. */
static uint8_t FTP_RESPONSE_BUFFER[MAX_RESPONSE_SIZE];

/**
 * @ingroup mdfu_client_ftp
 * @brief Buffer for retrying FTP responses.
 *
 * This buffer is used to store FTP response data that needs
 * to be resent in case of transmission failures. The size of
 * the buffer is defined by MAX_RESPONSE_SIZE.
 */
static uint8_t FTP_RETRY_BUFFER[MAX_RESPONSE_SIZE];

static bool resetPending = false;
static bool isComBusy = false;

/**
 * @ingroup mdfu_client_ftp
 * @brief Structure manages the FTP parser data.
 */
static ftp_parser_helper_t ftpHelper = {
    .lastSequenceNumber = 0U,
    .currentSequenceNumber = 0U,
    .nextSequenceNumber = 1U,
    .resendRequired = false,
    .responseRequired = false,
};
static uint16_t ftpReceiveCount = 0U;
static uint16_t ftpResponseLength = 0U;

/**
 * @ingroup mdfu_client_ftp
 * @brief Checks and performs a reset when required.
 *
 * This function checks the static reset flag and performs the reset operation.
 * This controls the reset logic after the update has completed.
 *
 * @param None
 * @return None
 */
static void DeviceResetCheck(void);
/**
 * @ingroup mdfu_client_ftp
 * @brief Resets parser data use for command reception.
 *
 * This function resets all flags, buffers, and counters used when receiving FTP
 * commands.
 *
 * @param None
 * @return None
 */
static void ParserDataReset(void);
/**
 * @ingroup mdfu_client_ftp
 * @brief Validates the sequence number of the incoming command.
 *
 * This function checks the validity of the sequence number based on past operations
 * and the next expected number.
 *
 * @param None
 * @return Returns true if the sequence number is valid, false otherwise
 */
static bool SequenceNumberValidate(void);
/**
 * @ingroup mdfu_client_ftp
 * @brief Sets the Get Client Info data in the response buffer.
 *
 * This function defines and sets the response data to the Get Client Info command.
 * The Get Client Info command data payload used in this function is defined by the MDFU protocol.
 *
 * @param None
 * @return None
 */
static void ClientInfoResponseSet(void);

/**
 * @ingroup mdfu_client_ftp
 * @brief Processes and executes the FTP command data received by the host.
 *
 * This function processes the FTP receive buffer and calls the required operational layer or performs the steps needed to execute the FTP command.
 * The Get Client Info Command data payload used in this function is defined by the MDFU protocol.
 *
 * @param None
 * @return @ref BL_PASS - FTP process cycle finished successfully
 * @return @ref BL_ERROR_UNKNOWN_COMMAND - FTP process failed due to an unknown command code or unknown file data block type
 * @return @ref BL_ERROR_VERIFICATION_FAIL - FTP process failed due to a data verification failed. Could be returned when an image failure occurs or when a meta-data validation fails
 * @return @ref BL_ERROR_ADDRESS_OUT_OF_RANGE - FTP process failed due to an address error
 * @return @ref BL_ERROR_COMMAND_PROCESSING - FTP process failed due to a general memory process error
 */
static bl_result_t OperationalBlockExecute(void);

/**
 * @ingroup mdfu_client_ftp
 * @brief Sets the response in the FTP process frame.
 *
 * This function configures the response for a given FTP buffer by
 * setting the response payload, status, sequence byte, and response length.
 *
 * @param [in,out] buffer - Pointer to the FTP response buffer where the frame must be set
 * @param [in] responsePayload - Pointer to the response payload data
 * @param [in] responseStatus - Status of the FTP response
 * @param [in] sequenceByte - Sequence byte for the response
 * @param [in] responsePayloadLength - Length of the response payload
 * @return None
 */
static void ResponseSet(
                        uint8_t * buffer,
                        uint8_t * responsePayload,
                        ftp_response_status_t responseStatus,
                        uint8_t sequenceByte,
                        uint16_t responsePayloadLength
                        );
/**
 * @ingroup mdfu_client_ftp
 * @brief Appends a TLV (Type-Length-Value) structure to a data buffer.
 *
 * This function appends a given TLV structure to the specified data buffer.
 * It updates the buffer with the TLV data, ensuring that the data is correctly
 * formatted and aligned within the response buffer.
 *
 * @param [in,out] dataBufferStart - Pointer to the start of the data buffer where the TLV will be appended
 * @param [in] tlvData - Pointer to the TLV structure containing the data to append
 * @return The number of bytes appended to the buffer
 *
 * @note Ensure that the data buffer has sufficient space to accommodate the TLV data.
 */
static uint8_t TLVAppend(uint8_t * dataBufferStart, ftp_tlv_t * tlvData);

/**
 * @ingroup mdfu_client_ftp
 * @brief Converts the given result codes into MDFU protocol defined data values.
 *
 * This function converts the bootloader core result codes into codes that are defined by the MDFU protocol.
 *
 * @param [in] targetStatus - Bootloader result code that needs to be mapped to one of the defined protocol codes
 * @return @ref FTP_INVALID_FILE_ERROR - The bootloader failed during file verification, either during the metadata block validation or a failed image verification
 * @return @ref FTP_ADDRESS_ERROR - The bootloader processed a block with an invalid address
 * @return @ref FTP_WRITE_ERROR - The bootloader encountered an error while trying to process the data. Likely be due to NVM errors
 * @return @ref FTP_GENERIC_ERROR - The bootloader code received has not been mapped to a specific FTP abort code
 */
static ftp_abort_code_t AbortCodeGet(bl_result_t targetStatus);

bl_result_t FTP_Task(void)
{
    if (!isComBusy)
    {
        DeviceResetCheck();
    }
    bl_result_t processResult = BL_FAIL;
    ftp_transport_failure_code_t transportStatusResult = FTP_INTEGRITY_CHECK_ERROR;
    com_adapter_result_t comResult = COM_FAIL;

    // Call the command to load the buffer up with the current receive count
    comResult = COM_FrameTransfer((uint8_t *) & FTP_RECEIVE_BUFFER, &ftpReceiveCount);
    /* cppcheck-suppress misra-c2012-10.1; false Positive */
    if ((com_adapter_result_t)COM_BUFFER_ERROR == comResult)
    {
        processResult = BL_ERROR_BUFFER_OVERLOAD;
        ftpHelper.resendRequired = true;
        transportStatusResult = FTP_COMMAND_TOO_LONG_ERROR;
        ResponseSet((uint8_t *) & FTP_RETRY_BUFFER, (uint8_t *) & transportStatusResult, FTP_COMMAND_NOT_EXECUTED, ftpHelper.nextSequenceNumber ^ RETRY_TRANSFER_bm, 1U);
        ParserDataReset();
    }
    /* cppcheck-suppress misra-c2012-10.1; false Positive */
    else if ((com_adapter_result_t)COM_PASS == comResult)
    {

        if (ftpReceiveCount < MIN_TRANSFER_SIZE)
        {
            processResult = BL_ERROR_BUFFER_UNDERLOAD;
            transportStatusResult = FTP_COMMAND_TOO_SHORT_ERROR;
            ftpHelper.resendRequired = true;
            ResponseSet((uint8_t *) & FTP_RETRY_BUFFER, (uint8_t *) & transportStatusResult, FTP_COMMAND_NOT_EXECUTED, ftpHelper.nextSequenceNumber ^ RETRY_TRANSFER_bm, 1U);
        }
        else if (SequenceNumberValidate())
        {
            // Call execution to handle the rest of the command processes
            processResult = OperationalBlockExecute();
            ftpHelper.responseRequired = true;
        }
        else
        {
            processResult = BL_ERROR_FRAME_VALIDATION_FAIL;
        }
        ParserDataReset();
    }
    /* cppcheck-suppress misra-c2012-10.1; false Positive */
    else if ((com_adapter_result_t)COM_TRANSPORT_FAILURE == comResult)
    {
        processResult = BL_ERROR_FRAME_VALIDATION_FAIL;
        ftpHelper.resendRequired = true;
        ResponseSet((uint8_t *) & FTP_RETRY_BUFFER, (uint8_t *) & transportStatusResult, FTP_COMMAND_NOT_EXECUTED, ftpHelper.nextSequenceNumber ^ RETRY_TRANSFER_bm, 1U);
    }
    /* cppcheck-suppress misra-c2012-10.1; false Positive */
    else if ((com_adapter_result_t)COM_BUSY == comResult)
    {
        // Still Loading
        processResult = BL_BUSY;
    }
#ifdef MULTI_STAGE_RESPONSE
    /* cppcheck-suppress misra-c2012-10.1; false Positive */
    else if ((com_adapter_result_t)COM_SEND_COMPLETE == comResult)
    {
        // flip the busy flag to allow resets
        isComBusy = false;
        processResult = BL_BUSY;
    }
#endif
    else
    {
        processResult = BL_ERROR_COMMUNICATION_FAIL;
    }

    if (ftpHelper.resendRequired)
    {
        comResult = COM_FrameSet((uint8_t *) & FTP_RETRY_BUFFER, ftpResponseLength);
        /* cppcheck-suppress misra-c2012-10.1; false Positive */
        if (COM_PASS != comResult)
        {
            processResult = BL_ERROR_COMMUNICATION_FAIL;
        }
        ftpHelper.resendRequired = false;
    }
    else if (ftpHelper.responseRequired)
    {
        comResult = COM_FrameSet((uint8_t *) & FTP_RESPONSE_BUFFER, ftpResponseLength);
        /* cppcheck-suppress misra-c2012-10.1; false Positive */
        if (COM_PASS != comResult)
        {
            processResult = BL_ERROR_COMMUNICATION_FAIL;
        }
        ftpHelper.responseRequired = false;
    }
    else
    {
        // Do nothing
    }

    return processResult;
}

static bool SequenceNumberValidate(void)
{
    bool isValidSequenceNum = false;

    // Get the sequence Number info
    ftpHelper.currentSequenceNumber = FTP_RECEIVE_BUFFER[SEQUENCE_BYTE_INDEX] & SEQUENCE_NUMBER_bm;
    bool syncRequested = ((FTP_RECEIVE_BUFFER[SEQUENCE_BYTE_INDEX] & SYNC_TRANSFER_bm) != 0U) ? true : false;

    // Sequence Sync Check
    if (syncRequested)
    {
        // If the sync field is check synchronize the buffer and execute the command
        isValidSequenceNum = true;
        ftpHelper.lastSequenceNumber = ftpHelper.currentSequenceNumber;
        ftpHelper.nextSequenceNumber = (ftpHelper.currentSequenceNumber + 1U) & MAX_SEQUENCE_VALUE;
    }
        // Else if the packet is next packet expected, execute the packet
    else if (ftpHelper.currentSequenceNumber == ftpHelper.nextSequenceNumber)
    {
        isValidSequenceNum = true;
        ftpHelper.lastSequenceNumber = ftpHelper.currentSequenceNumber;
        ftpHelper.nextSequenceNumber = (ftpHelper.currentSequenceNumber + 1U) & MAX_SEQUENCE_VALUE;
    }
    else if (ftpHelper.currentSequenceNumber == ftpHelper.lastSequenceNumber)
    {
        // Don't execute the command but resend the response that is already in the buffer
        isValidSequenceNum = false;
        ftpHelper.responseRequired = true;
    }
        // Else send a resend request for the next packet sequence number
    else
    {
        isValidSequenceNum = false;
        ftpHelper.resendRequired = true;
        ftp_transport_failure_code_t transportStatusResult = FTP_INVALID_SEQUENCE_NUMBER_ERROR;
        ResponseSet((uint8_t *) & FTP_RETRY_BUFFER, (uint8_t *) & transportStatusResult, FTP_COMMAND_NOT_EXECUTED, ftpHelper.nextSequenceNumber ^ RETRY_TRANSFER_bm, 1U);
    }
    return isValidSequenceNum;
}

static bl_result_t OperationalBlockExecute(void)
{
    bl_result_t processResult = BL_BUSY;

    switch (FTP_RECEIVE_BUFFER[FTP_BYTE_INDEX])
    {
    case FTP_GET_CLIENT_INFO:
    {
        ClientInfoResponseSet();
        processResult = BL_PASS;
        break;
    }
    case FTP_GET_IMAGE_STATE:
    {
        processResult = BL_ImageVerify();
        ftp_image_state_t isImageValid = (processResult == (bl_result_t)BL_PASS) ? FTP_IMAGE_VALID : FTP_IMAGE_INVALID;
        ResponseSet((uint8_t *) & FTP_RESPONSE_BUFFER, (uint8_t *) & isImageValid, FTP_COMMAND_SUCCESS, ftpHelper.currentSequenceNumber, 1U);
        break;
    }    
    case FTP_START_TRANSFER:
    {
        processResult = BL_PASS;
        (void) BL_Initialize();
        ResponseSet((uint8_t *) & FTP_RESPONSE_BUFFER, NULL, FTP_COMMAND_SUCCESS, ftpHelper.currentSequenceNumber, 0U);
        break;
    }
    case FTP_WRITE_CHUNK:
    {
        processResult = BL_BootCommandProcess(&FTP_RECEIVE_BUFFER[FILE_DATA_INDEX], ftpReceiveCount - COMMAND_DATA_SIZE - SEQUENCE_DATA_SIZE - FRAME_CHECK_SIZE);
        /* cppcheck-suppress misra-c2012-10.1; false Positive */
        if ((bl_result_t)BL_PASS == processResult)
        {
            ResponseSet((uint8_t *) & FTP_RESPONSE_BUFFER, NULL, FTP_COMMAND_SUCCESS, ftpHelper.currentSequenceNumber, 0U);
        }
        else
        {
            ftp_abort_code_t abortCode = AbortCodeGet(processResult);
            ResponseSet((uint8_t *) & FTP_RESPONSE_BUFFER, (uint8_t *) & abortCode, FTP_ABORT_TRANSFER, ftpHelper.currentSequenceNumber, 1U);
        }
        break;
    }
    case FTP_END_TRANSFER:
    {
        ResponseSet((uint8_t *) & FTP_RESPONSE_BUFFER, NULL, FTP_COMMAND_SUCCESS, ftpHelper.currentSequenceNumber, 0U);
        resetPending = true;
#ifdef MULTI_STAGE_RESPONSE
        // Prevent any reset from occurring until the communication layer is working.
        isComBusy = true;
#endif
        processResult = BL_PASS;
        break;
    }
    default:
    {
        processResult = BL_ERROR_UNKNOWN_COMMAND;
        ResponseSet((uint8_t *) & FTP_RESPONSE_BUFFER, NULL, FTP_COMMAND_NOT_SUPPORTED, ftpHelper.currentSequenceNumber, 0U);
        break;
    }
    }

    return processResult;
}

static ftp_abort_code_t AbortCodeGet(bl_result_t targetStatus)
{
    ftp_abort_code_t abortCode = FTP_GENERIC_ERROR;
    switch (targetStatus)
    {
    case BL_ERROR_VERIFICATION_FAIL:
        abortCode = FTP_INVALID_FILE_ERROR;
        break;
    case BL_ERROR_ADDRESS_OUT_OF_RANGE:
        abortCode = FTP_ADDRESS_ERROR;
        break;
    case BL_ERROR_COMMAND_PROCESSING:
        abortCode = FTP_WRITE_ERROR;
        break;
    case BL_ERROR_UNKNOWN_COMMAND:
        abortCode = FTP_INVALID_FILE_ERROR;
        break;
    default:
        // Do Nothing - Unknown code
        break;
    }
    return abortCode;
}

static void ParserDataReset(void)
{
    ftpReceiveCount = 0x00U;
    // Clear the transfer buffer
    const void* result = memset(&FTP_RECEIVE_BUFFER, 0x00, MAX_TRANSFER_SIZE);
    (void)result; // Explicitly cast to void to indicate the return value is intentionally unused
}

static void DeviceResetCheck(void)
{
    if (true == resetPending)
    {   
        // Device reset delay of 2500 ms
        SYSTICK_TimerStart();
        SYSTICK_DelayMs(1200U);
        SYSTICK_TimerStop();

    NVIC_SystemReset();
    }
}

static void ResponseSet(uint8_t * buffer, uint8_t * responsePayload, ftp_response_status_t responseStatus, uint8_t sequenceByte, uint16_t responsePayloadLength)
{
    // Calculate the length of the response
    ftpResponseLength = (responsePayloadLength + SEQUENCE_DATA_SIZE + COMMAND_DATA_SIZE);
    // Update The Sequence Value
    buffer[SEQUENCE_BYTE_INDEX] = sequenceByte;
    // Status
    buffer[FTP_BYTE_INDEX] = (uint8_t)responseStatus;
    if(responsePayload != NULL){
        // Data Bytes
        (void)memcpy(&buffer[FILE_DATA_INDEX], responsePayload, (size_t)responsePayloadLength);
    } else{
        // Do Nothing
    }
}

static uint8_t TLVAppend(uint8_t * dataBufferStart, ftp_tlv_t * tlvData)
{
    // Type & Length
    (void)memcpy(dataBufferStart, (uint8_t*)tlvData, (size_t)2U);
    // Data Bytes
    (void)memcpy(&dataBufferStart[TLV_HEADER_SIZE], tlvData->valueBuffer, (size_t)tlvData->dataLength);
    return tlvData->dataLength + TLV_HEADER_SIZE;
}

static void ClientInfoResponseSet(void)
{
    uint32_t minimumInterMessageDelayData = (uint32_t) 0x0016E360U; // 1,500,000 nanoseconds => 1.5 milliseconds
    uint8_t numberOfTLVDataValues = 4U;

    struct ftp_discovery_data_t
    {
        uint16_t maxPayloadSize;
        uint8_t numberOfPacketBuffers;
    } discoveryData = {
        .numberOfPacketBuffers = (uint8_t)PACKET_BUFFER_COUNT,
        .maxPayloadSize = (uint16_t)BL_MAX_BUFFER_SIZE
    };

    /**
     * This solution is utilizing the FTP UART implementation defined in the MDFU protocol version 1.0.0
     */
    struct ftp_version_data_t
    {
        uint8_t major;
        uint8_t minor;
        uint8_t patch;
    } ftpVersionData = {
        .major = 0x01U,
        .minor = 0x02U,
        .patch = 0x00U,
    };

    struct ftp_command_timeout_info_t
    {
        uint8_t commandCode;
        uint8_t timeoutValueLow;
        uint8_t timeoutValueHigh;
    } generalCommandTimeoutData = {
        .commandCode = 0x00U, // General Command Timeout Code: 0x64 -> 100 dec -> 10 Seconds
        .timeoutValueLow = 0x64U,
        .timeoutValueHigh = 0x00U,
    };

    ftp_tlv_t ftpVersionTLVData = {
        .dataType = (uint8_t)FTP_PROTOCOL_VERSION,
        .dataLength = 0x03U,
        .valueBuffer = (uint8_t *) & ftpVersionData
    };

    ftp_tlv_t ftpTransferParametersTLVData = {
        .dataType = (uint8_t)FTP_TRANSFER_PARAMETERS,
        .dataLength = 0x03U,
        .valueBuffer = (uint8_t *) & discoveryData
    };

    ftp_tlv_t ftpTimeoutTLVData = {
        .dataType = (uint8_t)FTP_TIMEOUT_INFO,
        .dataLength = 0x03U,
        .valueBuffer = (uint8_t *) & generalCommandTimeoutData
    };

    ftp_tlv_t ftpMinInterMessageDelayTLVData = {
        .dataType = (uint8_t)FTP_MIN_INTER_MESSAGE_DELAY_INFO,
        .dataLength = 0x04U,
        .valueBuffer = (uint8_t *) & minimumInterMessageDelayData
    };
    // Calculate and set the response length
    ftpResponseLength = (
            (uint16_t)ftpVersionTLVData.dataLength +
            (uint16_t)ftpTransferParametersTLVData.dataLength +
            (uint16_t)ftpTimeoutTLVData.dataLength +
            (uint16_t)ftpMinInterMessageDelayTLVData.dataLength +
            (uint16_t)SEQUENCE_DATA_SIZE +
            (uint16_t)COMMAND_DATA_SIZE +
            ((uint16_t)TLV_HEADER_SIZE * (uint16_t)numberOfTLVDataValues)
            );

    // Update The Sequence Value
    FTP_RESPONSE_BUFFER[SEQUENCE_BYTE_INDEX] = ftpHelper.currentSequenceNumber;

    // Update Status
    FTP_RESPONSE_BUFFER[FTP_BYTE_INDEX] = (uint8_t)FTP_COMMAND_SUCCESS;

    uint16_t fileDataOffset = (uint16_t)(FILE_DATA_INDEX);

    // Push each TLV Byte Stream to the buffer
    fileDataOffset += TLVAppend(&(FTP_RESPONSE_BUFFER[fileDataOffset]), &ftpVersionTLVData);
    fileDataOffset += TLVAppend(&(FTP_RESPONSE_BUFFER[fileDataOffset]), &ftpTransferParametersTLVData);
    fileDataOffset += TLVAppend(&(FTP_RESPONSE_BUFFER[fileDataOffset]), &ftpTimeoutTLVData);
    // Drop the length of the last TLV append command because it is not needed
    (void) TLVAppend(&(FTP_RESPONSE_BUFFER[fileDataOffset]), &ftpMinInterMessageDelayTLVData);
}

bl_result_t FTP_Initialize(void)
{
    // Tell com layer the max size of the buffer it can use
    com_adapter_result_t comInitStatus = COM_Initialize((uint16_t)(MAX_TRANSFER_SIZE));
    isComBusy = false;
    resetPending = false;
    /* cppcheck-suppress misra-c2012-10.1; false Positive */
    return ((comInitStatus == (com_adapter_result_t)COM_PASS) ? (bl_result_t)BL_PASS : (bl_result_t)BL_FAIL);
}