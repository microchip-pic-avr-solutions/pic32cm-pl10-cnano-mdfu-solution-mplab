/**
 * � 2025 Microchip Technology Inc. and its subsidiaries.
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
 * @file        bl_sha256.c
 * @ingroup     mdfu_client_8bit_core
 * 
 * @brief       This source file provides the implementation of the SHA256 cryptographic hash algorithm 
 */

#include <stdint.h>
#include <string.h>
#include "bl_sha256.h"
#include "peripheral/nvmctrl/plib_nvmctrl.h"

// Byte-wise rotation and shift macros, with explicit casts and parentheses for precedence
#define SHA2_ROTL(x, n)      (uint32_t)((((uint32_t)(x)) << ((uint32_t)(n))) | (((uint32_t)(x)) >> (32U - ((uint32_t)(n)))))
#define SHA2_ROTR(x, n)      (uint32_t)((((uint32_t)(x)) >> ((uint32_t)(n))) | (((uint32_t)(x)) << (32U - ((uint32_t)(n)))))
#define SHA2_SHR(x, n)       (uint32_t)(((uint32_t)(x)) >> ((uint32_t)(n)))

// SHA256 bit-mixing functions using explicit casts and distinct parameters
#define SHA2_SIG_U0(x)      (uint32_t)(SHA2_ROTR((uint32_t)(x), 2U) ^ SHA2_ROTR((uint32_t)(x), 13U) ^ SHA2_ROTR((uint32_t)(x), 22U))
#define SHA2_SIG_U1(x)      (uint32_t)(SHA2_ROTR((uint32_t)(x), 6U) ^ SHA2_ROTR((uint32_t)(x), 11U) ^ SHA2_ROTR((uint32_t)(x), 25U))
#define SHA2_SIG_L0(x)      (uint32_t)(SHA2_ROTR((uint32_t)(x), 7U) ^ SHA2_ROTR((uint32_t)(x), 18U) ^ SHA2_SHR((uint32_t)(x), 3U))
#define SHA2_SIG_L1(x)      (uint32_t)(SHA2_ROTR((uint32_t)(x), 17U) ^ SHA2_ROTR((uint32_t)(x), 19U) ^ SHA2_SHR((uint32_t)(x), 10U))

// SHA256 choice and majority functions with explicit casts for clarity
#define SHA2_CH(x, y, z)      (uint32_t)(((uint32_t)((x) & (y))) ^ (uint32_t)(((~(x)) & (z))))
#define SHA2_MAJ(x, y, z)     (uint32_t)(((uint32_t)((x) & (y))) ^ (uint32_t)((x) & (z)) ^ (uint32_t)((y) & (z)))

// Block size constants, use 'U' suffix for unsigned and explicit types per MISRA 2023 rule 7.2
#define MAX_BYTES_IN_SHA256_BLOCK           (64U)
#define LAST_BYTE_LOCATION_IN_SHA256_ARRAY  (0x3FU)


static uint32_t hash[8];
static uint32_t totalBytes;
static uint8_t buffer[MAX_BYTES_IN_SHA256_BLOCK];

static void SHA256_OutputData (uint8_t * output, uint32_t value);

static void SHA256_DataAdd (uint8_t *data)
{
    uint32_t a;
    uint32_t b;
    uint32_t c;
    uint32_t d;
    uint32_t e;
    uint32_t f;
    uint32_t g;
    uint32_t h;
    uint8_t i;
    uint32_t t1;
    uint32_t t2;
//    static uint32_t workingBuffer[MAX_BYTES_IN_SHA256_BLOCK];
    uint32_t workingBuffer[MAX_BYTES_IN_SHA256_BLOCK];
    
    static const uint32_t SHA256_K[64] = {
    0x428a2f98U, 0x71374491U, 0xb5c0fbcfU, 0xe9b5dba5U, 0x3956c25bU, 0x59f111f1U, 0x923f82a4U, 0xab1c5ed5U,
    0xd807aa98U, 0x12835b01U, 0x243185beU, 0x550c7dc3U, 0x72be5d74U, 0x80deb1feU, 0x9bdc06a7U, 0xc19bf174U,
    0xe49b69c1U, 0xefbe4786U, 0x0fc19dc6U, 0x240ca1ccU, 0x2de92c6fU, 0x4a7484aaU, 0x5cb0a9dcU, 0x76f988daU,
    0x983e5152U, 0xa831c66dU, 0xb00327c8U, 0xbf597fc7U, 0xc6e00bf3U, 0xd5a79147U, 0x06ca6351U, 0x14292967U,
    0x27b70a85U, 0x2e1b2138U, 0x4d2c6dfcU, 0x53380d13U, 0x650a7354U, 0x766a0abbU, 0x81c2c92eU, 0x92722c85U,
    0xa2bfe8a1U, 0xa81a664bU, 0xc24b8b70U, 0xc76c51a3U, 0xd192e819U, 0xd6990624U, 0xf40e3585U, 0x106aa070U,
    0x19a4c116U, 0x1e376c08U, 0x2748774cU, 0x34b0bcb5U, 0x391c0cb3U, 0x4ed8aa4aU, 0x5b9cca4fU, 0x682e6ff3U,
    0x748f82eeU, 0x78a5636fU, 0x84c87814U, 0x8cc70208U, 0x90befffaU, 0xa4506cebU, 0xbef9a3f7U, 0xc67178f2U
};
    
    for (i = 0U; i < 16U; i++)
    {
        t1 = ((uint32_t)(data[(uint32_t)0])) << 24U;
        t1 |= ((uint32_t)(data[(uint32_t)1])) << 16U;
        t1 |= ((uint32_t)(data[(uint32_t)2])) << 8U;
        t1 |= ((uint32_t)(data[(uint32_t)3]));
        workingBuffer[i] = t1;
        /* coverity[misra_c_2023_rule_17_8_violation] This does not affect API functionality */
        data = &data[4];
    }

    for (i = 16U; i < MAX_BYTES_IN_SHA256_BLOCK; i++)
    {
        uint32_t temp1 = workingBuffer[(uint32_t)i - 2U];
        uint32_t temp2 = workingBuffer[(uint32_t)i - 7U];
        uint32_t temp3 = workingBuffer[(uint32_t)i - 15U];
        uint32_t temp4 = workingBuffer[(uint32_t)i - 16U];
        workingBuffer[i] = (uint32_t)((uint32_t)SHA2_SIG_L1(temp1) + (uint32_t)temp2 + (uint32_t)SHA2_SIG_L0(temp3) + (uint32_t)temp4);
    }

    a = hash[0U];
    b = hash[1U];
    c = hash[2U];
    d = hash[3U];
    e = hash[4U];
    f = hash[5U];
    g = hash[6U];
    h = hash[7U];

    for (i = 0U; i < MAX_BYTES_IN_SHA256_BLOCK; i++)
    {
        t1 = h;
        t1 = (uint32_t)((uint32_t)t1 + SHA2_SIG_U1(e));
        t1 = (uint32_t)((uint32_t)t1 + SHA2_CH(e, f, g));
        t1 = (uint32_t)((uint32_t)t1 + SHA256_K[(uint32_t)i]);
        t1 = (uint32_t)((uint32_t)t1 + workingBuffer[(uint32_t)i]);

        t2 = SHA2_SIG_U0(a);
        t2 = (uint32_t)((uint32_t)t2 + SHA2_MAJ(a, b, c));

        h = g;
        g = f;
        f = e;
        e = d + t1;
        d = c;
        c = b;
        b = a;
        a = t1 + t2;
    }

    hash[0] += a;
    hash[1] += b;
    hash[2] += c;
    hash[3] += d;
    hash[4] += e;
    hash[5] += f;
    hash[6] += g;
    hash[7] += h;
}


static void SHA256_OutputData (uint8_t * output, uint32_t value)
{
    output[0U] = (uint8_t)((value >> 24U) & 0xFFU);
    output[1U] = (uint8_t)((value >> 16U) & 0xFFU);
    output[2U] = (uint8_t)((value >> 8U) & 0xFFU);
    output[3U] = (uint8_t)(value & 0xFFU);
}

static void SHA256_Initialize (void)
{  
    // Initialize context to produce 256-bit digest
    hash[0] = 0x6a09e667U;
    hash[1] = 0xbb67ae85U;
    hash[2] = 0x3c6ef372U;
    hash[3] = 0xa54ff53aU;
    hash[4] = 0x510e527fU;
    hash[5] = 0x9b05688cU;
    hash[6] = 0x1f83d9abU;
    hash[7] = 0x5be0cd19U;
    
    totalBytes = 0U;
}

static void SHA256_Calculate (uint8_t *result)
{
    uint8_t *blockPtr = &buffer[(uint32_t)(totalBytes & (uint32_t)LAST_BYTE_LOCATION_IN_SHA256_ARRAY)];
    uint8_t *endPtr;
    uint8_t i;

    // Append a single 1
    *blockPtr = 0x80U;
    blockPtr++;

    // Pad with 0's until data is a multiple of (512 - 64) bits = 448 bits (56 bytes)
    endPtr = &buffer[56];

    if(blockPtr > endPtr)
    {
        endPtr = &endPtr[8];
        while (blockPtr < endPtr)
        {
            *blockPtr = 0x00U;
            blockPtr++;
        }
        SHA256_DataAdd(buffer);
        blockPtr = buffer;
        /* coverity[misra_c_2023_rule_18_4_violation] This does not affect API functionality */
        endPtr = endPtr - 8;
    }

    // Set the offset to 5 bytes before the end of the block
    endPtr = &endPtr[3];
    while (blockPtr < endPtr)
    {
        *blockPtr = 0x00U;
        blockPtr++;
    }

    /* coverity[misra_c_2023_rule_2_2_violation] Reserved for future use */
    uint64_t bitLen = ((uint64_t)totalBytes) << 3;

    *blockPtr = (uint8_t)((((uint32_t)totalBytes) >> 29U) & 0xFFU);
    blockPtr++;
    *blockPtr = (uint8_t)((((uint32_t)totalBytes) >> 21U) & 0xFFU);
    blockPtr++;
    *blockPtr = (uint8_t)((((uint32_t)totalBytes) >> 13U) & 0xFFU);
    blockPtr++;
    *blockPtr = (uint8_t)((((uint32_t)totalBytes) >> 5U) & 0xFFU);
    blockPtr++;
    *blockPtr = (uint8_t)((((uint32_t)totalBytes) << 3U) & 0xFFU);
    blockPtr++;

    // Calculate a hash on this final block and add it to the sum
    SHA256_DataAdd(buffer);

    // Format the result in big-endian format
    for (i = 0U; i < 7U; i++)
    {
        SHA256_OutputData (&result[(uint32_t)i << 2U], hash[i]);
    }
    SHA256_OutputData (&result[28], hash[7]);
}

void SHA256(const uint32_t startAddress, const uint32_t endAddress, uint8_t* resultBuffer)
{      
    uint32_t byteCount = ((uint32_t)(endAddress) - (uint32_t)(startAddress)) + (uint32_t)1;
    uint32_t currentAddress = startAddress;
    uint32_t blockCount = byteCount >> 6U;
    uint32_t remainingBytes;
    SHA256_Initialize();
    
    while (blockCount > 0U)
    {        
        (void)NVMCTRL_Read((uint32_t *) buffer, MAX_BYTES_IN_SHA256_BLOCK, currentAddress); // 32-bit
        SHA256_DataAdd(buffer);
        currentAddress += MAX_BYTES_IN_SHA256_BLOCK;
        blockCount--;
    }
    remainingBytes = byteCount & 0x3FU;
    (void)memset(buffer, 0U, MAX_BYTES_IN_SHA256_BLOCK);
    // Calculate on the remainder
    if (remainingBytes > 0U)
    {
        (void)NVMCTRL_Read((uint32_t *) buffer, remainingBytes, currentAddress);
    }
    
    totalBytes = byteCount;
    SHA256_Calculate(resultBuffer);
}
