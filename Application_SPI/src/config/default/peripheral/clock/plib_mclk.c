/********************************************************************************
* Copyright © 2025 Microchip Technology Inc. and its subsidiaries.
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
/******************************************************************************
* @file plib_mclk.c
* @brief Main Clock (MCLK) Controller Peripheral Library Implementation.
*
* @details This file provides the Implementation of the Main Clock (MCLK) 
* peripheral configuration functions. Including functions to initialize the 
* MCLK, configure CPU clock division, and enable/disable. AHB and APB clocks 
* for various modules. It also provides interrupt handling and callback 
* registration for the Clock Ready event.
*******************************************************************************/

#include "plib_mclk.h"

/* Internal callback pointer for CKRDY event */
static MCLK_CALLBACK mclk_callback = (MCLK_CALLBACK)0;


MCLK_CPU_CLOCK_DIVIDER MCLK_GetCPUClockDivider(void)
{
    return (MCLK_CPU_CLOCK_DIVIDER)MCLK_REGS->MCLK_CPUDIV;
}

void MCLK_SetCPUClockDivider(MCLK_CPU_CLOCK_DIVIDER div)
{
    MCLK_REGS->MCLK_CPUDIV = div;
}

void MCLK_EnableAHBClock(MCLK_AHB_MODULE module)
{
    MCLK_REGS->MCLK_AHBMASK |= module;
}

void MCLK_DisableAHBClock(MCLK_AHB_MODULE module)
{ 
    MCLK_REGS->MCLK_AHBMASK &= ~module;
}

void MCLK_EnableAPBAClock(MCLK_APBA_MODULE module)
{
    MCLK_REGS->MCLK_APBAMASK |= module;
}

void MCLK_EnableAPBBClock(MCLK_APBB_MODULE module)
{
    MCLK_REGS->MCLK_APBBMASK |= module;
}

void MCLK_EnableAPBCClock(MCLK_APBC_MODULE module)
{
    MCLK_REGS->MCLK_APBCMASK |= module;
}

#if defined(MCLK_APBDMASK_Msk)
void MCLK_EnableAPBDClock(MCLK_APBD_MODULE module)
{
    MCLK_REGS->MCLK_APBDMASK |= module;
}
#endif
    
void MCLK_DisableAPBAClock(MCLK_APBA_MODULE module)
{
    MCLK_REGS->MCLK_APBAMASK &= ~module;
}

void MCLK_DisableAPBBClock(MCLK_APBB_MODULE module)
{
    MCLK_REGS->MCLK_APBBMASK &= ~module;
}

void MCLK_DisableAPBCClock(MCLK_APBC_MODULE module)
{
    MCLK_REGS->MCLK_APBCMASK &= ~module;
}

#if defined(MCLK_APBDMASK_Msk)
void MCLK_DisableAPBDClock(MCLK_APBD_MODULE module)
{
    MCLK_REGS->MCLK_APBDMASK &= ~module;
}
#endif

bool MCLK_ClockIsReady(void)
{
    return ((MCLK_REGS->MCLK_INTFLAG & MCLK_INTFLAG_CKRDY_Msk) != 0U);
}

void MCLK_EnableClockReadyInterrupt(void)
{
    MCLK_REGS->MCLK_INTENSET = MCLK_INTENSET_CKRDY_Msk;
}

void MCLK_DisableClockReadyInterrupt(void)
{
    MCLK_REGS->MCLK_INTENCLR = MCLK_INTENCLR_CKRDY_Msk;
}

void MCLK_ClearClockReadyFlag(void)
{
    MCLK_REGS->MCLK_INTFLAG = MCLK_INTFLAG_CKRDY_Msk;
}

void MCLK_SetCallbackHandler(MCLK_CALLBACK callback)
{
    mclk_callback = callback;
}

void MCLK_Handler(void)
{
    if ((MCLK_REGS->MCLK_INTFLAG & MCLK_INTFLAG_CKRDY_Msk) != 0U)
    {
        if (mclk_callback != (MCLK_CALLBACK)0)
        {
            mclk_callback();
        }

        MCLK_REGS->MCLK_INTFLAG = MCLK_INTFLAG_CKRDY_Msk;
    }
}

void MCLK_Initialize(void)
{
    NVIC_SetVector(MCLK_IRQn, (uint32_t)MCLK_Handler);
    NVIC_EnableIRQ(MCLK_IRQn);
}

