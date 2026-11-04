/*******************************************************************************
  Non-Volatile Memory Controller(NVMCTRL) PLIB.

  Company:
    Microchip Technology Inc.

  File Name:
    plib_nvmctrl.h

  Summary:
    Interface definition of NVMCTRL Plib.

  Description:
    This file defines the interface for the NVMCTRL Plib.
    It allows user to Program, Erase and lock the on-chip Non Volatile Flash
    Memory.
*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2018 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/
// DOM-IGNORE-END

#ifndef PLIB_NVMCTRL_H
#define PLIB_NVMCTRL_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "device.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// DOM-IGNORE-BEGIN
#ifdef __cplusplus // Provide C++ Compatibility
 extern "C" {
#endif

// DOM-IGNORE-END

#define NVMCTRL_FLASH_START_ADDRESS        (0x0C000000U)
#define NVMCTRL_FLASH_PAGESIZE             (512U)
#define NVMCTRL_FLASH_ROWSIZE              (2048U)

/* Write-Protect Key */
#define NVMCTRL_WPCTRL_KEY		 ( 0x4E564DU )

/* No error */
#define   NVMCTRL_ERROR_NONE     ( 0x0U )

/* NVMCTRL invalid commands and/or bad keywords error */
#define    NVMCTRL_ERROR_PROG    ( 0x4U )

/* NVMCTRL lock error */
#define   NVMCTRL_ERROR_LOCK     ( 0x8U )

typedef uint32_t NVMCTRL_ERROR;


typedef enum
{
    FLASH_ERASE_2_PAGE = 2,
    FLASH_ERASE_4_PAGE = 4,
    FLASH_ERASE_8_PAGE = 8,
    FLASH_ERASE_16_PAGE = 16,
    FLASH_ERASE_32_PAGE = 32

} FLASH_ERASE;


/* void NVMCTRL_Initialize(void); */

bool NVMCTRL_Read( uint32_t *data, uint32_t length, const uint32_t address );

bool NVMCTRL_FlashWrite( uint32_t *data, const uint32_t address, uint32_t size );

bool NVMCTRL_PageErase( uint32_t address );

bool NVMCTRL_PagesErase( uint32_t address, FLASH_ERASE num_pages );

bool NVMCTRL_IsBusy( void );

void NVMCTRL_RegionLock (uint32_t address);

void NVMCTRL_RegionUnlock (uint32_t address);

void NVMCTRL_WriteProtect_enable( void );

void NVMCTRL_WriteProtect_disable( void );

void NVMCTRL_WriteProtect_Writelock( void );

void NVMCTRL_CMD_Clear( void );

bool NVMCTRL_BOOTCFG_FlashErase( uint32_t address );

bool NVMCTRL_BOOTCFG_FlashWrite( uint32_t *data, const uint32_t address, uint32_t size );

NVMCTRL_ERROR NVMCTRL_ErrorGet( void );


uint32_t NVMCTRL_InterruptFlagGet(void);

// DOM-IGNORE-BEGIN
#ifdef __cplusplus // Provide C++ Compatibility
}
#endif
// DOM-IGNORE-END
#endif // PLIB_NVMCTRL_H
