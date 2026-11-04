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
 * @file    bl_memory.h
 * @defgroup bl_memory Memory Helper
 * @brief   This file contains the API prototypes and data types for the helper functions used with the Non-volatile Memory (NVM) peripheral driver
 *
 */
#ifndef BL_MEMORY_H
/* cppcheck-suppress misra-c2012-2.5 */
#define BL_MEMORY_H

#include <stdint.h>
#include <xc.h>
#include "../../../peripheral/nvmctrl/plib_nvmctrl.h"
#include "bl_config.h"
#include <string.h>

#define PROGMEM_SIZE (200000U)
#define PROGMEM_PAGE_SIZE (512U)

/**
* @ingroup bl_memory
* @def KEY_OPERATOR
* @brief Defines a key operator used by the core as a form of internal memory write protection.
* @details This macro defines a constant value (0x1234U) that is used as an operator on the internal memory keys.
 By forcefully scaling the key values used for internal memory actions, the bootloader can have some safe guards
 against undesired writes if the application code accidentally jumps to the internal memory APIs.
*/
#define BL_KEY_OPERATOR (0x1234U) /* cppcheck-suppress misra-c2012-2.5; This is a false positive. */

/**
 * @ingroup bl_memory
 * @struct key_structure_t
 * @brief Contains variables for the keys received by the user from the bootloader memory extension APIs.
 * @var key_structure_t:: eraseUnlockKey
 * Contains the unlock key needed to erase a page of memory.
 * @var key_structure_t:: readUnlockKey
 * Contains the unlock key needed to read a page of memory.
 * @var key_structure_t:: byteWordWriteUnlockKey
 * Contains the unlock key needed to write a word/byte to memory.
 * @var key_structure_t:: rowWriteUnlockKey
 * Contains the unlock key needed to write a row to memory.
 */
typedef struct
{
    uint16_t eraseUnlockKey;
    uint16_t readUnlockKey;
    uint16_t byteWordWriteUnlockKey;
    uint16_t rowWriteUnlockKey;
} key_structure_t;

/**
 * @ingroup bl_memory
 * @enum bl_mem_result_t
 * @brief Contains the code for the return values of the bootloader memory extension APIs.
 * @var bl_mem_result_t:: BL_MEM_PASS
 * 0x00 - NVM operation succeeded
 * @var bl_mem_result_t:: BL_MEM_FAIL
 * 0x01 -  NVM operation failed
 * @var bl_mem_result_t:: BL_MEM_INVALID_ARG
 * 0x02 -  NVM operation failed due to invalid argument
 *
 */
typedef enum
{
    BL_MEM_FAIL = 0x00U,
    BL_MEM_PASS = 0x01U, 
    BL_MEM_INVALID_ARG = 0x02U,
} bl_mem_result_t;


/**
 * @ingroup bl_memory
 * @brief Helper function to enable the direct copying of one Flash area to another.
 * @param [in] srcAddress - Starting address of the source data for the Flash copy operation
 * @param [in] destAddress - Starting address of the destination for the Flash copy operation
 * @param [in] length - Total number of bytes to be copied to the destination address
 * @return @ref BL_MEM_PASS - Flash write succeeded \n
 * @return @ref BL_MEM_FAIL - Flash write failed \n
 * @return @ref BL_MEM_INVALID_ARG - An invalid argument is passed to the function \n
 */
bl_mem_result_t BL_FlashCopy(uint32_t srcAddress, uint32_t destAddress, size_t length);

#endif /* BL_MEMORY_H */