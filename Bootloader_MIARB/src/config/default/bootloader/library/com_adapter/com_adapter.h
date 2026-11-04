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
 * @file    com_adapter.h
 * @brief   Contains prototypes and other data types for communication adapter layer.
 *
 * @defgroup com_adapter Communication Adapter
 * @brief This layer implements the custom transport layer that is defined by the MDFU protocol.
 */
/**@misradeviation{@advisory, 2.5} This is a false positive.
 */

#ifndef COM_ADAPTER_H
/* cppcheck-suppress misra-c2012-2.5 */
#define COM_ADAPTER_H

#include <stdint.h>

/* cppcheck-suppress misra-c2012-2.5 */
/**
 * @ingroup com_adapter
 * @def FRAME_CHECK_SIZE
 * @brief Length of the frame check field in bytes.
 */
#define FRAME_CHECK_SIZE        (2U)

/* cppcheck-suppress misra-c2012-2.5 */
/**
 * @ingroup com_adapter
 * @def FRAME_CHECK_SIZE
 * @brief Length of the frame bytes needed.
 *
 * This is the length of bytes that must be defined in the FTP handler buffer in order
 * to properly implement the current transport layer.
 */
#define COM_FRAME_BYTE_COUNT (FRAME_CHECK_SIZE)

/**
 * @ingroup com_adapter
 * @enum com_adapter_result_t
 * @brief Contains codes for the return values of the bootloader communication adapter layer APIs.
 * @var com_adapter_result_t: COM_PASS
 * 0xE7U - com_adapter operation succeeded
 * @var com_adapter_result_t: COM_FAIL
 * 0xC3U - com_adapter operation failed
 * @var com_adapter_result_t: COM_INVALID_ARG
 * 0x96U - com_adapter operation has an invalid argument
 * @var com_adapter_result_t: COM_BUFFER_ERROR
 * 0x69U - com_adapter operation has encountered an overflow
 * @var com_adapter_result_t: COM_BUSY
 * 0x18U - com_adapter operation is not finished yet
 * @var com_adapter_result_t: COM_TRANSPORT_FAILURE
 * 0x3CU - com_adapter operation has encountered a transport error
 * @var com_adapter_result_t: COM_SEND_COMPLETE
 * 0x7EU - com_adapter sending operation is finished
 */
typedef enum
{
    COM_PASS = 0xE7U,
    COM_FAIL = 0xC3U,
    COM_INVALID_ARG = 0x96U,
    COM_BUFFER_ERROR = 0x69U,
    COM_BUSY = 0x18U,
    COM_TRANSPORT_FAILURE = 0x3CU,
    COM_SEND_COMPLETE = 0x7EU,
} com_adapter_result_t;

/**
 * @ingroup com_adapter
 * @brief Receives or sends byte over SERCOM.
 *
 * When receiving this function will push data bytes into the buffer provided until a complete frame is received.
 * When sending this function uses the static send buffer defined in communication adapter file to send out bytes
 * until it is complete.
 *
 * @note For UART, this function does not send data out because it is asynchronous, but for other host driven
 * protocols this function controls the transfer in both directions.
 *
 * @param [in,out] receiveBufferPtr - Pointer to the buffer provided to SERCOM
 * @param [in,out] receiveIndexPtr - Pointer to the number of bytes successfully received by SERCOM
 * @return @ref COM_PASS - SERCOM has received a complete frame and is ready for further processing \n
 * @return @ref COM_BUSY - SERCOM still loading the buffer \n
 * @return @ref COM_BUFFER_ERROR - SERCOM received too many or encountered a data error \n
 * @return @ref COM_FAIL - An error occurred in the SERCOM \n
 */
com_adapter_result_t COM_FrameTransfer(uint8_t *receiveBufferPtr, uint16_t *receiveIndexPtr);

/**
 * @ingroup com_adapter
 * @brief Copies and formats bytes from the given buffer into the static send buffer using the defined framing format.
 *
 * @note For UART, this function will simply send the bytes out of the peripheral because the communication layer does
 * not need to wait for the host to initiate any transfer. Doing this makes it so we do not need to define a static
 * buffer in the communication code.
 *
 * @param [in] responseBufferPtr - Pointer to the buffer that needs to be sent
 * @param [in] responseLength - Length of the response that needs to be sent
 * @return @ref COM_PASS - Buffer was transferred without error \n
 * @return @ref COM_FAIL - An error occurred in the SERCOM while transferring the buffer \n
 */
com_adapter_result_t COM_FrameSet(uint8_t *responseBufferPtr, uint16_t responseLength);

/**
 * @ingroup com_adapter
 * @brief Performs initialization actions for the communication peripheral and adapter code.
 *
 * @note This function takes the maximum buffer length of the FTP handler so that it
 * knows when to signal an overflow to the FTP code.
 *
 * @param [in] maximumBufferLength - Maximum length that the COM adapter is allowed to read
 * @return @ref COM_PASS - Specified arguments were valid and initialization was successful \n
 * @return @ref COM_INVALID_ARG - Specified arguments were invalid \n
 * @return @ref COM_FAIL - An error occurred in the SERCOM initialization \n
 */
com_adapter_result_t COM_Initialize(uint16_t maximumBufferLength);

#endif //COM_ADAPTER_H