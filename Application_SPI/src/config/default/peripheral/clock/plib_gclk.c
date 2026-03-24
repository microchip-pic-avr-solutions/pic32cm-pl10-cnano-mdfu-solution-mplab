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
* @file plib_gclk.c
* @brief Generic Clock Controller(GCLK) Peripheral Library Source File
*
* @details This file contains the implementation of the Generic Clock (GCLK) 
* peripheral library for configuring and controlling clock generators and 
* peripheral channels on the device. The API provides functions for software reset, 
* generator configuration, division factor, duty cycle improvement, output control, 
* standby operation, and peripheral channel management.
*******************************************************************************/

#include "plib_gclk.h"

static bool GclkPeripheralChannelIsEnabled(GCLK_PERIPHERAL_CHANNEL_ID channel_id)
{
    return ((GCLK_REGS->GCLK_PCHCTRL[channel_id] & GCLK_PCHCTRL_CHEN_Msk) != 0U);
}

static void GclkGeneratorWaitForSync(GCLK_GENERATOR_ID generator_id)
{
    while((GCLK_REGS->GCLK_SYNCBUSY & (GCLK_SYNCBUSY_GENCTRL0_Msk << generator_id)) != 0U)
    {
        // Wait for synchronization
    }
}

void GCLK_Initialize(void)
{

}

bool GCLK_GetGeneratorControlSyncStatus(GCLK_GENERATOR_ID generator_id)
{
    return ((GCLK_REGS->GCLK_SYNCBUSY & (GCLK_SYNCBUSY_GENCTRL0_Msk << generator_id)) != 0U);
}

void GCLK_SetGeneratorSource( GCLK_GENERATOR_ID generator_id, GCLK_SOURCE source)
{
    GCLK_REGS->GCLK_GENCTRL[generator_id] = (GCLK_REGS->GCLK_GENCTRL[generator_id] & ~GCLK_GENCTRL_SRC_Msk) 
                                            |  ((uint32_t)source << GCLK_GENCTRL_SRC_Pos);
}

GCLK_SOURCE GCLK_GetGeneratorSource( GCLK_GENERATOR_ID generator_id)
{
    return (GCLK_SOURCE)((GCLK_REGS->GCLK_GENCTRL[generator_id] & GCLK_GENCTRL_SRC_Msk)>> GCLK_GENCTRL_SRC_Pos);                                          
}

void GCLK_SetDivisionParameters(GCLK_GENERATOR_ID generator_id, uint16_t divide_factor, GCLK_DIVIDE_TYPE divide_type, bool improve_duty_cycle)
{
    uint32_t genctrl = GCLK_REGS->GCLK_GENCTRL[generator_id];

    // Set division factor
    genctrl = (genctrl & ~GCLK_GENCTRL_DIV_Msk) | ((uint32_t)divide_factor << GCLK_GENCTRL_DIV_Pos);

    // Set division type
    genctrl = (genctrl & ~GCLK_GENCTRL_DIVSEL_Msk) | ((uint32_t)divide_type << GCLK_GENCTRL_DIVSEL_Pos);

    // Set duty cycle improvement only for integer division
    if (divide_type == GCLK_DIVISION_INTEGER)
    {
        genctrl = (genctrl & ~GCLK_GENCTRL_IDC_Msk) | ((improve_duty_cycle ? 1U : 0U) << GCLK_GENCTRL_IDC_Pos);
    }
    else
    {
        genctrl = (genctrl & ~GCLK_GENCTRL_IDC_Msk); // Clear IDC for power-of-two-plus-one division
    }

    GCLK_REGS->GCLK_GENCTRL[generator_id] = genctrl;
    GclkGeneratorWaitForSync(generator_id);
}

GCLK_DIVIDE_TYPE GCLK_GetDivideType(GCLK_GENERATOR_ID generator_id)
{
    return (GCLK_DIVIDE_TYPE)((GCLK_REGS->GCLK_GENCTRL[generator_id] & GCLK_GENCTRL_DIVSEL_Msk) >> GCLK_GENCTRL_DIVSEL_Pos);
}

uint16_t GCLK_GetDivideFactor(GCLK_GENERATOR_ID generator_id)
{
    return (uint16_t)((GCLK_REGS->GCLK_GENCTRL[generator_id] & GCLK_GENCTRL_DIV_Msk) >> GCLK_GENCTRL_DIV_Pos);
}

void GCLK_SetOutputOffValue(GCLK_GENERATOR_ID generator_id, bool output_off_value)
{
    GCLK_REGS->GCLK_GENCTRL[generator_id] = (GCLK_REGS->GCLK_GENCTRL[generator_id] & ~GCLK_GENCTRL_OOV_Msk) 
                                    | ((output_off_value ? 1U : 0U) << GCLK_GENCTRL_OOV_Pos);
    GclkGeneratorWaitForSync(generator_id);
}

void GCLK_SetOutputEnable(GCLK_GENERATOR_ID generator_id, bool output_enable)
{
    GCLK_REGS->GCLK_GENCTRL[generator_id] = (GCLK_REGS->GCLK_GENCTRL[generator_id] & ~GCLK_GENCTRL_OE_Msk) 
                                    | ((output_enable ? 1U : 0U) << GCLK_GENCTRL_OE_Pos);
    GclkGeneratorWaitForSync(generator_id);
}

void GCLK_EnableStandbyRun(GCLK_GENERATOR_ID generator_id)
{
    GCLK_REGS->GCLK_GENCTRL[generator_id] = (GCLK_REGS->GCLK_GENCTRL[generator_id] & ~GCLK_GENCTRL_RUNSTDBY_Msk) 
                                    | ((uint32_t)true << GCLK_GENCTRL_RUNSTDBY_Pos);
    GclkGeneratorWaitForSync(generator_id);
}

void GCLK_DisableStandbyRun(GCLK_GENERATOR_ID generator_id)
{
    GCLK_REGS->GCLK_GENCTRL[generator_id] = (GCLK_REGS->GCLK_GENCTRL[generator_id] & ~GCLK_GENCTRL_RUNSTDBY_Msk) 
                                    | ((uint32_t)false << GCLK_GENCTRL_RUNSTDBY_Pos);
    GclkGeneratorWaitForSync(generator_id);
}

void GCLK_GeneratorEnable(GCLK_GENERATOR_ID generator_id)
{
    uint32_t genctrl = GCLK_REGS->GCLK_GENCTRL[generator_id];
    genctrl = (genctrl & ~GCLK_GENCTRL_GENEN_Msk) | GCLK_GENCTRL_GENEN_Msk;
    GCLK_REGS->GCLK_GENCTRL[generator_id] = genctrl;
    GclkGeneratorWaitForSync(generator_id);
}

void GCLK_GeneratorDisable(GCLK_GENERATOR_ID generator_id)
{
    uint32_t genctrl = GCLK_REGS->GCLK_GENCTRL[generator_id];
    genctrl &= ~GCLK_GENCTRL_GENEN_Msk;
    GCLK_REGS->GCLK_GENCTRL[generator_id] = genctrl;
    GclkGeneratorWaitForSync(generator_id);
}

void GCLK_SetPeripheralChannelGenSrc(GCLK_PERIPHERAL_CHANNEL_ID channel_id, GCLK_GENERATOR_ID generator_id)
{
    if(GclkPeripheralChannelIsEnabled(channel_id))
    {
        //Disable the channel first
        GCLK_REGS->GCLK_PCHCTRL[channel_id] = (GCLK_REGS->GCLK_PCHCTRL[channel_id] & ~GCLK_PCHCTRL_CHEN_Msk);
    }
    while(GclkPeripheralChannelIsEnabled(channel_id)); 

    GCLK_REGS->GCLK_PCHCTRL[channel_id] = (GCLK_REGS->GCLK_PCHCTRL[channel_id] & ~GCLK_PCHCTRL_GEN_Msk) 
                                        | ((uint32_t)generator_id << GCLK_PCHCTRL_GEN_Pos);
}

void GCLK_EnablePeripheralChannel(GCLK_PERIPHERAL_CHANNEL_ID channel_id)
{
    GCLK_REGS->GCLK_PCHCTRL[channel_id] |= GCLK_PCHCTRL_CHEN_Msk;
    while(!GclkPeripheralChannelIsEnabled(channel_id));
}

void GCLK_PeripheralChannelDisable(GCLK_PERIPHERAL_CHANNEL_ID channel_id)
{
    GCLK_REGS->GCLK_PCHCTRL[channel_id] &= ~GCLK_PCHCTRL_CHEN_Msk;
    while(GclkPeripheralChannelIsEnabled(channel_id));
}

bool GCLK_PeripheralChannelIsEnabled(GCLK_PERIPHERAL_CHANNEL_ID channel_id)
{
    return GclkPeripheralChannelIsEnabled(channel_id);
}

void GCLK_EnablePeripheralChannelWriteLock(GCLK_PERIPHERAL_CHANNEL_ID channel_id)
{
    GCLK_REGS->GCLK_PCHCTRL[channel_id] = (GCLK_REGS->GCLK_PCHCTRL[channel_id] & ~GCLK_PCHCTRL_WRTLOCK_Msk) 
                                    | ((uint32_t)true << GCLK_PCHCTRL_WRTLOCK_Pos);
}
