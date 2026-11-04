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
 * @file        bl_config.h
 * @ingroup     mdfu_client_32bit
 *
 * @brief       Contains macros and type definitions related to the
 *              bootloader client device configuration and bootloader settings.
 */


#ifndef BL_BOOT_CONFIG_H
/* cppcheck-suppress misra-c2012-2.5; This is a false positive. */
#define BL_BOOT_CONFIG_H

#include <stdint.h>

/**
 * @ingroup mdfu_client_32bit
 * @def BL_IMAGE_FORMAT_MAJOR_VERSION
 * @brief Represents the major version of the image format that is
 * understood by the bootloader core. \n
 */
#define BL_IMAGE_FORMAT_MAJOR_VERSION (0x1)
/**
 * @ingroup mdfu_client_32bit
 * @def BL_IMAGE_FORMAT_MINOR_VERSION
 * @brief Represents the minor version of the image format that is
 * understood by the bootloader core. \n
 */
#define BL_IMAGE_FORMAT_MINOR_VERSION (0x0)
/**
 * @ingroup mdfu_client_32bit
 * @def BL_IMAGE_FORMAT_PATCH_VERSION
 * @brief Represents the patch version of the image format that is
 * understood by the bootloader core. \n
 */
#define BL_IMAGE_FORMAT_PATCH_VERSION (0x0)
/**
 * @ingroup mdfu_client_32bit
 * @def BL_VECTORED_INTERRUPTS_ENABLED
 * @brief Indicates that the bootloader supports vectored interrupts in the application.
 *
 * @note Not needed by all architectures.
 */
#define BL_VECTORED_INTERRUPTS_ENABLED (0)
/**
 * @ingroup mdfu_client_32bit
 * @def BL_APPLICATION_START_ADDRESS
 * @brief Start of the application memory space.
 */
#define BL_APPLICATION_START_ADDRESS (0xC004000U)
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
#define BL_APPLICATION_END_ADDRESS (0xC009FFFU)
/**
 * @ingroup mdfu_client_32bit
 * @def BL_IMAGE_PARTITION_SIZE
 * @brief Defined size of the application memory space.
 */
#define BL_IMAGE_PARTITION_SIZE (0x6000U) // Flash size - the size of the bootloader
/**
 * @ingroup mdfu_client_32bit
 * @def BL_STAGING_IMAGE_START
 * @brief Start of the application download space.
 */
#define BL_STAGING_IMAGE_START (0xC00A000U)
/**
 * @ingroup mdfu_client_32bit
 * @def BL_STAGING_IMAGE_END
 * @brief End of the application download space.
 */
#define BL_STAGING_IMAGE_END (0xC00FFFFU)
/**
 * @ingroup mdfu_client_32bit
 * @def BL_STAGING_IMAGE_ID
 * @brief Image area ID that identifies the download location of the transferred data.
 */
#define BL_STAGING_IMAGE_ID (1U)
/**
 * @ingroup mdfu_client_32bit
 * @def BL_APPLICATION_IMAGE_COUNT
 * @brief Number to represent how many image spaces are configured by the bootloader.
 */
#define BL_APPLICATION_IMAGE_COUNT (2U)
/**
 * @ingroup mdfu_client_32bit
 * @def BL_SOFTWARE_ENTRY_PATTERN_START
 * @brief Start address of the software entry pattern array.
 */
#define BL_SOFTWARE_ENTRY_PATTERN_START (0x20000000U + (0x0002000U - 16U))
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
 * @ingroup mdfu_client_8bit_core
 * @def SIGNATURE_LENGTH
 * The size of the ECDSA signature.
 */
#define SIGNATURE_LENGTH      (64U)
/**
 * @ingroup mdfu_client_32bit
 * @def APPLICATION_SLOT_ID_DATA_SIZE
 * @brief Size of the application ID data in bytes.
 */
#define APPLICATION_SLOT_ID_DATA_SIZE (4U)
/**
* @ingroup mdfu_client_32bit
* @def APPLICATION_VERSION_DATA_SIZE
* @brief Size of the version data in bytes.
*/
#define APPLICATION_VERSION_DATA_SIZE (4U)
/**
* @ingroup mdfu_client_32bit
* @def VERIFY_END_ADDRESS_SIZE
* @brief Size of the verify end address data in bytes.
*/
#define VERIFY_END_ADDRESS_SIZE (4U)
/**
* @ingroup mdfu_client_32bit
* @def VERIFY_START_ADDRESS_SIZE
* @brief Size of the verify start address data in bytes.
*/
#define VERIFY_START_ADDRESS_SIZE (4U)
/**
* @ingroup mdfu_client_32bit
* @def HASH_DATA_OFFSET
* @brief Offset of the hash data in bytes, calculated as the sum of verify start address size, verify end address size, version data size, and partition ID data size.
*/
#define HASH_DATA_OFFSET (VERIFY_START_ADDRESS_SIZE + VERIFY_END_ADDRESS_SIZE + APPLICATION_VERSION_DATA_SIZE + APPLICATION_SLOT_ID_DATA_SIZE)
/**
* @ingroup mdfu_client_32bit
* @def ANTI_ROLLBACK_ENABLED
* @brief Defines whether the anti-rollback feature is enabled or not.
*/
#define BL_ANTI_ROLLBACK_ENABLED (0U)
/**
* @ingroup mdfu_client_32bit
* @def BL_RESTORATION_FROM_BACKUP_ENABLED
* @brief Defines whether the backup image feature is enabled or not.
*/
#define BL_RESTORATION_FROM_BACKUP_ENABLED (0U)
/**
* @ingroup mdfu_client_32bit
* @enum bl_image_id_t
* @brief Contains the code corresponding to the various image IDs
* used in the system.
* @var IMAGE_ID::IMAGE_0
* 0x00 - Image ID 0 will always be the execution space due to hardware limitations. The image will be located from address 0xC004000 to address 0xC009FFF
* @var IMAGE_ID::IMAGE_1
* 0x01 - Image ID 1 is the image space that resides from address 0xC00A000 to address 0xC00FFFF
*/
typedef enum
{
    IMAGE_0 = 0x00,
    IMAGE_1
} bl_image_id_t;
/**
 * @ingroup mdfu_client_32bit
 * @struct bl_footer_data_t
 * @brief Contains metadata for the bootloader footer.
 * @var bl_footer_data_t::applicationId
 * Contains the identifier for the application. The high byte identifies where the image can be executed from (0x00 in most cases). The low byte identifies the image space where it will be stored.
 * @var bl_footer_data_t::applicationVersion
 * Contains the version of the application.
 * @var bl_footer_data_t::verificationEndAddress
 * Contains the end address for verification.
 * @var bl_footer_data_t::verificationStartAddress
 * Contains the start address for verification.
 * @var bl_footer_data_t::verificationData
 * Contains the verification hash value for verification.
 */
typedef struct
{    
    uint32_t applicationId;
    uint32_t applicationVersion;
    uint32_t verificationEndAddress;
    uint32_t verificationStartAddress;
    uint8_t signature[SIGNATURE_LENGTH];
    uint32_t verificationData;
} bl_footer_data_t;
/**
 * @ingroup mdfu_client_32bit
 * @def ASM_VECTOR
 * @brief Macro defined to jump the program to the application reset location.
 */
#define ASM_VECTOR              asm("bx %0"::"r" (reset_vector))

#endif // BL_BOOT_CONFIG_H