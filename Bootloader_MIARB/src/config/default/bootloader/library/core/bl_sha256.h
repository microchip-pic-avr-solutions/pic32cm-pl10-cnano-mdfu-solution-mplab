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
 * @file        bl_sha256_pic32cm.h
 * @ingroup     mdfu_client_core_pic32cm
 *
 * @brief       This header file provides the API prototypes of the SHA256 cryptographic hash algorithm for PIC32CM M0
 */
 
#ifndef BL_SHA256_PIC32CM_H
#define BL_SHA256_PIC32CM_H
 
#include <stdint.h>
 
/**
 * @ingroup mdfu_client_pic32cm
 * @brief This routine calculates the SHA256 hash over a region in Flash memory. The calculation covers the range from startAddress to endAddress, inclusive.
 * @param startAddress - The start address of the memory range for hash calculation
 * @param endAddress - The end address of the memory range for hash calculation (inclusive)
 * @param resultBuffer - A buffer to store the calculated hash digest (32 bytes for SHA-256)
 * @return none
 */
void SHA256(const uint32_t startAddress, const uint32_t endAddress, uint8_t* resultBuffer);
 
#endif // BL_SHA256_PIC32CM_H
