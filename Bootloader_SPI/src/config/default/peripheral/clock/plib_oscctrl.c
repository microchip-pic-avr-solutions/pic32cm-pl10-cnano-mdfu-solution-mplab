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
* @file plib_oscctrl.c
* @brief Oscillator Controller Peripheral Library (PLIB) implementation.
*
* @details This file provides functions to configure, control, and monitor the 
* internal high-frequency oscillator (OSCHF) using the OSCCTRL hardware module. 
* It includes register definitions, interrupt and event handling, frequency 
* selection, autotune, on-demand operation, and write protection mechanisms.
*******************************************************************************/


#include "plib_oscctrl.h"

static const uint32_t oscctrl_freq_table[] = {
    [OSCCTRL_OSCHF_FREQ_1M]  = 1000000UL,
    [OSCCTRL_OSCHF_FREQ_2M]  = 2000000UL,
    [OSCCTRL_OSCHF_FREQ_3M]  = 3000000UL,
    [OSCCTRL_OSCHF_FREQ_4M]  = 4000000UL,
    [OSCCTRL_OSCHF_FREQ_8M]  = 8000000UL,
    [OSCCTRL_OSCHF_FREQ_12M] = 12000000UL,
    [OSCCTRL_OSCHF_FREQ_16M] = 16000000UL,
    [OSCCTRL_OSCHF_FREQ_20M] = 20000000UL,
    [OSCCTRL_OSCHF_FREQ_24M] = 24000000UL
};

/* Callback for OSCHF ready event */
static OSCCTRL_OSCHF_READY_CALLBACK oscctrl_ready_callback = NULL;


void OSCCTRL_OSCHF_SetFrequency(OSCCTRL_OSCHF_FREQ freq_sel)
{
    OSCCTRL_REGS->OSCCTRL_OSCHFCTRL = (OSCCTRL_REGS->OSCCTRL_OSCHFCTRL & ~OSCCTRL_OSCHFCTRL_FRQSEL_Msk) |
                                        OSCCTRL_OSCHFCTRL_FRQSEL(freq_sel);
}

uint32_t OSCCTRL_OSCHF_GetFrequency(void)
{
    OSCCTRL_OSCHF_FREQ frequency_tag = ((OSCCTRL_REGS->OSCCTRL_OSCHFCTRL & OSCCTRL_OSCHFCTRL_FRQSEL_Msk) >> OSCCTRL_OSCHFCTRL_FRQSEL_Pos);
    return oscctrl_freq_table[frequency_tag];
}

void OSCCTRL_OSCHF_EnableAutotune(void)
{
    OSCCTRL_REGS->OSCCTRL_OSCHFCTRL |= OSCCTRL_OSCHFCTRL_AUTOTUNE_Msk;
}

void OSCCTRL_OSCHF_DisableAutotune(void)
{
    OSCCTRL_REGS->OSCCTRL_OSCHFCTRL &= ~OSCCTRL_OSCHFCTRL_AUTOTUNE_Msk;
}

bool OSCCTRL_OSCHF_AutotuneIsEnabled(void)
{
    return ((OSCCTRL_REGS->OSCCTRL_OSCHFCTRL & OSCCTRL_OSCHFCTRL_AUTOTUNE_Msk) != 0U);
}

void OSCCTRL_OSCHF_EnableOnDemand()
{

    OSCCTRL_REGS->OSCCTRL_OSCHFCTRL |= OSCCTRL_OSCHFCTRL_ONDEMAND_Msk;
}

void OSCCTRL_OSCHF_DisableOnDemand()
{
    OSCCTRL_REGS->OSCCTRL_OSCHFCTRL &= ~OSCCTRL_OSCHFCTRL_ONDEMAND_Msk;

}

bool OSCCTRL_OSCHF_OnDemandIsEnabled(void)
{
    return ((OSCCTRL_REGS->OSCCTRL_OSCHFCTRL & OSCCTRL_OSCHFCTRL_ONDEMAND_Msk) != 0U);
}

void OSCCTRL_EnableWriteProtection(void)
{
    OSCCTRL_REGS->OSCCTRL_WPCTRL = OSCCTRL_WPCTRL_WPEN_Msk | (((uint32_t)OSCCTRL_WP_KEY << OSCCTRL_WPCTRL_WPKEY_Pos));
}

void OSCCTRL_DisableWriteProtection(void)
{
    OSCCTRL_REGS->OSCCTRL_WPCTRL = (((uint32_t)OSCCTRL_WP_KEY << OSCCTRL_WPCTRL_WPKEY_Pos));
}

bool OSCCTRL_WriteProtectionIsEnabled(void)
{
    return ((OSCCTRL_REGS->OSCCTRL_WPCTRL & OSCCTRL_WPCTRL_WPEN_Msk) != 0U);
}

void OSCCTRL_WPCTRL_EnableWriteLock(void)
{
    OSCCTRL_REGS->OSCCTRL_WPCTRL = (OSCCTRL_REGS->OSCCTRL_WPCTRL & OSCCTRL_WPCTRL_WPEN_Msk) 
                                    | (OSCCTRL_WPCTRL_WPLCK_Msk) 
                                    | (((uint32_t)OSCCTRL_WP_KEY << OSCCTRL_WPCTRL_WPKEY_Pos));
}

bool OSCCTRL_WPCTRL_WriteLockIsEnabled(void)
{
    return ((OSCCTRL_REGS->OSCCTRL_WPCTRL & OSCCTRL_WPCTRL_WPLCK_Msk) != 0U);
}

void OSCCTRL_OSCHF_SetManualTune(uint8_t tune_value)
{
    OSCCTRL_REGS->OSCCTRL_OSCHFTUNE = (OSCCTRL_REGS->OSCCTRL_OSCHFTUNE & ~OSCCTRL_OSCHFTUNE_TUNE_Msk) |
                             OSCCTRL_OSCHFTUNE_TUNE(tune_value);
}

uint8_t OSCCTRL_OSCHF_GetFrequencyTune(void)
{
    return (uint8_t)((OSCCTRL_REGS->OSCCTRL_OSCHFTUNE & OSCCTRL_OSCHFTUNE_TUNE_Msk) >> OSCCTRL_OSCHFTUNE_TUNE_Pos);
}

bool OSCCTRL_OSCHF_IsReady(void)
{
    return ((OSCCTRL_REGS->OSCCTRL_STATUS & OSCCTRL_STATUS_OSCHFRDY_Msk) != 0U);
}

void OSCCTRL_OSCHF_EnableReadyInterrupt(void)
{
    OSCCTRL_REGS->OSCCTRL_INTENSET = OSCCTRL_INTENSET_OSCHFRDY_Msk;
}

bool OSCCTRL_OSCHF_ReadyInterruptIsEnabled(void)
{
    return ((OSCCTRL_REGS->OSCCTRL_INTENSET & OSCCTRL_INTENSET_OSCHFRDY_Msk) != 0U);
}

void OSCCTRL_OSCHF_DisableReadyInterrupt(void)
{
    OSCCTRL_REGS->OSCCTRL_INTENCLR = OSCCTRL_INTENCLR_OSCHFRDY_Msk;
}

bool OSCCTRL_OSCHF_InterruptFlagIsSet(void)
{
    return ((OSCCTRL_REGS->OSCCTRL_INTFLAG & OSCCTRL_INTFLAG_OSCHFRDY_Msk) != 0U);
}

void OSCCTRL_OSCHF_ClearInterruptFlag(void)
{
    OSCCTRL_REGS->OSCCTRL_INTFLAG = OSCCTRL_INTFLAG_OSCHFRDY_Msk;
}

void OSCCTRL_OSCHF_SetReadyInterruptFlag(void)
{
    OSCCTRL_REGS->OSCCTRL_INTFLAGSET = OSCCTRL_INTFLAGSET_OSCHFRDY_Msk;
}

void OSCCTRL_OSCHF_SetReadyCallbackHandler(OSCCTRL_OSCHF_READY_CALLBACK callback)
{
    oscctrl_ready_callback = callback;
}

void OSCCTRL_Handler(void)
{
    if ((OSCCTRL_REGS->OSCCTRL_INTFLAG & OSCCTRL_INTFLAG_OSCHFRDY_Msk) != 0U)
    {
        /* Clear the interrupt flag */
        OSCCTRL_REGS->OSCCTRL_INTFLAG = OSCCTRL_INTFLAG_OSCHFRDY_Msk;

        if (oscctrl_ready_callback != NULL)
        {
            oscctrl_ready_callback();
        }
    }
}

void OSCCTRL_OSCHF_Initialize(void)
{
    NVIC_SetVector(OSCCTRL_IRQn, (uint32_t)OSCCTRL_Handler);
    NVIC_EnableIRQ(OSCCTRL_IRQn);
}

