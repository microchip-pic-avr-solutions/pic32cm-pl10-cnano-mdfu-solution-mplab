/*******************************************************************************
 * Copyright (C) 2025 Microchip Technology Inc. and its subsidiaries.
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
/*******************************************************************************
 * @file plib_tc0_capture16bit.c
 *
 * @brief TC Peripheral Library Interface (Capture Mode)
 *
 * @details This file implements the interface for configuring and controlling the TC0 in 16-bit capture mode.
 *******************************************************************************/

#include "plib_tc0_capture16bit.h"
#include "plib_tc0_interrupt.h"

static volatile TC0_16CAPTURE_OBJECT tc0_16bit_capture_obj;

static void WaitForSyncBusy16(uint32_t mask)
{
    while ((TC0_REGS->COUNT16.TC_SYNCBUSY & mask) != 0U)
    {
    }
}



void TC0_CAPTURE_16BIT_SetClockPrescaler(TC_GCLK_PRESCALER prescaler, TC_PRESCALER_SYNC_MODE presc_sync_mode)
{
    TC0_REGS->COUNT16.TC_CTRLA &= ~(TC_CTRLA_PRESCALER_Msk | TC_CTRLA_PRESCSYNC_Msk);
    TC0_REGS->COUNT16.TC_CTRLA |= ((uint32_t)prescaler | (uint32_t)presc_sync_mode);
}

void TC0_CAPTURE_16BIT_Enable(void)
{
    TC0_REGS->COUNT16.TC_CTRLA |= TC_CTRLA_ENABLE_Msk;
    WaitForSyncBusy16(TC_SYNCBUSY_ENABLE_Msk);
}

void TC0_CAPTURE_16BIT_Disable(void)
{
    TC0_REGS->COUNT16.TC_CTRLA &= ~TC_CTRLA_ENABLE_Msk;
    WaitForSyncBusy16(TC_SYNCBUSY_ENABLE_Msk);
}

void TC0_CAPTURE_16BIT_ResetSoftware(void)
{
    TC0_REGS->COUNT16.TC_CTRLA |= TC_CTRLA_SWRST_Msk;
    WaitForSyncBusy16(TC_SYNCBUSY_SWRST_Msk);
}

void TC0_CAPTURE_16BIT_StopCapture(void)
{
    TC0_REGS->COUNT16.TC_CTRLBSET = ((uint8_t)TC_CTRLBSET_CMD_STOP << TC_CTRLBSET_CMD_Pos) & TC_CTRLBSET_CMD_Msk;
    WaitForSyncBusy16(TC_SYNCBUSY_CTRLB_Msk);
}

bool TC0_CAPTURE_16BIT_CaptureIsStopped(void)
{
    return ((TC0_REGS->COUNT16.TC_STATUS & TC_STATUS_STOP_Msk) != 0);
}

void TC0_CAPTURE_16BIT_RetriggerCapture(void)
{
    TC0_REGS->COUNT16.TC_CTRLBSET = ((uint8_t)TC_CTRLBSET_CMD_RETRIGGER << TC_CTRLBSET_CMD_Pos) & TC_CTRLBSET_CMD_Msk;
    WaitForSyncBusy16(TC_SYNCBUSY_CTRLB_Msk);
}

void TC0_CAPTURE_16BIT_EnableCaptureChannel(TC_CAPTURE_CHANNEL channel)
{
    TC0_REGS->COUNT16.TC_CTRLA |= (TC_CTRLA_CAPTEN0_Msk << channel);
}

void TC0_CAPTURE_16BIT_DisableCaptureChannel(TC_CAPTURE_CHANNEL channel)
{
    TC0_REGS->COUNT16.TC_CTRLA &= ~(TC_CTRLA_CAPTEN0_Msk << channel);
}

TC_GCLK_PRESCALER TC0_CAPTURE_16BIT_GetPrescaler(void)
{
    return  (TC_GCLK_PRESCALER)((TC0_REGS->COUNT16.TC_CTRLA & TC_CTRLA_PRESCALER_Msk) >> TC_CTRLA_PRESCALER_Pos);
}

uint16_t TC0_CAPTURE_16BIT_GetCaptureValue(TC_CAPTURE_CHANNEL channel)
{
    return (uint16_t)TC0_REGS->COUNT16.TC_CC[channel];
}

void TC0_CAPTURE_16BIT_SetInputPinPolarity(TC_CAPTURE_CHANNEL channel, TC_SIGNAL_POLARITY polarity)
{
    if (TC_SIGNAL_POLARITY_INVERTED == polarity)
    {
        TC0_REGS->COUNT16.TC_DRVCTRL |= (TC_DRVCTRL_INVEN0_Msk << channel);
    }
    else
    {
        TC0_REGS->COUNT16.TC_DRVCTRL &= ~(TC_DRVCTRL_INVEN0_Msk << channel);
    }
}

void TC0_CAPTURE_16BIT_SelectTriggerSource(TC_CAPTURE_CHANNEL channel, TC_CAPTURE_TRIGGER_SOURCE trigger_source)
{
    if (TC_CAPTURE_TRIGGER_SOURCE_IO == trigger_source)
    {
        TC0_REGS->COUNT16.TC_CTRLA |= (TC_CTRLA_COPEN0_Msk << channel);
    }
    else
    {
        TC0_REGS->COUNT16.TC_CTRLA &= ~(TC_CTRLA_COPEN0_Msk << channel);
    }
}

#if defined(TC_CTRLA_CAPTMODE0_Msk) || defined(TC_CTRLA_CAPTMODE1_Msk)
void TC0_CAPTURE_16BIT_SetMode(TC_CAPTURE_CHANNEL channel, TC_CAPTURE_MODE mode)
{
    if (TC_CAPTURE_CHANNEL_0 == channel)
    {
        TC0_REGS->COUNT16.TC_CTRLA = (TC0_REGS->COUNT16.TC_CTRLA & (~TC_CTRLA_CAPTMODE0_Msk)) | mode;
    }
    else
    {
        TC0_REGS->COUNT16.TC_CTRLA = (TC0_REGS->COUNT16.TC_CTRLA & (~TC_CTRLA_CAPTMODE1_Msk)) | (mode << 3);
    }
}

TC_CAPTURE_MODE TC0_CAPTURE_16BIT_GetMode(TC_CAPTURE_CHANNEL channel)
{
    uint8_t capture_mode = 0;
    if (TC_CAPTURE_CHANNEL_0 == channel)
    {
        capture_mode = (uint8_t)((TC0_REGS->COUNT16.TC_CTRLA & TC_CTRLA_CAPTMODE0_Msk));
    }
    else
    {
        capture_mode = (uint8_t)((TC0_REGS->COUNT16.TC_CTRLA & TC_CTRLA_CAPTMODE1_Msk));
    }
    return (TC_CAPTURE_MODE)capture_mode;
}
#endif

void TC0_CAPTURE_16BIT_EnableEventOutput(TC_CAPTURE_CHANNEL channel)
{
    TC0_REGS->COUNT16.TC_EVCTRL |= (TC_EVCTRL_MCEO0_Msk << channel);
}

void TC0_CAPTURE_16BIT_DisableEventOutput(TC_CAPTURE_CHANNEL channel)
{
    TC0_REGS->COUNT16.TC_EVCTRL &= ~(TC_EVCTRL_MCEO0_Msk << channel);
}

void TC0_CAPTURE_16BIT_EnableInputEvent(void)
{
    TC0_REGS->COUNT16.TC_EVCTRL |= TC_EVCTRL_TCEI_Msk;
}

void TC0_CAPTURE_16BIT_DisableInputEvent(void)
{
    TC0_REGS->COUNT16.TC_EVCTRL &= ~TC_EVCTRL_TCEI_Msk;
}

void TC0_CAPTURE_16BIT_SetEventInputPolarity(TC_SIGNAL_POLARITY polarity)
{
    if (TC_SIGNAL_POLARITY_INVERTED == polarity)
    {
        TC0_REGS->COUNT16.TC_EVCTRL |= TC_EVCTRL_TCINV_Msk;
    }
    else
    {
        TC0_REGS->COUNT16.TC_EVCTRL &= ~TC_EVCTRL_TCINV_Msk;
    }
}

void TC0_CAPTURE_16BIT_EnableClockOnDemand(void)
{
    TC0_REGS->COUNT16.TC_CTRLA |= TC_CTRLA_ONDEMAND_Msk;
}
void TC0_CAPTURE_16BIT_DisableClockOnDemand(void)
{
    TC0_REGS->COUNT16.TC_CTRLA &= ~TC_CTRLA_ONDEMAND_Msk;
}

void TC0_CAPTURE_16BIT_EnableInterrupt(TC_INTERRUPT source)
{
    TC0_REGS->COUNT16.TC_INTENSET = (uint8_t)source;
}

void TC0_CAPTURE_16BIT_SetEventInputAction(TC_EVENT_ACTION action)
{
    TC0_REGS->COUNT16.TC_EVCTRL = ((TC0_REGS->COUNT16.TC_EVCTRL & ~TC_EVCTRL_EVACT_Msk) | action);
}

void TC0_CAPTURE_16BIT_DisableInterrupt(TC_INTERRUPT source)
{
    TC0_REGS->COUNT16.TC_INTENCLR = (uint8_t)source;
}

void TC0_CAPTURE_16BIT_ClearInterruptFlag(TC_INTERRUPT flag)
{
    TC0_REGS->COUNT16.TC_INTFLAG = (uint8_t)flag;
}

TC_INTERRUPT TC0_CAPTURE_16BIT_GetInterruptFlag(void)
{
    return (TC_INTERRUPT)(TC0_REGS->COUNT16.TC_INTFLAG & 0xFFU);
}

void TC0_CAPTURE_16BIT_SetCallbackHandler(TC0_16CAPTURE_CALLBACK_HANDLER callback)
{
    tc0_16bit_capture_obj.capture_16_callback = callback;
}

void TC0_CAPTURE_16BIT_InterruptHandler(void)
{
    TC_INTERRUPT capture_16_int_cause = TC0_CAPTURE_16BIT_GetInterruptFlag();
    if (capture_16_int_cause != 0U)
    {
        TC0_CAPTURE_16BIT_ClearInterruptFlag(capture_16_int_cause);
        if (tc0_16bit_capture_obj.capture_16_callback != NULL)
        {
            tc0_16bit_capture_obj.capture_16_callback(capture_16_int_cause);
        }
    }
}
void TC0_CAPTURE_16BIT_Initialize(void)
{
    TC0_REGS->COUNT16.TC_CTRLA = TC_CTRLA_MODE_COUNT16;
    TC0_SetInterruptHandler(TC0_CAPTURE_16BIT_InterruptHandler);
}