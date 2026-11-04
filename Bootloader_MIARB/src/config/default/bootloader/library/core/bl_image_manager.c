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
 * @file        bl_image_manager.c
 * @ingroup     bl_image_manager
 *
 * @brief       This file contains APIs to support application
 *              footer data operations and validation operations for the
 *              32-bit MDFU Client library.
 *
 * @see @ref    mdfu_client_32bit
 */

 /**@misradeviation{@required, 7.2} The MACRO is used in the bl_interrupt file as an argument for
 * assembly instructions, which requires the value to be a pure hexadecimal number without the appended
 * U or u.
 */
 
#include <string.h>
#include "bl_image_manager.h"
#include "bl_config.h"

uint32_t BL_ApplicationStartAddressGet(uint8_t imageId)
{
    uint32_t imageStartAddress = 0x00U;

    if (imageId < BL_APPLICATION_IMAGE_COUNT)
    {
        /* cppcheck-suppress misra-c2012-7.2; This rule cannot be followed due to assembly syntax requirements. */
        imageStartAddress = ((uint32_t) BL_APPLICATION_START_ADDRESS) + ((uint32_t)BL_IMAGE_PARTITION_SIZE * imageId);
    }

    return imageStartAddress;
}

/* cppcheck-suppress misra-c2012-8.7; For a driver API that is made available to users through external linkage, users have the option to add this API to the application. */
uint32_t BL_ApplicationFooterStartAddressGet(uint8_t imageId)
{
    uint32_t footerStartAddress = 0x00U;

    if (imageId < BL_APPLICATION_IMAGE_COUNT)
    {
        /* cppcheck-suppress misra-c2012-7.2; This rule cannot be followed due to assembly syntax requirements. */
        footerStartAddress = ((uint32_t) BL_APPLICATION_END_ADDRESS + 1U) + ((uint32_t)BL_IMAGE_PARTITION_SIZE * imageId) - (sizeof (bl_footer_data_t));
    }

    return footerStartAddress;
}

uint32_t BL_ApplicationVersionGet(uint8_t imageId)
{
    bl_footer_data_t workFooterData = {
        .applicationId = 0U,
        .applicationVersion = 0U,
        .verificationEndAddress = 0U,
        .verificationStartAddress = 0U,
        .signature = {0U},
        .verificationData = 0U
    };

    (void)BL_ApplicationFooterRead(imageId, &workFooterData);
    return workFooterData.applicationVersion;
}

uint8_t BL_ApplicationDownloadIdGet(uint8_t imageId)
{   
    bl_footer_data_t workFooterData = {
        .applicationId = 0U,
        .applicationVersion = 0U,
        .verificationEndAddress = 0U,
        .verificationStartAddress = 0U,
        .signature = {0U},
        .verificationData = 0U
    };
    
    (void)BL_ApplicationFooterRead(imageId, &workFooterData);
    
    // Uses only the lower 8-bits
    return (uint8_t)(workFooterData.applicationId & 0xFFU);
}

uint8_t BL_ApplicationExecutionIdGet(uint8_t imageId)
{   
    bl_footer_data_t workFooterData = {
        .applicationId = 0U,
        .applicationVersion = 0U,
        .verificationEndAddress = 0U,
        .verificationStartAddress = 0U,
        .signature = {0U},
        .verificationData = 0U
    };
    
    (void)BL_ApplicationFooterRead(imageId, &workFooterData);
    
    // Uses only the upper 8-bits
    return (uint8_t)(workFooterData.applicationId & 0xFF00U);
}

bool BL_ApplicationIsVersionValid(uint32_t imageVersion)
{
    return ((imageVersion != 0xFFFFFFFFU) && (imageVersion != 0x00000000U));
}

bl_mem_result_t BL_ApplicationFooterRead(uint8_t appId, bl_footer_data_t * footerData)
{
    uint32_t footerAddressStart = BL_ApplicationFooterStartAddressGet(appId);
    bl_mem_result_t readResult = BL_MEM_FAIL;

    bl_footer_data_t workFooterData = {
        .verificationEndAddress = 0U,
        .verificationStartAddress = 0U,
        .signature = {0U},
        .verificationData = 0U
    };
    
    readResult = NVMCTRL_Read((uint32_t *) & workFooterData, sizeof(bl_footer_data_t), footerAddressStart);

    if (BL_MEM_PASS == readResult)
    {
        footerData->applicationId = workFooterData.applicationId;
        footerData->applicationVersion = workFooterData.applicationVersion;
        footerData->verificationEndAddress = workFooterData.verificationEndAddress;
        footerData->verificationStartAddress = workFooterData.verificationStartAddress;
        (void)memcpy(footerData->signature,workFooterData.signature,SIGNATURE_LENGTH);
        footerData->verificationData = workFooterData.verificationData;
    }

    return readResult;
}

bool BL_ApplicationRollbackCheck(uint8_t imageId)
{
    // Initialize the return value
    bool isTargetVersionNewer = false;
    // Read the id from the requested location which corresponds to the update slot the data should reside in
    uint8_t targetImageId = BL_ApplicationDownloadIdGet(imageId);

    // Perform check if the target location is different than the requested location
    if (targetImageId != imageId)
    {
        // Read the version data held at the requested image location and target update location
        uint32_t newVersion = BL_ApplicationVersionGet(imageId);
        uint32_t oldImageVersion = BL_ApplicationVersionGet(targetImageId);

        // Check validity of the data
        bool oldVersionIsValid = BL_ApplicationIsVersionValid(oldImageVersion);
        bool newVersionIsValid = BL_ApplicationIsVersionValid(newVersion);
        
        // If both versions are valid
        if ((true == oldVersionIsValid) && (true == newVersionIsValid))
        {
            // Anti-Rollback check
            isTargetVersionNewer = (newVersion > oldImageVersion);
        }
        else if ((false == oldVersionIsValid) && (true == newVersionIsValid))
        {
            // If the target location is not valid and the new version is valid; set status to pass
            isTargetVersionNewer = true;
        }
        else
        {
            // Do nothing
        }
    }

    return isTargetVersionNewer;
}