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
 * @file        bl_config.h
 * @ingroup     mdfu_client_32bit
 *
 * @brief       Contains macros and type definitions related to the
 *              bootloader client device configuration and bootloader settings.
 */

#ifndef BL_CONFIG_H
/* cppcheck-suppress misra-c2012-2.5; This is a false positive. */
#define BL_CONFIG_H

/**
 * @ingroup mdfu_client_32bit
 * @def BL_IMAGE_FORMAT_MAJOR_VERSION
 * @brief Represents the major version of the image format that is understood by the bootloader core.
 */
#define BL_IMAGE_FORMAT_MAJOR_VERSION (0x1)
/**
 * @ingroup mdfu_client_32bit
 * @def BL_IMAGE_FORMAT_MINOR_VERSION
 * @brief Represents the minor version of the image format that is understood by the bootloader core.
 */
#define BL_IMAGE_FORMAT_MINOR_VERSION (0x0)
/**
 * @ingroup mdfu_client_32bit
 * @def BL_IMAGE_FORMAT_PATCH_VERSION
 * @brief Represents the patch version of the image format that is understood by the bootloader core.
 */
#define BL_IMAGE_FORMAT_PATCH_VERSION (0x0)
/**
 * @ingroup mdfu_client_32bit
 * @def BL_VECTORED_INTERRUPTS_ENABLED
 * @brief Indicates that the bootloader supports vectored interrupts in the application.
 */
#define BL_VECTORED_INTERRUPTS_ENABLED (0)
/**
 * @ingroup mdfu_client_32bit
 * @def BL_APPLICATION_START_ADDRESS
 * @brief Start of the application memory space.
 */
#define BL_APPLICATION_START_ADDRESS (0xC002000U)
/**
 * @ingroup mdfu_client_32bit
 * @def BL_DEVICE_ID_START_ADDRESS_U
 * @brief Device ID address.
 */
#define BL_DEVICE_ID_START_ADDRESS_U (0x41002120U)
/**
 * @ingroup mdfu_client_32bit
 * @def BL_APPLICATION_END_ADDRESS
 * @brief End of the application memory space.
 */
#define BL_APPLICATION_END_ADDRESS (0xC00FFFFU)
/**
 * @ingroup mdfu_client_32bit
 * @def BL_IMAGE_PARTITION_SIZE
 * @brief Defined size of the application memory space.
 */
#define BL_IMAGE_PARTITION_SIZE (0xE000U)
/**
 * @ingroup mdfu_client_32bit
 * @def BL_STAGING_IMAGE_START
 * @brief Start of the application download space.
 */
#define BL_STAGING_IMAGE_START (BL_APPLICATION_START_ADDRESS)
/**
 * @ingroup mdfu_client_32bit
 * @def BL_STAGING_IMAGE_END
 * @brief End of the application download space.
 */
#define BL_STAGING_IMAGE_END (BL_APPLICATION_END_ADDRESS)
/**
 * @ingroup mdfu_client_32bit
 * @def BL_STAGING_IMAGE_ID
 * @brief Image area ID that identifies the download location of the transferred data.
 */
#define BL_STAGING_IMAGE_ID (0U)
/**
 * @ingroup mdfu_client_32bit
 * @def BL_APPLICATION_IMAGE_COUNT
 * @brief Number to represent how many image spaces are configured by the bootloader.
 */
#define BL_APPLICATION_IMAGE_COUNT (1U)
/**
 * @ingroup mdfu_client_32bit
 * @def BL_SOFTWARE_ENTRY_PATTERN_START_ADDRESS
 * @brief Start address of the software entry pattern array.
 */
#define BL_SOFTWARE_ENTRY_PATTERN_START_ADDRESS (0x20000000)
/**
 * @ingroup mdfu_client_32bit
 * @def BL_SOFTWARE_ENTRY_PATTERN
 * @brief 32-bit pattern used to indicate that a software entry has been requested.
 */
#define BL_SOFTWARE_ENTRY_PATTERN (0x5048434DU)
/**
 * @ingroup mdfu_client_32bit
 * @def HASH_DATA_SIZE
 * @brief Size of the verification hash data in bytes.
 */
#define BL_HASH_DATA_SIZE (4U)
/**
 * @ingroup mdfu_client_32bit
 * @def ASM_VECTOR
 * @brief Macro defined to jump the program to the application reset location.
 */
#define ASM_VECTOR  asm("bx %0"::"r" (reset_vector))

#endif // BL_CONFIG_H