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
 * @file        bl_image_manager.h
 * @defgroup    bl_image_manager Image Manager for 8-bit MDFU Client
 * @ingroup     mdfu_client_32bit
 * 
 * @brief       Contains the API prototypes to
 *              perform image footer data related operations.
 */

#ifndef BL_IMAGE_MANAGER_H
#define	BL_IMAGE_MANAGER_H

#include "bl_config.h"
#include "stdbool.h"
#include "bl_memory.h"

/**
* @ingroup bl_image_manager
* @brief Retrieves the start address of the application based on the provided image ID
* @param [in] imageId - Identifier for the application image space
* @return uint32_t - The start address of the specified application
*/
uint32_t BL_ApplicationStartAddressGet(uint8_t imageId);

/**
* @ingroup bl_image_manager
* @brief Retrieves the start address of the application footer based on the provided image ID
* @param [in] imageId - Identifier for the application image space
* @return uint32_t - The start address of the specified application footer
*/
uint32_t BL_ApplicationFooterStartAddressGet(uint8_t imageId);

/**
* @ingroup bl_image_manager
* @brief Retrieves the version of the application based on the provided image ID
* @param [in] imageId - Identifier for the application image space
* @return uint32_t - The version of the specified application image
*/
uint32_t BL_ApplicationVersionGet(uint8_t imageId);

/**
* @ingroup bl_image_manager
* @brief Retrieves the download ID of the application based on the provided image ID
* @param [in] imageId - Identifier for the application image space
* @return uint8_t - The download ID of the specified application image
*/
uint8_t BL_ApplicationDownloadIdGet(uint8_t imageId);

/**
* @ingroup bl_image_manager
* @brief Retrieves the execution ID of the application based on the provided image ID
* @param [in] imageId - Identifier for the application image space
* @return uint8_t - The execution ID of the specified application image
*/
uint8_t BL_ApplicationExecutionIdGet(uint8_t imageId);

/**
* @ingroup bl_image_manager
* @brief Validates the provided application version
* @param [in] imageVersion - Version of the application image to be validated
* @return True - Image version is valid
* @return False - Image version is invalid
*/
bool BL_ApplicationIsVersionValid(uint32_t imageVersion);

/**
* @ingroup bl_image_manager
* @brief Reads the footer data of the application based on the provided application ID
* @param [in] appId - Identifier for the application image space
* @param [out] footerData - Pointer to the structure where the footer data will be stored
* @return @ref bl_mem_result_t - Result of the bootloader memory operation
*/
bl_mem_result_t BL_ApplicationFooterRead(uint8_t appId, bl_footer_data_t * footerData);

/**
* @ingroup bl_image_manager
* @brief Performs a rollback check on the version data present in the target footer by taking the given image ID
* as the new version data and the target version as the old data
* @pre Run this function only when both image locations have been verified.
* @param [in] imageId - Identifier for the application image space
* @return True - The version data at image ID is either newer than the version data held at the target location or the
* target location does not have a valid version
* @return False - The version data at image ID is older than the version data held at the target location 
*/
bool BL_ApplicationRollbackCheck(uint8_t imageId);

#endif	/* BL_IMAGE_MANAGER_H */
