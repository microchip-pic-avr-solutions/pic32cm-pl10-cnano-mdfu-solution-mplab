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
 * @file        bl_app_verify.c
 * @ingroup     mdfu_client_32bit
 *
 * @brief       Contains APIs to support verification of the
 *              application image space.
 */

#include <stdint.h>
#include <stdbool.h>
#include "bl_app_verify.h"
#include "bl_config.h"
#include "bl_sha256.h"
#include "bl_memory.h"
#include "bl_image_manager.h"
#include "../../../peripheral/nvmctrl/plib_nvmctrl.h"
#include "../../../peripheral/dmac/plib_dmac.h"
#include "../../../library/cryptoauthlib/atca_basic.h"
#include "../../../library/cryptoauthlib/atca_iface.h"
#include "../../../library/cryptoauthlib/atca_status.h"
#include "../../../library/cryptoauthlib/calib/calib_basic.h"

#define EMPTY_ADDRESS (0xFFFFFFFFU)
#define KEY_SLOT_TO_USE (13U)


bl_result_t BL_ImageVerify(void)
{
    // The staging area must always be validated when the FTP is connected to the core.
    // Verify the staging area
    bl_result_t verificationStatus = BL_ImageVerifyById(BL_STAGING_IMAGE_ID);

    // The protocol calls for having Anti-Rollback notify the host of the failure in versions at the time of the update
#if (BL_ANTI_ROLLBACK_ENABLED == 1)
    if (BL_PASS == verificationStatus)
    {
        // Perform rollback check on the data held at the staging area
        if (true == BL_ApplicationRollbackCheck((uint8_t) BL_STAGING_IMAGE_ID))
        {
            verificationStatus = BL_PASS;
        }
        else
        {
            verificationStatus = BL_ERROR_ROLLBACK_FAILURE;
        }
    }
#endif
    return verificationStatus;
}

bl_result_t BL_ImageVerifyById(uint8_t installLocationId)
{
    bl_result_t result = BL_ERROR_VERIFICATION_FAIL;
    bl_mem_result_t footerReadResult = BL_MEM_FAIL;
    ATCA_STATUS status;
    bool isVerified = false;
    uint8_t sha256Result[32];
    bl_footer_data_t footerData = {
        .applicationId = 0U,
        .applicationVersion = 0U,
        .verificationEndAddress = 0U,
        .verificationStartAddress = 0U,
        .signature = {0U},
#if BL_HASH_DATA_SIZE != 0U
        .verificationData = 0U
#endif
    };
    
    footerReadResult = BL_ApplicationFooterRead(installLocationId, &footerData);
    if (BL_MEM_PASS == footerReadResult)
    {
        if ((footerData.verificationStartAddress != EMPTY_ADDRESS) || (footerData.verificationEndAddress != EMPTY_ADDRESS))
        {
            if (installLocationId != (uint8_t)IMAGE_0)
            {
                uint32_t offset = (uint32_t)((uint32_t)installLocationId & 0x00FFU) * (uint32_t) BL_IMAGE_PARTITION_SIZE;
                footerData.verificationStartAddress += offset;
                footerData.verificationEndAddress += offset;
            }
            SHA256(footerData.verificationStartAddress, footerData.verificationEndAddress, sha256Result);

            status = atcab_verify_stored(sha256Result, footerData.signature, KEY_SLOT_TO_USE, &isVerified);

            if ((ATCA_SUCCESS == status) && (true == isVerified))
            {
                result = BL_PASS;
            }
            else
            {
                result = BL_ERROR_VERIFICATION_FAIL;
            }
        }
        else
        {
            result = BL_ERROR_INVALID_ARGUMENTS;
        }
    }
    else
    {
        result = BL_FAIL;
    }
    
    return result;
}