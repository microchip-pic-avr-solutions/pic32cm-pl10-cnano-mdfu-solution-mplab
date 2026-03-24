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
* @file plib_osc32kctrl.c
* @brief 32Khz Oscillator Controller Peripheral Library (PLIB) Implementation.
*
* @details This file implementation for configuring the OSC32KCTRL peripheral, 
* providing configuration, control, status, interrupt, and callback management
* for the XOSC32K and OSC32K oscillators, clock failure detection,
* RTC clock source selection, and write protection.
*******************************************************************************/

#include "plib_osc32kctrl.h"

/* Callback for OSC32KCTRL module events */
static OSC32KCTRL_CALLBACK osc32kctrl_callback = NULL;

static void Osc32kctrlInvokeCallback (OSC32KCTRL_CALLBACK callback, OSC32KCTRL_IRQ_SOURCE irq_source)
{
    if (callback != (OSC32KCTRL_CALLBACK)0)
    {
        callback(irq_source);
    }
}



bool OSC32KCTRL_OSC32K_IsReady(void)
{
    return ((OSC32KCTRL_REGS->OSC32KCTRL_STATUS & OSC32KCTRL_STATUS_OSC32KRDY_Msk) != 0U);
}

void OSC32KCTRL_OSC32K_EnableOnDemand(void)
{
    OSC32KCTRL_REGS->OSC32KCTRL_OSC32KCTRL |= OSC32KCTRL_OSC32KCTRL_ONDEMAND_Msk;
}

void OSC32KCTRL_OSC32K_DisableOnDemand(void)
{
    OSC32KCTRL_REGS->OSC32KCTRL_OSC32KCTRL &= ~OSC32KCTRL_OSC32KCTRL_ONDEMAND_Msk;
}

bool OSC32KCTRL_OSC32K_OnDemandIsEnabled(void)
{
    return ((OSC32KCTRL_REGS->OSC32KCTRL_OSC32KCTRL & OSC32KCTRL_OSC32KCTRL_ONDEMAND_Msk) != 0U);
}

void OSC32KCTRL_RTC_SelectClockSource(OSC32KCTRL_RTC_CLOCK rtc_sel)
{
    OSC32KCTRL_REGS->OSC32KCTRL_RTCCTRL = (OSC32KCTRL_REGS->OSC32KCTRL_RTCCTRL & ~OSC32KCTRL_RTCCTRL_RTCSEL_Msk)
                                          | ((uint32_t)rtc_sel << OSC32KCTRL_RTCCTRL_RTCSEL_Pos);
}

OSC32KCTRL_RTC_CLOCK OSC32KCTRL_RTC_GetClockSource(void)
{
    return (OSC32KCTRL_RTC_CLOCK)((OSC32KCTRL_REGS->OSC32KCTRL_RTCCTRL & OSC32KCTRL_RTCCTRL_RTCSEL_Msk) >> OSC32KCTRL_RTCCTRL_RTCSEL_Pos);
}

bool OSC32KCTRL_XOSC32K_IsReady(void)
{
    bool status = ((OSC32KCTRL_REGS->OSC32KCTRL_STATUS & OSC32KCTRL_STATUS_XOSC32KRDY_Msk) != 0U);
    return status;
}

void OSC32KCTRL_XOSC32K_SelectClockSource(OSC32KCTRL_XTAL_SOURCE xtal_source)
{
    OSC32KCTRL_REGS->OSC32KCTRL_XOSC32KCTRL = (OSC32KCTRL_REGS->OSC32KCTRL_XOSC32KCTRL & ~OSC32KCTRL_XOSC32KCTRL_XTALEN_Msk)
                                            | (uint32_t)xtal_source;
}

void OSC32KCTRL_XOSC32K_Enable(void)
{
    OSC32KCTRL_REGS->OSC32KCTRL_XOSC32KCTRL |= OSC32KCTRL_XOSC32KCTRL_ENABLE_Msk;
}

void OSC32KCTRL_XOSC32K_Disable(void)
{
    OSC32KCTRL_REGS->OSC32KCTRL_XOSC32KCTRL &= ~OSC32KCTRL_XOSC32KCTRL_ENABLE_Msk;
    //wait for the XOSC32K to be disabled
    while((OSC32KCTRL_REGS->OSC32KCTRL_STATUS & OSC32KCTRL_STATUS_XOSC32KRDY_Msk) != 0U);
}

void OSC32KCTRL_XOSC32K_EnableOnDemand(void)
{
    OSC32KCTRL_REGS->OSC32KCTRL_XOSC32KCTRL |= OSC32KCTRL_XOSC32KCTRL_ONDEMAND_Msk;
}

void OSC32KCTRL_XOSC32K_DisableOnDemand(void)
{
    OSC32KCTRL_REGS->OSC32KCTRL_XOSC32KCTRL &= ~OSC32KCTRL_XOSC32KCTRL_ONDEMAND_Msk;
}

bool OSC32KCTRL_XOSC32K_OnDemandIsEnabled(void)
{
    return ((OSC32KCTRL_REGS->OSC32KCTRL_XOSC32KCTRL & OSC32KCTRL_XOSC32KCTRL_ONDEMAND_Msk) != 0U);
}

void OSC32KCTRL_XOSC32K_SetStartUpTime(OSC32KCTRL_CSUT startup_time)
{
    OSC32KCTRL_REGS->OSC32KCTRL_XOSC32KCTRL = (OSC32KCTRL_REGS->OSC32KCTRL_XOSC32KCTRL & ~OSC32KCTRL_XOSC32KCTRL_CSUT_Msk)
                                            | (uint32_t)startup_time << OSC32KCTRL_XOSC32KCTRL_CSUT_Pos;
}

OSC32KCTRL_CSUT OSC32KCTRL_XOSC32K_GetStartUpTime(void)
{
    return (OSC32KCTRL_CSUT)((OSC32KCTRL_REGS->OSC32KCTRL_XOSC32KCTRL & OSC32KCTRL_XOSC32KCTRL_CSUT_Msk) >> OSC32KCTRL_XOSC32KCTRL_CSUT_Pos);
}

void OSC32KCTRL_XOSC32K_EnableLowPowerMode(void)
{
    OSC32KCTRL_REGS->OSC32KCTRL_XOSC32KCTRL |= OSC32KCTRL_XOSC32KCTRL_LPMODE_Msk;
}

void OSC32KCTRL_XOSC32K_DisableLowPowerMode(void)
{
    OSC32KCTRL_REGS->OSC32KCTRL_XOSC32KCTRL &= ~OSC32KCTRL_XOSC32KCTRL_LPMODE_Msk;
}

bool OSC32KCTRL_XOSC32K_LowPowerIsEnabled(void)
{
    return (bool)((OSC32KCTRL_REGS->OSC32KCTRL_XOSC32KCTRL & OSC32KCTRL_XOSC32KCTRL_LPMODE_Msk) >> OSC32KCTRL_XOSC32KCTRL_LPMODE_Pos);
}

void OSC32KCTRL_CFD_Enable(void)
{
    OSC32KCTRL_REGS->OSC32KCTRL_CFDCTRL |= OSC32KCTRL_CFDCTRL_CFDEN_Msk; 
}

void OSC32KCTRL_CFD_Disable(void)
{
    OSC32KCTRL_REGS->OSC32KCTRL_CFDCTRL &= ~OSC32KCTRL_CFDCTRL_CFDEN_Msk;
}

bool OSC32KCTRL_CFD_GetClockFailureStatus(void)
{
    return ((OSC32KCTRL_REGS->OSC32KCTRL_STATUS & OSC32KCTRL_STATUS_CLKFAIL_Msk) != 0U);
}

void OSC32KCTRL_CFD_EnableEventOutput(void)
{
    OSC32KCTRL_REGS->OSC32KCTRL_EVCTRL |= OSC32KCTRL_EVCTRL_CFDEO_Msk;
}

void OSC32KCTRL_CFD_DisableEventOutput(void)
{
    OSC32KCTRL_REGS->OSC32KCTRL_EVCTRL &= ~OSC32KCTRL_EVCTRL_CFDEO_Msk;
}

bool OSC32KCTRL_CFD_ClockIsSwitched(void)
{
    return ((OSC32KCTRL_REGS->OSC32KCTRL_STATUS & OSC32KCTRL_STATUS_CLKSW_Msk)!= 0U);
}

void OSC32KCTRL_CFD_SetSwitchBack(void)
{
    OSC32KCTRL_REGS->OSC32KCTRL_CFDCTRL |= OSC32KCTRL_CFDCTRL_SWBACK_Msk;
}

bool OSC32KCTRL_CFD_GetSwitchBack(void)
{
    return ((OSC32KCTRL_REGS->OSC32KCTRL_CFDCTRL & OSC32KCTRL_CFDCTRL_SWBACK_Msk)!=0);
}

void OSC32KCTRL_CFD_SetOsc32kPrescaler(OSC32K_CFD_PRESCALER prescaler)
{
    OSC32KCTRL_REGS->OSC32KCTRL_CFDCTRL = (OSC32KCTRL_REGS->OSC32KCTRL_CFDCTRL & ~OSC32KCTRL_CFDCTRL_CFDPRESC_Msk)
                                            | (uint32_t)prescaler << OSC32KCTRL_CFDCTRL_CFDPRESC_Pos;
}

OSC32K_CFD_PRESCALER OSC32KCTRL_CFD_GetOsc32kPrescaler(void)
{
    return (OSC32K_CFD_PRESCALER)((OSC32KCTRL_REGS->OSC32KCTRL_CFDCTRL & OSC32KCTRL_CFDCTRL_CFDPRESC_Msk) >> OSC32KCTRL_CFDCTRL_CFDPRESC_Pos);
}

void OSC32KCTRL_EnableInterrupt(OSC32KCTRL_IRQ_SOURCE irq_source)
{
    OSC32KCTRL_REGS->OSC32KCTRL_INTENSET |= (OSC32KCTRL_INTENSET_XOSC32KRDY_Msk << irq_source);
}

void OSC32KCTRL_DisableInterrupt(OSC32KCTRL_IRQ_SOURCE irq_source)
{
    OSC32KCTRL_REGS->OSC32KCTRL_INTENCLR |= (OSC32KCTRL_INTENCLR_XOSC32KRDY_Msk << irq_source);
}

bool OSC32KCTRL_InterruptIsEnabled(OSC32KCTRL_IRQ_SOURCE irq_source)
{
    return ((OSC32KCTRL_REGS->OSC32KCTRL_INTENSET & (OSC32KCTRL_INTENSET_XOSC32KRDY_Msk << irq_source)) != 0U);
}

void OSC32KCTRL_SetReadyFlag(OSC32KCTRL_IRQ_SOURCE irq_source)
{
    OSC32KCTRL_REGS->OSC32KCTRL_INTFLAGSET |= (OSC32KCTRL_INTFLAGSET_XOSC32KRDY_Msk << irq_source);
}

bool OSC32KCTRL_IntFlagSetIsEnabled(OSC32KCTRL_IRQ_SOURCE irq_source)
{
    return ((OSC32KCTRL_REGS->OSC32KCTRL_INTFLAGSET & (OSC32KCTRL_INTFLAGSET_XOSC32KRDY_Msk << irq_source)) != 0U);
}

bool OSC32KCTRL_InterruptFlagIsSet(OSC32KCTRL_IRQ_SOURCE irq_source)
{
    return ((OSC32KCTRL_REGS->OSC32KCTRL_INTFLAG & (OSC32KCTRL_INTFLAG_XOSC32KRDY_Msk << irq_source)) != 0U);
}

void OSC32KCTRL_ClearInterruptFlag(OSC32KCTRL_IRQ_SOURCE irq_source)
{
    OSC32KCTRL_REGS->OSC32KCTRL_INTFLAG |= (OSC32KCTRL_INTFLAG_XOSC32KRDY_Msk << irq_source);
}

void OSC32KCTRL_EnableWriteProtection(void)
{
    OSC32KCTRL_REGS->OSC32KCTRL_WPCTRL = ((OSC32KCTRL_WPCTRL_WPEN_Msk) |(((uint32_t)OSC32KCTRL_WP_KEY << OSC32KCTRL_WPCTRL_WPKEY_Pos)));
}

void OSC32KCTRL_DisableWriteProtection(void)
{
    OSC32KCTRL_REGS->OSC32KCTRL_WPCTRL = (((uint32_t)OSC32KCTRL_WP_KEY << OSC32KCTRL_WPCTRL_WPKEY_Pos));
}

bool OSC32KCTRL_WriteProtectionIsEnabled(void)
{
    return ((OSC32KCTRL_REGS->OSC32KCTRL_WPCTRL & OSC32KCTRL_WPCTRL_WPEN_Msk) != 0U);
}

void OSC32KCTRL_WPCTRL_EnableWriteLock(void)
{
    OSC32KCTRL_REGS->OSC32KCTRL_WPCTRL = (OSC32KCTRL_REGS->OSC32KCTRL_WPCTRL & OSC32KCTRL_WPCTRL_WPEN_Msk)
                                        | ((OSC32KCTRL_WPCTRL_WPLCK_Msk) 
                                        | ((uint32_t)OSC32KCTRL_WP_KEY << OSC32KCTRL_WPCTRL_WPKEY_Pos));
}

void OSC32KCTRL_SetCallbackHandler(OSC32KCTRL_CALLBACK callback)
{
    osc32kctrl_callback = callback;
}

void OSC32KCTRL_Handler(void)
{
    uint32_t inten = OSC32KCTRL_REGS->OSC32KCTRL_INTENSET;
    uint32_t intflag = OSC32KCTRL_REGS->OSC32KCTRL_INTFLAG;
    
    /* XOSC32KRDY */
    if (((inten & OSC32KCTRL_INTENSET_XOSC32KRDY_Msk) != 0U) &&
        ((intflag & OSC32KCTRL_INTFLAG_XOSC32KRDY_Msk) != 0U))
    {
        //Clear the interrupt flag
        OSC32KCTRL_REGS->OSC32KCTRL_INTFLAG = OSC32KCTRL_INTFLAG_XOSC32KRDY_Msk;
        Osc32kctrlInvokeCallback (osc32kctrl_callback,OSC32KCTRL_IRQ_XOSC32KRDY );
    }

    /* OSC32KRDY */
    if (((inten & OSC32KCTRL_INTENSET_OSC32KRDY_Msk) != 0U) &&
        ((intflag & OSC32KCTRL_INTFLAG_OSC32KRDY_Msk) != 0U))
    {
        //Clear the interrupt flag
        OSC32KCTRL_REGS->OSC32KCTRL_INTFLAG = OSC32KCTRL_INTFLAG_OSC32KRDY_Msk;
        Osc32kctrlInvokeCallback (osc32kctrl_callback, OSC32KCTRL_IRQ_OSC32KRDY);
    }

    /* CLKFAIL */
    if (((inten & OSC32KCTRL_INTENSET_CLKFAIL_Msk) != 0U) &&
        ((intflag & OSC32KCTRL_INTFLAG_CLKFAIL_Msk) != 0U))
    {
        OSC32KCTRL_REGS->OSC32KCTRL_INTFLAG = OSC32KCTRL_INTFLAG_CLKFAIL_Msk;
        //Clear the interrupt flag
        Osc32kctrlInvokeCallback (osc32kctrl_callback, OSC32KCTRL_IRQ_CLKFAIL);
    }
}

void OSC32KCTRL_Initialize(void)
{
    NVIC_SetVector(OSC32KCTRL_IRQn, (uint32_t)OSC32KCTRL_Handler);
    NVIC_EnableIRQ(OSC32KCTRL_IRQn);
}



