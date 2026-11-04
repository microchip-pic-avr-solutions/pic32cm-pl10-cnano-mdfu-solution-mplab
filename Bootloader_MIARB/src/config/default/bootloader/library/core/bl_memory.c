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
 * @ingroup bl_memory
 * @brief   This file contains implementation for the helper functions used with the NVM peripheral driver
 *
 */

#include "bl_memory.h"

// Static Buffer Declared to Assist in writing blocks of any length upto 1 page
/* cppcheck-suppress misra-c2012-8.9 */
static uint32_t writeBuffer[NVMCTRL_FLASH_PAGESIZE];


bl_mem_result_t BL_FlashCopy(uint32_t srcAddress, uint32_t destAddress, size_t length)
{
    bl_mem_result_t result = BL_MEM_FAIL;
    uint32_t destEndAddress = (uint32_t)(destAddress + length);
    uint32_t srcEndAddress = (uint32_t)(srcAddress + length);
    uint32_t flashEndAddress = 0x0C010000U;
    uint8_t totalPages = 4U;

    // Check if the given source and destination addresses are outside Flash memory range
    if (
            (srcAddress < 0x0C000000U) ||
            (destAddress < 0x0C000000U)
            )
    {
        result = BL_MEM_INVALID_ARG;
    }
        // Check if the given source and destination regions are overlapping
    else if (
            (srcAddress == destAddress) ||
            ((srcEndAddress > destAddress) && (srcEndAddress < destEndAddress)) ||
            ((destEndAddress > srcAddress) && (destEndAddress < srcEndAddress))
            )
    {
        result = BL_MEM_INVALID_ARG;
    }
        // Check if the length is invalid
    else if (
            (length <= (size_t) 0) ||
            (srcEndAddress > flashEndAddress) ||
            (destEndAddress > flashEndAddress)
            )
    {
        result = BL_MEM_INVALID_ARG;
    }
    else
    {
        // Read the data into the static buffer using the BL_FlashRead.
        result = NVMCTRL_Read(&writeBuffer[0], length, srcAddress);
        
        while (true == NVMCTRL_IsBusy())
        {

        }

        if (BL_MEM_PASS == result)
        {
            for (uint8_t pageNum = 0U; pageNum < totalPages; pageNum++)
            {
                uint32_t pageAddress = destAddress + ((uint32_t)pageNum * (uint32_t)NVMCTRL_FLASH_PAGESIZE);

                NVMCTRL_RegionUnlock(pageAddress);
                while (true == NVMCTRL_IsBusy())
                {
                }

                (void)NVMCTRL_PageErase(pageAddress);
                while (true == NVMCTRL_IsBusy())
                {
                }

                NVMCTRL_RegionLock(pageAddress);
                while (true == NVMCTRL_IsBusy())
                {
                }
            }
            
            for(uint8_t pageNum = 0U; pageNum < totalPages; pageNum++)
            {
                NVMCTRL_RegionUnlock(destAddress);
                
                while(true == NVMCTRL_IsBusy())
                {
    
                }
                
                (void)NVMCTRL_FlashWrite(&writeBuffer[(((uint32_t)pageNum * (uint32_t)NVMCTRL_FLASH_PAGESIZE)) / 4U], destAddress + ((uint32_t)pageNum * (uint32_t)NVMCTRL_FLASH_PAGESIZE), NVMCTRL_FLASH_PAGESIZE);
                
                while(true == NVMCTRL_IsBusy())
                {
    
                }
                NVMCTRL_RegionLock(destAddress);
                
                while(true == NVMCTRL_IsBusy())
                {
    
                }
            }
            
            result = BL_MEM_PASS;
        }
    }

    return result;
}