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
 * @file        bl_core.c
 * @ingroup     mdfu_client_32bit
 *
 * @brief       Contains APIs to support file transfer-based
 *              bootloader operations, including a File Transfer Protocol(FTP) module and all bootloader
 *              core firmware.
 *
 * @see @ref    mdfu_client_ftp
 */

#include "bl_core.h"
#include "bl_config.h"
#include "ftp/bl_ftp.h"

/**
 * @ingroup mdfu_client_32bit
 * @struct bl_unlock_boot_metadata_t
 * @brief Structure containing metadata required to unlock the bootloader.
 *
 * This structure holds information about the bootloader image version,
 * device identification, payload size, and associated command header.
 * This data is processed as the first block of file data and will not
 * allow memory operations to occur in the core until this data has been
 * validated.
 *
 * @var bl_unlock_boot_metadata_t::blockHeader
 *   Block header information for the bootloader metadata.
 * @var bl_unlock_boot_metadata_t::imageVersionPatch
 *   Patch version of the bootloader image.
 * @var bl_unlock_boot_metadata_t::imageVersionMinor
 *   Minor version of the bootloader image.
 * @var bl_unlock_boot_metadata_t::imageVersionMajor
 *   Major version of the bootloader image.
 * @var bl_unlock_boot_metadata_t::deviceId
 *   Unique identifier for the target device.
 * @var bl_unlock_boot_metadata_t::maxPayloadSize
 *   Maximum allowed payload size for bootloader write operations.
 * @var bl_unlock_boot_metadata_t::commandHeader
 *   Command header information for the bootloader write commands.
 */
typedef struct
{
    bl_block_header_t blockHeader;
    uint8_t imageVersionPatch;
    uint8_t imageVersionMinor;
    uint8_t imageVersionMajor;
    uint32_t deviceId;
    uint16_t maxPayloadSize;
    bl_command_header_t commandHeader;
} bl_unlock_boot_metadata_t;

/**
 * @ingroup mdfu_client_32bit
 * @brief Buffer used for write operations.
 *
 * This static buffer is allocated to hold data for write operations.
 * The size of the buffer is determined by BL_WRITE_BYTE_LENGTH divided by 4,
 * to accommodate 32-bit (uint32_t) data elements.
 */
static uint32_t writeBuffer[BL_WRITE_BYTE_LENGTH / 4U];

/**
 * @ingroup mdfu_client_32bit
 * @brief Flag for indicating if the meta data has been validated in the update process.
 */
static bool bootloaderCoreUnlocked = false;
/**
 * @ingroup mdfu_client_32bit
 * @brief Unlocks the bootloader processor using the provided buffer.
 *
 * This function attempts to unlock the bootloader processor by processing
 * the meta data found at the data pointer.
 *
 * @param [in] bufferPtr Pointer to a buffer containing meta data
 * @return @ref BL_PASS - Bootloader metadata block has been validated and the core memory functions can now be used
 * @return @ref BL_ERROR_VERIFICATION_FAIL - Invalid data was found in the metadata block and core memory functions remain disabled
 * @return @ref BL_FAIL - Metadata validation failed unexpectedly
 */
static bl_result_t BootloaderProcessorUnlock(uint8_t * bufferPtr);
/**
 * @ingroup mdfu_client_32bit
 * @brief Erases the entire area used to download the image data.
 *
 * This function will erase the entire image area if there is only one image.
 * In build configurations where there is a staging area this function will erase the staging area only.
 *
 * @param[in] startAddress - Start address of the area used to download the image data
 * @return None
 */
static void DownloadAreaErase(uint32_t startAddress);

bl_result_t BL_BootCommandProcess(uint8_t * commandBuffer, uint16_t commandLength)
{
    bl_result_t bootCommandStatus = BL_ERROR_UNKNOWN_COMMAND;

    bl_block_header_t blockHeader;
    (void) memcpy((void *)&blockHeader.blockLength, (const void *) & commandBuffer[0], (size_t)2U);
    (void) memcpy((void *)&blockHeader.blockType, (const void *) & commandBuffer[2U], (size_t)1U);

    // Switch on the bootloader command and execute the logic needed
    switch (blockHeader.blockType)
    {
    case UNLOCK_BOOTLOADER:
        bootCommandStatus = BootloaderProcessorUnlock(commandBuffer);
        break;
    case WRITE_FLASH:
        if (bootloaderCoreUnlocked)
        {
            // Copy out the data buffer into a defined packet structure
            bl_command_header_t commandHeader;
            (void) memcpy((void *)&commandHeader.startAddress, (const void *) & commandBuffer[BL_BLOCK_HEADER_SIZE], (size_t)4U);
            /*
            Calculate the offset needed for the download location. *Valuable when multiple image locations are defined*
            This mathematical corelation is consistent as long as the execution image is located at the lower addresses
            and all image spaces are the same size.
             */
            uint32_t stagingAreaOffset = (uint32_t) (BL_STAGING_IMAGE_START - BL_APPLICATION_START_ADDRESS);

            if ((uint32_t) (commandHeader.startAddress + stagingAreaOffset) >= (uint32_t) BL_STAGING_IMAGE_START)
            {
                (void) memcpy((void *)&writeBuffer[0], (const void *)&commandBuffer[BL_COMMAND_HEADER_SIZE + BL_BLOCK_HEADER_SIZE], (size_t)((size_t)commandLength - (size_t)BL_COMMAND_HEADER_SIZE - (size_t)BL_BLOCK_HEADER_SIZE));

                NVMCTRL_RegionUnlock(commandHeader.startAddress + stagingAreaOffset);
                while (NVMCTRL_IsBusy() == true)
                {
                }

                // Write all pages of the row size                
                bool writeStatus = NVMCTRL_FlashWrite(&writeBuffer[0], commandHeader.startAddress + stagingAreaOffset, NVMCTRL_FLASH_PAGESIZE);

                while (NVMCTRL_IsBusy() == true)
                {
                }

                NVMCTRL_RegionLock(commandHeader.startAddress + stagingAreaOffset);
                while (NVMCTRL_IsBusy())
                {
                }
                bootCommandStatus = (writeStatus == true) ? BL_PASS : BL_ERROR_COMMAND_PROCESSING;
            }
            else
            {
                bootCommandStatus = BL_ERROR_ADDRESS_OUT_OF_RANGE;
            }
        }
        
        break;
    default:
        bootCommandStatus = BL_ERROR_UNKNOWN_COMMAND;
        break;
    }

    return bootCommandStatus;
}

void BL_ApplicationStart(void)
{
    uint32_t msp = *(uint32_t *) (BL_APPLICATION_START_ADDRESS);
    uint32_t reset_vector = *(uint32_t *) (BL_APPLICATION_START_ADDRESS + 4U);

    if (msp == 0xffffffffU)
    {
        return;
    }

    /* Do custom deinitialize sequence to free any resources acquired by Bootloader */

    __set_MSP(msp);
    ASM_VECTOR;
}

bl_result_t BL_Initialize(void)
{
    bl_result_t initResult = BL_PASS;

    // Prevent the core memory functions from executing until the meta-data has been validated
    bootloaderCoreUnlocked = false;

    return initResult;
}

static bl_result_t BootloaderProcessorUnlock(uint8_t * bufferPtr)
{
    bl_result_t commandStatus = BL_FAIL;

    bl_unlock_boot_metadata_t metadataPacket;
    (void) memcpy((void *)&metadataPacket.blockHeader, (const void *) &bufferPtr[0], (size_t)3U);
    (void) memcpy((void *)&metadataPacket.imageVersionPatch, (const void *) &bufferPtr[3U], (size_t)1U);
    (void) memcpy((void *)&metadataPacket.imageVersionMinor, (const void *) &bufferPtr[4U], (size_t)1U);
    (void) memcpy((void *)&metadataPacket.imageVersionMajor, (const void *) &bufferPtr[5U], (size_t)1U);
    (void) memcpy((void *)&metadataPacket.deviceId, (const void *) &bufferPtr[6U], (size_t)4U);
    (void) memcpy((void *)&metadataPacket.maxPayloadSize, (const void *) &bufferPtr[10U], (size_t)2U);
    (void) memcpy((void *)&metadataPacket.commandHeader, (const void *) &bufferPtr[12U], (size_t)BL_COMMAND_HEADER_SIZE);

    /**
     * Verify the file format major version. The core must use the exact major version of the file format.
     *  - If the file has a lower major version then there are likely
     * missing data elements that are required by the running version of the core.
     * - If the file has a larger major version then the data elements in the new
     * file format have likely shifted around and may not function as intended, so it
     * is more stable to reject it, in this case.
     *
     * <u>Note:</u> We must always increase the major version of the file anytime the metadata block changes or a new block is added
     * to the file definition, that is a requirement of the core firmware in order to perform an update.
     */
    if ((metadataPacket.imageVersionMajor) != (uint8_t) BL_IMAGE_FORMAT_MAJOR_VERSION)
    {
        commandStatus = BL_ERROR_VERIFICATION_FAIL;
    }
        /*
         * Verify the minor version. The minor version must be less than or equal to the configured version.
         * - If the image minor version is less than the configured version then all block types will be valid in the new implementation.
         * - If the image minor version is larger than the current configured version that would indicate that a new block type has been added
         * to the file format being uploaded and the core may encounter an unknown block that could cause a failed update.
         *
         * <u>Note:</u> We must always increase the minor version when a new block is added to the file definition that does not change
         * the behavior of any already defined block types and is not a required operation in the core firmware. If any new blocks
         * are added to the file definition that break these two rules it should be added as a major change.
         */
    else if (metadataPacket.imageVersionMinor > (uint8_t) BL_IMAGE_FORMAT_MINOR_VERSION)
    {
        commandStatus = BL_ERROR_VERIFICATION_FAIL;
    }
    else 
    {
        // Do nothing
    }

    // Read device information from memory
    uint32_t deviceId = 0x0U;
    (void)NVMCTRL_Read(&deviceId, 4U, BL_DEVICE_ID_START_ADDRESS_U);

    // Mask the revision number to obtain the device id
    deviceId &= ~(0xF00U);

    // Compare the device id of the current hardware and the expected id from the file data
    if (deviceId != (uint32_t) metadataPacket.deviceId)
    {
        commandStatus = BL_ERROR_VERIFICATION_FAIL;
    }
    // Read and compare write size
    if (metadataPacket.maxPayloadSize != BL_WRITE_BYTE_LENGTH)
    {
        commandStatus = BL_ERROR_VERIFICATION_FAIL;
    }
    // Compare the given start of app to the APPLICATION_START_ADDRESS and handle
    if (metadataPacket.commandHeader.startAddress != (uint32_t) BL_APPLICATION_START_ADDRESS)
    {
        commandStatus = BL_ERROR_VERIFICATION_FAIL;
    }

    if (commandStatus != BL_ERROR_VERIFICATION_FAIL)
    {
        bootloaderCoreUnlocked = true;
        commandStatus = BL_PASS;
        DownloadAreaErase(BL_STAGING_IMAGE_START);
    }

    return commandStatus;
}

static void DownloadAreaErase(uint32_t startAddress)
{
    uint32_t address;
    address = (uint32_t) startAddress;

    while (address < BL_STAGING_IMAGE_END)
    {
        NVMCTRL_RegionUnlock(address);
        while (NVMCTRL_IsBusy() == true)
        {
        }

        (void)NVMCTRL_PageErase(address);
        while (NVMCTRL_IsBusy() == true)
        {
        }

        NVMCTRL_RegionLock(address);
        while (NVMCTRL_IsBusy() == true)
        {
        }

        address += NVMCTRL_FLASH_PAGESIZE;
    }
}

bool BL_CheckForcedEntry(void)
{
    uint32_t * entryFlagArray = (uint32_t *) (BL_SOFTWARE_ENTRY_PATTERN_START_ADDRESS);
    if (
            (entryFlagArray[0] == BL_SOFTWARE_ENTRY_PATTERN)
            && (entryFlagArray[1] == BL_SOFTWARE_ENTRY_PATTERN)
            && (entryFlagArray[2] == BL_SOFTWARE_ENTRY_PATTERN)
            && (entryFlagArray[3] == BL_SOFTWARE_ENTRY_PATTERN)
        )
    {
        entryFlagArray[0] = 0U;
        return true;
    }

    return false;
}
