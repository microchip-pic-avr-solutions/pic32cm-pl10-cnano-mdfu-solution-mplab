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
#include "../../../peripheral/nvmctrl/plib_nvmctrl.h"
#include "../../../peripheral/dmac/plib_dmac.h"
#include "bl_result_type.h"

/**
 * @ingroup mdfu_client_32bit
 * @brief Calculates the CRC32 checksum for a specified memory region.
 *
 * This function computes the CRC32 checksum for given range of memory starting
 * at the given address and spanning the specified length. The result is
 * stored in the provided CRC seed pointer. This function utilized the DSU peripheral.
 *
 * @param [in] startAddress - The starting address of the memory block to calculate the CRC for
 * @param [in] length - The length of the memory block in bytes
 * @param [in,out] crc - Pointer to a variable where the calculated CRC32 checksum will be stored. This variable must
 * be passed to the function with the CRC seed value set at the pointer.
 * @return None
 */
static uint32_t CRC32_Calculate(uint32_t startAddress, uint32_t length);

/**
 * @ingroup mdfu_client_32bit
 * @brief Validates the CRC32 checksum for a specified memory region.
 *
 * This function checks the CRC32 checksum of a memory block against a
 * stored CRC value to verify data integrity and then returns a value indicating
 * whether the validation was successful or not.
 *
 * @param [in] startAddress - The starting address of the memory block to validate
 * @param [in] length - The length of the memory block in bytes
 * @param [in] crcAddress - The address where the expected CRC32 checksum is stored
 * @return @ref BL_PASS - Bootloader verified the application image with no errors \n
 * @return @ref BL_FAIL - Bootloader encountered an error and failed unexpectedly \n
 * @return @ref BL_ERROR_VERIFICATION_FAIL - Bootloader image verification failed \n
 */
static bl_result_t CRC32_Validate(uint32_t startAddress, uint32_t length, uint32_t crcAddress);

static uint32_t CRC32_Calculate(uint32_t startAddress, uint32_t length)
{
    DMAC_CRC_SETUP CRCSetup = {0};
    CRCSetup.polynomial_type = DMAC_CRC_TYPE_32;
    CRCSetup.seed = 0xFFFFFFFFU;
    uint32_t crc_32 = 0U; 
    crc_32 = DMAC_CRCCalculate((uint32_t *)startAddress,length, CRCSetup);
    return ~crc_32;
}

static bl_result_t CRC32_Validate(uint32_t startAddress, uint32_t length, uint32_t refAddress)
{
    bl_result_t result = BL_FAIL;
    uint32_t crc = 0xFFFFFFFFU;
    crc = CRC32_Calculate(startAddress, length);
    volatile uint32_t myCrcVal = *( uint32_t *)(refAddress);
    
    if (myCrcVal != crc)
    {
        result = BL_ERROR_VERIFICATION_FAIL;
    }
    else
    {
        result = BL_PASS;
            
    }
    return result;
}

bl_result_t BL_ImageVerify(void)
{
    // Verify the app area
    bl_result_t verificationStatus = CRC32_Validate(BL_APPLICATION_START_ADDRESS, (uint32_t)(BL_IMAGE_PARTITION_SIZE - BL_HASH_DATA_SIZE), 0xC00FFFCU);

    return verificationStatus;
}