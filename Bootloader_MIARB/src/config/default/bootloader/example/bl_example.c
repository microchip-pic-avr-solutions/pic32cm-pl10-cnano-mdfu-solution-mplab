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
 * @file        bl_example.c
 * @ingroup     mdfu_client_32bit
 *
 * @brief       Contains APIs for running a bootloader update process
 *              with multiple image spaces using the FTP Handler and bootloader APIs.
 */
#include "../library/core/bl_core.h"
#include "../library/core/bl_app_verify.h"
#include "../library/core/ftp/bl_ftp.h"
#include "../library/core/bl_image_manager.h"
#include "../../peripheral/port/plib_port.h"
#include "bl_example.h"

/**
 * @ingroup mdfu_client_32bit
 * @def BOOTLOADER_START_ADDRESS
 * Defines the start address of the bootloader in Flash memory.
 * This value is used by the bootloader and application to identify
 * the memory region reserved for the bootloader operations.
 */
#define BOOTLOADER_START_ADDRESS (0x0000U)

/**
 * @ingroup mdfu_client_32bit
 * @def IO_PIN_ENTRY_GetInputValue
 * Remaps the get value function of the entry pin.
 */
#define IO_PIN_ENTRY_GetInputValue  BL_ENTRY_Get

/**
 * @ingroup mdfu_client_32bit
 * @def IO_PIN_ENTRY_RUN_BL
 * Represents the "run bootloader" signal based on the
 * entry pin activation setting.
 * This is the expected level required at the pin to enter into Bootloader mode.
 */
#define IO_PIN_ENTRY_RUN_BL         (0U)

/**
 * @ingroup mdfu_client_32bit
 * @def BL_INDICATOR_ON
 * Enables the bootloader indicator pin.
 * When the pin is set to start high, the bootloader will assume
 * that it needs to drive the pin low to enable it.
 */
#define BL_INDICATOR_ON             BL_INDICATOR_Clear

/**
 * @ingroup mdfu_client_32bit
 * @def BL_INDICATOR_OFF
 * Disables the bootloader indicator pin.
 * When the pin is set to start high, the bootloader will assume
 * that it needs to drive the pin high to disable it.
 */
#define BL_INDICATOR_OFF            BL_INDICATOR_Set

typedef enum
{
    BOOTLOADER,
    APPLICATION,
    ERROR_STATE,
} bootloader_state_t;

static bootloader_state_t BootState;
static bool stagingAreaIsValid = false;
static bool isExecutionAreaValidated = false;
static bool executionImageHasBeenTested = false;

static bool ForcedEntryCheck(void);

void BL_Example(void)
{
    bl_result_t result = BL_FAIL;

    switch (BootState)
    {
    case APPLICATION:
        BL_INDICATOR_OFF();
        BL_ApplicationStart();
        break;
        
    case BOOTLOADER:
        BL_INDICATOR_ON();
        /**
         * FTP tasks should be run to:
         * 1. Receive the data from the COM layer.
         * 2. Perform the verification on the area where it is downloaded.
         * 3. Communicate with the MDFU host.
         */
        result = FTP_Task();
        break;
        default:
        // Unknown State; Do nothing
        break;
    }

    if (result == BL_ERROR_VERIFICATION_FAIL)
    {

    }
}

#if BL_APPLICATION_IMAGE_COUNT > 1

static bl_result_t LoadNewImage(void)
{
    bl_result_t loadStatus = BL_FAIL;
    bool stagedImageRequiresLoading = false;
    /* coverity[misra_c_2023_rule_2_2_violation] Reserved for future use */
    bool isTargetImageValid = false;
    uint8_t targetId = BL_STAGING_IMAGE_ID;

    // Check to see if the staging area is valid
    stagingAreaIsValid = (BL_PASS == BL_ImageVerifyById(BL_STAGING_IMAGE_ID));

    if (true == stagingAreaIsValid)
    {
        /**
         * If the staging area is valid we can continue checking data.
         * Get the target id from the staging area footer data
         */ 
        targetId = BL_ApplicationDownloadIdGet(BL_STAGING_IMAGE_ID);

#if BL_ANTI_ROLLBACK_ENABLED == 1
        /**
         * In order to check version data, we need to verify that the data is valid and has not been corrupted
         */

        // Verify the target location
        isTargetImageValid = (BL_PASS == BL_ImageVerifyById(targetId));

        // If the execution space was just tested; log the results and set the flag to prevent re-verification later.
        if (targetId == (uint8_t)IMAGE_0)
        {
            // Image was already validated
            isExecutionAreaValidated = isTargetImageValid;
            executionImageHasBeenTested = true;
        }

        if (true == isTargetImageValid)
        {
            /**
             * If the target location is valid then we are allowed to perform the version checks.
             * Extract the version from the target location.
             */
            stagedImageRequiresLoading = BL_ApplicationRollbackCheck(BL_STAGING_IMAGE_ID);
        }
        else if (true == BL_ApplicationIsVersionValid(BL_ApplicationVersionGet(BL_STAGING_IMAGE_ID)))
        {
            /**
             * If the target image is not valid and the staging area has a valid version then, we can't trust the version held in the target space.
             * We must load the staged image.
             */
            stagedImageRequiresLoading = true;
        }
        else
        {
            asm("nop");
            stagedImageRequiresLoading = false;
        }
#else
        /**
         * If the staged image is valid and rollback is not enabled
         * Load the staged image in all cases because there is no way to prove it was already loaded
         */
        stagedImageRequiresLoading = true;
#endif
    }
    else
    {
        // If the staged image fails verification then we can't load it
        stagedImageRequiresLoading = false;
        loadStatus = BL_ERROR_VERIFICATION_FAIL;
    }
    
    if (true == stagedImageRequiresLoading)
    {
        // Copy the staged image into the target location
        loadStatus = BL_CopyImageAreas((uint8_t)BL_STAGING_IMAGE_ID, (uint8_t)targetId);

        // We need to verify the copied data is valid.
        if (BL_PASS == loadStatus)
        {
            loadStatus = BL_ImageVerifyById(targetId);

            // If the target image is the execution space, then we need to reset the static flags for the execution status
            if (targetId == (uint8_t)IMAGE_0)
            {
                isExecutionAreaValidated = (BL_PASS == loadStatus);
                executionImageHasBeenTested = true;
            }
        }
    }
    return loadStatus;
}
#endif

/**
 * Initializes the example by performing checks on entry mechanisms and current image spaces.
 * Then, set the BootState to tell the example what to do:
 * - BOOTLOADER -> Bootloader process, update/install new image
 * - APPLICATION -> Jump to the application reset vector
 */
bl_example_result_t BL_ExampleInitialize(void)
{
    // Initialize the FTP handler
    bl_result_t initStatus = FTP_Initialize();

    if ((bl_result_t)BL_PASS == initStatus)
    {
#warning "Customize the Initialization steps for the startup process and set the BootState accordingly."
        // Make assumption: We always start in bootload state

        BootState = BOOTLOADER;

        // If forced entry is requested, enter bootloader
        if (true == ForcedEntryCheck())
        {
            BootState = BOOTLOADER;
        }
        else if (true == BL_CheckForcedEntry())
        {
            BootState = BOOTLOADER;
        }
        else
        {
            /**
             *  Three operations that need to occur in order whenever the device starts up:
             *      1. Determine if the staging area needs to be loaded into the target location.
             *      2. Determine if the execution space is valid and can be executed.
             *      3. If execution image is not valid and if restoration feature is enabled; load the backup image.
             */

            /**
             * Staging area must be loaded if:
             * - Staging area is valid and target image is not valid
             * - Staging area is valid and target image does not have a version
             * - Staging area is valid and target image is valid, but the staging version is newer than the target
             * - If anti-rollback is not enabled, version data cannot be checked to determine if loading is required.
             *      Therefore, in this case the staging area will always be loaded to be certain the data is valid.
             * - Otherwise, no load is required
             */
            initStatus = LoadNewImage();

            /**
             * Stay in Bootloader mode if:
             * - Execution image is not valid
             * - Execution image does not have a version (Only supported when anti-rollback is enabled)
             * - Otherwise, run the application that has been verified
             */

            // If the execution image was already validated during the loading operation; save cycles by skipping it here
            if (false == isExecutionAreaValidated)
            {
                initStatus = BL_PASS;
                /**
                 * If the execution space is not valid;
                 * check to see if a verification on the
                 * execution space during the loading operation have already run.
                 */
                if (false == executionImageHasBeenTested)
                {
                    // Run the verification if we have not done so already
                    isExecutionAreaValidated = (BL_PASS == BL_ImageVerifyById((uint8_t)(IMAGE_0)));
                }

                // Set the initial status based on the execution space's status
                if (isExecutionAreaValidated)
                {
#if BL_ANTI_ROLLBACK_ENABLED == 1
                    // After we know the execution image is valid; pull out the version that it holds
                    uint32_t executionVersion = BL_ApplicationVersionGet((uint8_t)(IMAGE_0));

                    // If the execution space does not have a valid version we should not be running it
                    if (true == BL_ApplicationIsVersionValid(executionVersion))
                    {
                        BootState = APPLICATION;
                        initStatus = BL_PASS;
                    }
                    else
                    {
                        // Override the verification flag because the image does not contain a valid image version
                        isExecutionAreaValidated = false;
                        BootState = BOOTLOADER;
                        initStatus = BL_ERROR_ROLLBACK_FAILURE;
                    }
#else
                    // Anti-Rollback is not enabled
                    BootState = APPLICATION;
                    /* coverity[misra_c_2023_rule_2_2_violation] Value used in conditional compilation path */
                    initStatus = BL_PASS;
#endif
                }
                else
                {
                    BootState = BOOTLOADER;
                }
            }
            else
            {
                // The execution space has been validated already. Check the version if need be
#if BL_ANTI_ROLLBACK_ENABLED == 1
                    // Pull out the version that it holds
                    uint32_t executionVersion = BL_ApplicationVersionGet((uint8_t)(IMAGE_0));

                    // If the execution space does not have a valid version we should not be running it
                    if (true == BL_ApplicationIsVersionValid(executionVersion))
                    {
                        BootState = APPLICATION;
                        initStatus = BL_PASS;
                    }
                    else
                    {
                        // Override the verification flag because the image does not contain a valid image version
                        isExecutionAreaValidated = false;
                        BootState = BOOTLOADER;
                        initStatus = BL_ERROR_ROLLBACK_FAILURE;
                    }
#else
                    // Anti-Rollback is not enabled
                    BootState = APPLICATION;
                    /* coverity[misra_c_2023_rule_2_2_violation] Value used in conditional compilation path */
                    initStatus = BL_PASS;
#endif
            }
        }
    }
    else
    {

        BootState = ERROR_STATE;
    }
    return EXAMPLE_OK;
}

static bool ForcedEntryCheck(void)
{
    bool result = false;
    
    for (uint8_t i = 0U; i != 0xFFU; i++)
    {
        asm("nop");
    }
    // Check for entry pin signal
    /* cppcheck-suppress misra-c2012-10.1 */
    if (IO_PIN_ENTRY_GetInputValue() == IO_PIN_ENTRY_RUN_BL)
    {
        result = true;
    }
    return result;
}