/*******************************************************************************
  Non-Volatile Memory Controller(NVMCTRL) PLIB.

  Company:
    Microchip Technology Inc.

  File Name:
    plib_nvmctrl.c

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

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <string.h>
#include "plib_nvmctrl.h"
#include "interrupts.h"

// *****************************************************************************
// *****************************************************************************
// Section: NVMCTRL Implementation
// *****************************************************************************
// *****************************************************************************


bool NVMCTRL_Read( uint32_t *data, uint32_t length, const uint32_t address )
{
    uint32_t *paddress_read = (uint32_t *)address;
    (void) memcpy(data, paddress_read, length);
    return true;
}

bool NVMCTRL_FlashWrite( uint32_t *data, const uint32_t address, uint32_t size )
{
    uint32_t i;
    uint32_t * paddress = (uint32_t *)address;

    NVMCTRL_CMD_Clear();
    
    /* Set address and command */
    NVMCTRL_REGS->NVMCTRL_ADDR = address;

    NVMCTRL_REGS->NVMCTRL_CTRLB = NVMCTRL_CTRLB_CMD_FLWR_Val | NVMCTRL_CTRLB_CMDEX_KEY;

    /* writing 32-bit data into the given address */
    for (i = 0U; i < (size/4U); i++)
    {
        *paddress = data[i];
         paddress++;
    }

    while(NVMCTRL_IsBusy())
    {
        /* Waiting for Ready state */
    }
    
    return true;
}

bool NVMCTRL_PageErase( uint32_t address )
{
    NVMCTRL_CMD_Clear();
    
    /* Set address and command */
    NVMCTRL_REGS->NVMCTRL_ADDR = address;

    NVMCTRL_REGS->NVMCTRL_CTRLB = NVMCTRL_CTRLB_CMD_FLPER_Val | NVMCTRL_CTRLB_CMDEX_KEY;
    
    while(NVMCTRL_IsBusy())
    {
        /* Waiting for Ready state */
    }
    
    *((uint32_t *)address) = 0xFFFFFFFFU;
    
    while(NVMCTRL_IsBusy())
    {
        /* Waiting for Ready state */
    }

    return true;
}

bool NVMCTRL_PagesErase(uint32_t address, FLASH_ERASE num_pages)
{
    uint32_t cmd;
	bool status = true;
	
    NVMCTRL_CMD_Clear();
    
    switch (num_pages)
    {
        case FLASH_ERASE_2_PAGE:
            cmd = NVMCTRL_CTRLB_CMD_FLMPER2_Val;
            break;
        case FLASH_ERASE_4_PAGE:
            cmd = NVMCTRL_CTRLB_CMD_FLMPER4_Val;
            break;
        case FLASH_ERASE_8_PAGE:
            cmd = NVMCTRL_CTRLB_CMD_FLMPER8_Val;
            break;
        case FLASH_ERASE_16_PAGE:
            cmd = NVMCTRL_CTRLB_CMD_FLMPER16_Val;
            break;
        case FLASH_ERASE_32_PAGE:
            cmd = NVMCTRL_CTRLB_CMD_FLMPER32_Val;
            break;
        default:
			status = false;  
			break;
    }
	
	if (!status)
	{
		return status;
	}

    /* Set address and command */
    NVMCTRL_REGS->NVMCTRL_ADDR = address;
    
    /* Issue erase command */
    NVMCTRL_REGS->NVMCTRL_CTRLB = cmd | NVMCTRL_CTRLB_CMDEX_KEY;
    
    while(NVMCTRL_IsBusy())
    {
        /* Waiting for Ready state */
    }
    
    *((uint32_t *)address) = 0xFFFFFFFFU;
    
    while(NVMCTRL_IsBusy())
    {
        /* Waiting for Ready state */
    }

    return true;
}

bool NVMCTRL_BOOTCFG_FlashWrite( uint32_t *data, const uint32_t address, uint32_t size )
{
    uint32_t i;
    uint32_t * paddress = (uint32_t *)address;

    NVMCTRL_CMD_Clear();
    
    /* Set address and command */
    NVMCTRL_REGS->NVMCTRL_ADDR = address;

    NVMCTRL_REGS->NVMCTRL_CTRLB = NVMCTRL_CTRLB_CMD_WBOOTCFG_Val | NVMCTRL_CTRLB_CMDEX_KEY;

    /* writing 32-bit data into the given address */
    for (i = 0U; i < (size/4U); i++)
    {
        *paddress = data[i];
         paddress++;
    }

    while(NVMCTRL_IsBusy())
    {
        /* Waiting for Ready state */
    }
    
    return true;
}

bool NVMCTRL_BOOTCFG_FlashErase( uint32_t address )
{
    NVMCTRL_CMD_Clear();
    
    /* Set address and command */
    NVMCTRL_REGS->NVMCTRL_ADDR = address;

    NVMCTRL_REGS->NVMCTRL_CTRLB = NVMCTRL_CTRLB_CMD_EBOOTCFG_Val | NVMCTRL_CTRLB_CMDEX_KEY;
    
    while(NVMCTRL_IsBusy())
    {
        /* Waiting for Ready state */
    }
    
    *((uint32_t *)address) = 0xFFFFFFFFU;

    while(NVMCTRL_IsBusy())
    {
        /* Waiting for Ready state */
    }
    
    return true;
}

NVMCTRL_ERROR NVMCTRL_ErrorGet( void )
{
    volatile uint32_t nvm_error;

    /* Get the error bits set */
    nvm_error = (NVMCTRL_REGS->NVMCTRL_STATUS & (NVMCTRL_STATUS_LOCKE_Msk | NVMCTRL_STATUS_PROGE_Msk));

    /* Clear the error bits in both STATUS and INTFLAG register */
    NVMCTRL_REGS->NVMCTRL_STATUS |= nvm_error;

    NVMCTRL_REGS->NVMCTRL_INTFLAG = NVMCTRL_INTFLAG_ERROR_Msk;

    return (nvm_error);
}

bool NVMCTRL_IsBusy(void)
{
    return ((NVMCTRL_REGS->NVMCTRL_INTFLAG & NVMCTRL_INTFLAG_READY_Msk) == 0U);
}

void NVMCTRL_RegionLock(uint32_t address)
{
    NVMCTRL_CMD_Clear();
    
    /* Set address and command */
    NVMCTRL_REGS->NVMCTRL_ADDR = address;

    NVMCTRL_REGS->NVMCTRL_CTRLB = NVMCTRL_CTRLB_CMD_LR_Val | NVMCTRL_CTRLB_CMDEX_KEY;
    
    while(NVMCTRL_IsBusy())
    {
        /* Waiting for Ready state */
    }
}

void NVMCTRL_RegionUnlock(uint32_t address)
{
    NVMCTRL_CMD_Clear();
    
    /* Set address and command */
    NVMCTRL_REGS->NVMCTRL_ADDR = address;

    NVMCTRL_REGS->NVMCTRL_CTRLB = NVMCTRL_CTRLB_CMD_UR_Val | NVMCTRL_CTRLB_CMDEX_KEY;
    
    while(NVMCTRL_IsBusy())
    {
        /* Waiting for Ready state */
    }
}

void NVMCTRL_CMD_Clear(void)
{
    NVMCTRL_REGS->NVMCTRL_CTRLB = NVMCTRL_CTRLB_CMD_NOCMD | NVMCTRL_CTRLB_CMDEX_KEY;
    while(NVMCTRL_IsBusy())
    {
        /* Waiting for Ready state */
    }
}

void NVMCTRL_WriteProtect_enable( void )
{
    NVMCTRL_REGS->NVMCTRL_WPCTRL |= NVMCTRL_WPCTRL_WPKEY(NVMCTRL_WPCTRL_KEY)| NVMCTRL_WPCTRL_WPEN_Msk;
}

void NVMCTRL_WriteProtect_disable( void )
{
    NVMCTRL_REGS->NVMCTRL_WPCTRL = NVMCTRL_WPCTRL_WPKEY(NVMCTRL_WPCTRL_KEY) & (~NVMCTRL_WPCTRL_WPEN_Msk);
}

void NVMCTRL_WriteProtect_Writelock( void )
{
    NVMCTRL_REGS->NVMCTRL_WPCTRL |= NVMCTRL_WPCTRL_WPKEY(NVMCTRL_WPCTRL_KEY)| NVMCTRL_WPCTRL_WPLCK_Msk;
}

uint32_t NVMCTRL_InterruptFlagGet(void)
{
    uint32_t intFlag =  NVMCTRL_REGS->NVMCTRL_INTFLAG & NVMCTRL_INTFLAG_Msk;
    /* Clear interrupt falg */
    NVMCTRL_REGS->NVMCTRL_INTFLAG = intFlag;
    return intFlag;
}

