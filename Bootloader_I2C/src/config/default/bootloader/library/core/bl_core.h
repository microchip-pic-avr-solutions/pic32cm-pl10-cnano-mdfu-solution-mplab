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
 * @file        bl_core.h
 * @brief       Contains API prototypes to perform bootloader operations.
 *
 * @defgroup    mdfu_client_32bit 32-bit Microchip Device Firmware Update (MDFU) Client Library
 * @brief       Core firmware updated APIs for supporting device firmware updates
 *              using an MDFU ecosystem and MDFU protocol.
 */

#ifndef BL_CORE_H
#define BL_CORE_H

#include <stdint.h>
#include <stdbool.h>
#include "bl_result_type.h"
#include "bl_config.h"
#include "../../../peripheral/port/plib_port.h"
#include "../../../peripheral/nvmctrl/plib_nvmctrl.h"

/**
 * @ingroup mdfu_client_32bit
 * @enum bl_block_type_t
 * @brief Contains codes corresponding to the various types
 * of data blocks that the bootloader supports.
 * @var bl_block_type_t:: UNLOCK_BOOTLOADER
 * 0x01U - Unlock Bootloader Block - Identifies an
 * operational block that holds precondition metadata to be checked and validated before
 * any memory-changing actions occur in the bootloader
 * @var bl_block_type_t:: WRITE_FLASH
 * 0x02U - Flash Data Block - Identifies operational blocks
 * that need to be written into the Flash section of the memory
 */
typedef enum
{
    UNLOCK_BOOTLOADER = 0x01U,
    WRITE_FLASH = 0x02U,
} bl_block_type_t;

/**
 * @ingroup mdfu_client_32bit
 * @struct bl_command_header_t
 * @brief Operational data orientation for each operation.
 * @var bl_command_header_t:: startAddress
 * Member 'startAddress' contains the start address of the data payload.
 */
typedef struct
{
    uint32_t startAddress;
} bl_command_header_t;

/**
 * @ingroup mdfu_client_32bit
 * @def BL_COMMAND_HEADER_SIZE
 * @brief Total size of the operational block header part.
 */
#define BL_COMMAND_HEADER_SIZE  (4U)

/**
 * @ingroup mdfu_client_32bit
 * @struct bl_block_header_t
 * @brief Header data orientation for each block.
 * @var bl_block_header_t:: blockLength
 * Member 'blockLength' contains the total length of data bytes in the block
 * @var bl_block_header_t:: blockType
 * Member 'blockType' contains the code that corresponds to the type of data inside
 * the payload buffer
 */
typedef struct
{
    uint16_t blockLength;
    bl_block_type_t blockType;
} bl_block_header_t;

/**
 * @ingroup mdfu_client_32bit
 * @def BL_BLOCK_HEADER_SIZE
 * @brief Total size of the basic block header part.
 */
#define BL_BLOCK_HEADER_SIZE    (3U)

/**
 * @ingroup mdfu_client_32bit
 * @def BL_WRITE_BYTE_LENGTH
 * @brief Maximum number of bytes that the bootloader can hold inside of its process buffer.
 */
#define BL_WRITE_BYTE_LENGTH    (NVMCTRL_FLASH_PAGESIZE)

/**
 * @ingroup mdfu_client_32bit
 * @def BL_MAX_BUFFER_SIZE
 * @brief Maximum length of data in bytes that the bootloader can receive from the host in each operational block.
 */
#define BL_MAX_BUFFER_SIZE      (BL_BLOCK_HEADER_SIZE + BL_COMMAND_HEADER_SIZE + BL_WRITE_BYTE_LENGTH)

/**
 * @ingroup mdfu_client_32bit
 * @brief Performs the initialization steps required to configure the bootloader peripherals.
 * 
 * @param None.
 * @return @ref BL_PASS - Bootloader initialization was successful
 * @return @ref BL_ERROR_COMMAND_PROCESSING - Bootloader initialization failed
 */
bl_result_t BL_Initialize(void);

/**
 * @ingroup mdfu_client_32bit
 * @brief Executes the required action based on the block type received in the bootloader data buffer.
 * 
 * @param [in] commandBuffer - Pointer to the start of the bootloader operational data
 * @param [in] commandLength - Length of the new data received by the FTP
 * @return @ref BL_PASS - Process cycle finished successfully
 * @return @ref BL_FAIL - Process cycle failed unexpectedly
 * @return @ref BL_ERROR_UNKNOWN_COMMAND - Process cycle encountered an unknown command
 * @return @ref BL_ERROR_VERIFICATION_FAIL - Process cycle failed to verify the application image
 * @return @ref BL_ERROR_COMMAND_PROCESSING - Process cycle failed due to a data or processing related issue
 * @return @ref BL_ERROR_ADDRESS_OUT_OF_RANGE - Process cycle failed due to an incorrect address
 */
bl_result_t BL_BootCommandProcess(uint8_t * commandBuffer, uint16_t commandLength);

/**
 * @ingroup mdfu_client_32bit
 * @brief Performs actions to jump the MCU program counter to
 * the application start address.
 */
void BL_ApplicationStart(void);

/**
 * @ingroup mdfu_client_32bit
 * @brief Checks the software entry flags for a forced entry into Boot mode.
 *
 * @return True - The first four addresses of RAM contain the BL_SOFTWARE_ENTRY_PATTERN
 * @return False - The first four addresses of RAM do not contain the BL_SOFTWARE_ENTRY_PATTERN
 *
 * @note This function can be updated to check any forced entry mechanism. For example, utilizing a switch to enter the bootloader at start-up.
 */
bool BL_CheckForcedEntry(void);

#endif // BL_CORE_H