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
* @file plib_tc_common.h
*
* @brief TC Peripheral Library Interface

* @details This file contains common macros and enumerations for the TC peripheral library.
*******************************************************************************/

#ifndef TC0_COMMON_H
#define TC0_COMMON_H

#include <pic32c.h>
//#include "../../test/app_test/tc_interrupts.h"

/**
 * @brief TC0 clock prescaler options.
 * 
 * Enumerates the available clock division factors for the TC0 peripheral.
 * Used to configure the timer/counter clock rate.
 */
typedef enum
{
    TC_GCLK_PRESCALER_DIV_1    = TC_CTRLA_PRESCALER_DIV1,    /**< Divide by 1 */
    TC_GCLK_PRESCALER_DIV_2    = TC_CTRLA_PRESCALER_DIV2,    /**< Divide by 2 */
    TC_GCLK_PRESCALER_DIV_4    = TC_CTRLA_PRESCALER_DIV4,    /**< Divide by 4 */
    TC_GCLK_PRESCALER_DIV_8    = TC_CTRLA_PRESCALER_DIV8,    /**< Divide by 8 */
    TC_GCLK_PRESCALER_DIV_16   = TC_CTRLA_PRESCALER_DIV16,   /**< Divide by 16 */
    TC_GCLK_PRESCALER_DIV_64   = TC_CTRLA_PRESCALER_DIV64,   /**< Divide by 64 */
    TC_GCLK_PRESCALER_DIV_256  = TC_CTRLA_PRESCALER_DIV256,  /**< Divide by 256 */
    TC_GCLK_PRESCALER_DIV_1024 = TC_CTRLA_PRESCALER_DIV1024  /**< Divide by 1024 */
} TC_GCLK_PRESCALER;

/**
 * @brief TC0 prescaler synchronization mode.
 * 
 * Enumerates the available synchronization modes for the TC0 prescaler.
 * Determines how the prescaler synchronizes with the clock source.
 */
typedef enum
{
    TC_PRESCSYNC_GCLK   = TC_CTRLA_PRESCSYNC_GCLK,   /**< Synchronize with GCLK */
    TC_PRESCSYNC_PRESC  = TC_CTRLA_PRESCSYNC_PRESC,  /**< Synchronize with prescaler */
    TC_PRESCSYNC_RESYNC = TC_CTRLA_PRESCSYNC_RESYNC, /**< Resynchronize */
} TC_PRESCALER_SYNC_MODE;

/**
 * @brief TC0 waveform generation mode.
 * 
 * Enumerates the available waveform generation modes for the TC0 peripheral.
 * Used to configure timer/counter output behavior.
 */
typedef enum
{
    TC_WAVE_GEN_NFRQ = TC_WAVE_WAVEGEN_NFRQ, /**< Normal Frequency */
    TC_WAVE_GEN_MFRQ = TC_WAVE_WAVEGEN_MFRQ, /**< Match Frequency */
    TC_WAVE_GEN_NPWM = TC_WAVE_WAVEGEN_NPWM, /**< Normal PWM */
    TC_WAVE_GEN_MPWM = TC_WAVE_WAVEGEN_MPWM  /**< Match PWM */
} TC_WAVE_GEN_MODE;

/**
 * @brief TC0 counter direction.
 * 
 * Specifies the counting direction for the TC0 counter.
 */
typedef enum
{
    TC_COUNT_DIRECTION_UP   = 1, /**< Count up */
    TC_COUNT_DIRECTION_DOWN = 2  /**< Count down */
} TC_COUNT_DIRECTION;

/**
 * @brief TC0 interrupt sources.
 * 
 * Enumerates the available interrupt sources for the TC0 peripheral.
 */
typedef enum
{
    TC_INTERRUPT_OVERFLOW         = TC_INTENSET_OVF_Msk,   /**< Overflow Interrupt Mask */
    TC_INTERRUPT_ERROR            = TC_INTENSET_ERR_Msk,   /**< Error Interrupt Mask */
    TC_INTERRUPT_MATCH_CAPTURE_0  = TC_INTENSET_MC0_Msk,   /**< Match/Compare 0 Interrupt Mask */
    TC_INTERRUPT_MATCH_CAPTURE_1  = TC_INTENSET_MC1_Msk    /**< Match/Compare 1 Interrupt Mask */
} TC_INTERRUPT;

/**
 * @brief TC Capture Channel Selection.
 * 
 * Selects the capture channel for TC0 operations.
 */
typedef enum
{
    TC_CAPTURE_CHANNEL_0 = 0, /**< Capture Channel 0 */
    TC_CAPTURE_CHANNEL_1      /**< Capture Channel 1 */
} TC_CAPTURE_CHANNEL;

/**
 * @brief TC Compare Channel Selection.
 * 
 * Selects the compare channel for TC0 operations.
 */
typedef enum
{
    TC_COMPARE_CHANNEL_0 = 0, /**< Compare Channel 0 */
    TC_COMPARE_CHANNEL_1      /**< Compare Channel 1 */
} TC_COMPARE_CHANNEL;

#if defined(TC_CTRLA_CAPTMODE0_Msk) || defined(TC_CTRLA_CAPTMODE1_Msk)
/**
 * @brief TC Capture Mode Selection.
 * 
 * Enumerates the available capture modes for TC0.
 * Example values; refer to device datasheet for details.
 */
typedef enum
{
    TC_CAPTURE_MODE_DEFAULT = ((0x0 << TC_CTRLA_CAPTMODE0_Pos ) & TC_CTRLA_CAPTMODE0_Msk), /**< Default capture mode */
    TC_CAPTURE_MODE_CAPTMIN = ((0x1 << TC_CTRLA_CAPTMODE0_Pos ) & TC_CTRLA_CAPTMODE0_Msk), /**< Minimum capture mode */
    TC_CAPTURE_MODE_CAPTMAX = ((0x2 << TC_CTRLA_CAPTMODE0_Pos ) & TC_CTRLA_CAPTMODE0_Msk)  /**< Maximum capture mode */
} TC_CAPTURE_MODE;
#endif

/**
 * @brief TC Event Action Selection.
 * 
 * Enumerates the available event actions for TC0 event system.
 */
typedef enum
{
    TC_EVENT_ACTION_OFF       = ((0x0 << TC_EVCTRL_EVACT_Pos) & TC_EVCTRL_EVACT_Msk), /**< No action */
    TC_EVENT_ACTION_RETRIGGER = ((0x01 << TC_EVCTRL_EVACT_Pos) & TC_EVCTRL_EVACT_Msk), /**< Retrigger */
    TC_EVENT_ACTION_COUNT     = ((0x02 << TC_EVCTRL_EVACT_Pos) & TC_EVCTRL_EVACT_Msk), /**< Count */
    TC_EVENT_ACTION_START     = ((0x03 << TC_EVCTRL_EVACT_Pos) & TC_EVCTRL_EVACT_Msk), /**< Start */
    TC_EVENT_ACTION_STAMP     = ((0x04 << TC_EVCTRL_EVACT_Pos) & TC_EVCTRL_EVACT_Msk), /**< Stamp */
    TC_EVENT_ACTION_PPW       = ((0x05 << TC_EVCTRL_EVACT_Pos) & TC_EVCTRL_EVACT_Msk), /**< Period pulse width */
    TC_EVENT_ACTION_PWP       = ((0x06 << TC_EVCTRL_EVACT_Pos) & TC_EVCTRL_EVACT_Msk), /**< Pulse width period */
    TC_EVENT_ACTION_PW        = ((0x07 << TC_EVCTRL_EVACT_Pos) & TC_EVCTRL_EVACT_Msk)  /**< Pulse width */
} TC_EVENT_ACTION;

/**
 * @brief TC Signal Polarity Selection.
 * 
 * Specifies the polarity for TC0 input signals.
 */
typedef enum{
    TC_SIGNAL_POLARITY_NON_INVERTED = 0, /**< Non-inverted signal */
    TC_SIGNAL_POLARITY_INVERTED         /**< Inverted signal */
} TC_SIGNAL_POLARITY;

/**
 * @brief TC Capture Trigger Source Selection.
 * 
 * Specifies the trigger source for TC0 capture operations.
 */
typedef enum{
    TC_CAPTURE_TRIGGER_SOURCE_EVENT=0, /**< Event system trigger */
    TC_CAPTURE_TRIGGER_SOURCE_IO,      /**< I/O pin trigger */
} TC_CAPTURE_TRIGGER_SOURCE;

#endif // TC0_COMMON_H
