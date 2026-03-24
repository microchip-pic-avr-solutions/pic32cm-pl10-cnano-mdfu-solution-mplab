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
 * @file plib_tc0_capture16bit.h
 *
 * @brief TC Peripheral Library Interface (16-bit Capture Mode)
 *
 * @details Public API declarations for TC0 16-bit Capture Mode.
 *******************************************************************************/

#ifndef PLIB_TC0_CAPTURE16BIT_H
#define PLIB_TC0_CAPTURE16BIT_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "plib_tc_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Example usage of the TC0 16BIT Capture PLIB interface .
 * @code
 * #include "plib_tc0_capture16bit.h"
 *
 * void TC0_Capture_Interrupt_Handler(TC_INTERRUPT int_cause)
 * {
 *     // Handle capture interrupt, e.g., read captured value
 * }
 *
 * int main(void)
 * {
 *     TC0_CAPTURE_16BIT_ResetSoftware();
 *     TC0_CAPTURE_16BIT_Initialize();
 *     TC0_CAPTURE_16BIT_SetClockPrescaler(TC_GCLK_PRESCALER_DIV_1024, TC_PRESCSYNC_PRESC);
 *     #if defined(TC_CTRLA_CAPTMODE0_Msk) || defined(TC_CTRLA_CAPTMODE1_Msk)
 *     TC0_CAPTURE_16BIT_SetMode(TC_CAPTURE_CHANNEL_0, TC_CAPTURE_MODE_DEFAULT);
 *     TC0_CAPTURE_16BIT_SetMode(TC_CAPTURE_CHANNEL_1, TC_CAPTURE_MODE_DEFAULT);
 *     #endif
 *     TC0_CAPTURE_16BIT_SelectTriggerSource(TC_CAPTURE_CHANNEL_0, TC_CAPTURE_TRIGGER_SOURCE_EVENT);
 *     TC0_CAPTURE_16BIT_SelectTriggerSource(TC_CAPTURE_CHANNEL_1, TC_CAPTURE_TRIGGER_SOURCE_EVENT);
 *     TC0_CAPTURE_16BIT_SetInputPinPolarity(TC_CAPTURE_CHANNEL_0, TC_SIGNAL_POLARITY_NON_INVERTED);
 *     TC0_CAPTURE_16BIT_SetInputPinPolarity(TC_CAPTURE_CHANNEL_1, TC_SIGNAL_POLARITY_NON_INVERTED);
 *     TC0_CAPTURE_16BIT_EnableCaptureChannel(TC_CAPTURE_CHANNEL_0);
 *     TC0_CAPTURE_16BIT_EnableCaptureChannel(TC_CAPTURE_CHANNEL_1);
 *     TC0_CAPTURE_16BIT_EnableInputEvent();
 *     TC0_CAPTURE_16BIT_SetEventInputAction(TC_EVENT_ACTION_PPW);
 *     TC0_CAPTURE_16BIT_EnableInterrupt(TC_INTERRUPT_MATCH_CAPTURE_0 | TC_INTERRUPT_MATCH_CAPTURE_1);
 *     TC0_CAPTURE_16BIT_SetCallbackHandler(TC0_Capture_Interrupt_Handler);
 *     TC0_CAPTURE_16BIT_Enable();
 *     while (1)
 *     {
 *         // Application code here
 *     }
 * }
 * @endcode
 */
/**
 * @brief TC0 16-bit Capture callback handler type.
 *
 * This typedef defines the function pointer type for a callback handler
 * that is invoked when a TC0 16-bit capture interrupt occurs.
 *
 * The callback function receives the interrupt cause as a parameter,
 * allowing the application to handle specific capture events such as
 * match/capture, overflow, or error interrupts.
 *
 * @param int_cause The interrupt source mask of type TC_INTERRUPT.
 *
 * @note Register your callback using TC0_CAPTURE_16BIT_SetCallbackHandler().
 *       The callback will be called from the TC0 interrupt handler context.
 */
typedef void (*TC0_16CAPTURE_CALLBACK_HANDLER)(TC_INTERRUPT int_cause);

/**
 * @brief TC0 16-bit Capture object structure.
 *
 * This structure holds the state and callback information for the TC0 16-bit capture mode.
 * It is used internally by the peripheral library to manage capture interrupts and
 * callback invocation.
 *
 * @ TC0_16CAPTURE_OBJECT::capture_16_callback
 *      The registered callback handler for TC0 16-bit capture interrupts.
 *      This function will be called when a capture interrupt occurs.
 *
 * @ TC0_16CAPTURE_OBJECT::capture_16_int_cause
 *      The latest interrupt cause mask, indicating which interrupt triggered
 *      the callback.
 *
 * @note The application should not modify this structure directly.
 *       Use the provided PLIB API functions to register callbacks and handle interrupts.
 */
typedef struct
{
    /** @brief Callback function pointer for TC 16-bit capture interrupts. */
    TC0_16CAPTURE_CALLBACK_HANDLER capture_16_callback; 

    /** @brief Interrupt cause mask for the last TC interrupt. */
    TC_INTERRUPT capture_16_int_cause;                 
} TC0_16CAPTURE_OBJECT;

/**
 * @brief Initialize the TC0 16BIT capture.
 * @param None
 * @return None
 */
void TC0_CAPTURE_16BIT_Initialize(void);

/**
 * @brief Set the prescaler and prescaler synchronization for TC0 16BIT capture.
 * @param prescaler Prescaler value.
 * @param prescsync Prescaler synchronization value.
 * @return None
 */
void TC0_CAPTURE_16BIT_SetClockPrescaler(TC_GCLK_PRESCALER prescaler, TC_PRESCALER_SYNC_MODE presc_sync_mode);

/**
 * @brief Enable the TC0 16BIT capture.
 * @param None
 * @return None
 */
void TC0_CAPTURE_16BIT_Enable(void);

/**
 * @brief Disable the TC0 16BIT capture.
 * @param None
 * @return None
 */
void TC0_CAPTURE_16BIT_Disable(void);

/**
 * @brief Perform a software reset of the TC0 16BIT capture.
 * @param None
 * @return None
 */
void TC0_CAPTURE_16BIT_ResetSoftware(void);

/**
 * @brief Stop the capture operation.
 * @param None
 * @return None
 */
void TC0_CAPTURE_16BIT_StopCapture(void);

/**
 * @brief Check if the capture is stopped.
 * @param None
 * @return true if stopped, false otherwise.
 */
bool TC0_CAPTURE_16BIT_CaptureIsStopped(void);

/**
 * @brief Retrigger the capture operation.
 * @param None
 * @return None
 */
void TC0_CAPTURE_16BIT_RetriggerCapture(void);

/**
 * @brief Enable a specific capture channel.
 * @param channel Capture channel to enable.
 * @return None
 */
void TC0_CAPTURE_16BIT_EnableCaptureChannel(TC_CAPTURE_CHANNEL channel);

/**
 * @brief Disable a specific capture channel.
 * @param channel Capture channel to disable.
 * @return None
 */
void TC0_CAPTURE_16BIT_DisableCaptureChannel(TC_CAPTURE_CHANNEL channel);

/**
 * @brief Get the current prescaler value.
 * @param None
 * @return Prescaler value.
 */
TC_GCLK_PRESCALER TC0_CAPTURE_16BIT_GetPrescaler(void);

/**
 * @brief Get the captured value for a channel.
 * @param channel Capture channel.
 * @return Captured value.
 */
uint16_t TC0_CAPTURE_16BIT_GetCaptureValue(TC_CAPTURE_CHANNEL channel);

/**
 * @brief Set input pin polarity for a channel.
 * @param channel Capture channel.
 * @param polarity Signal polarity.
 * @return None
 */
void TC0_CAPTURE_16BIT_SetInputPinPolarity(TC_CAPTURE_CHANNEL channel, TC_SIGNAL_POLARITY polarity);

/**
 * @brief Select trigger source for a channel.
 * @param channel Capture channel.
 * @param trigger_source Trigger source.
 * @return None
 */
void TC0_CAPTURE_16BIT_SelectTriggerSource(TC_CAPTURE_CHANNEL channel, TC_CAPTURE_TRIGGER_SOURCE trigger_source);

#if defined(TC_CTRLA_CAPTMODE0_Msk) || defined(TC_CTRLA_CAPTMODE1_Msk)
/**
 * @brief Set capture mode for a channel.
 * @param channel Capture channel.
 * @param mode Capture mode.
 * @return None
 */
void TC0_CAPTURE_16BIT_SetMode(TC_CAPTURE_CHANNEL channel, TC_CAPTURE_MODE mode);

/**
 * @brief Get capture mode for a channel.
 * @param channel Capture channel.
 * @return Capture mode.
 */
TC_CAPTURE_MODE TC0_CAPTURE_16BIT_GetMode(TC_CAPTURE_CHANNEL channel);
#endif

/**
 * @brief Enable event output for a channel.
 * @param channel Capture channel.
 * @return None
 */
void TC0_CAPTURE_16BIT_EnableEventOutput(TC_CAPTURE_CHANNEL channel);

/**
 * @brief Disable event output for a channel.
 * @param channel Capture channel.
 * @return None
 */
void TC0_CAPTURE_16BIT_DisableEventOutput(TC_CAPTURE_CHANNEL channel);

/**
 * @brief Enable clock on demand.
 * @param None
 * @return None
 */
void TC0_CAPTURE_16BIT_EnableClockOnDemand(void);

/**
 * @brief Disable clock on demand.
 * @param None
 * @return None
 */
void TC0_CAPTURE_16BIT_DisableClockOnDemand(void);

/**
 * @brief Enable input event.
 * @param None
 * @return None
 */
void TC0_CAPTURE_16BIT_EnableInputEvent(void);

/**
 * @brief Disable input event.
 * @param None
 * @return None
 */
void TC0_CAPTURE_16BIT_DisableInputEvent(void);

/**
 * @brief Set event input polarity.
 * @param polarity Signal polarity.
 * @return None
 */
void TC0_CAPTURE_16BIT_SetEventInputPolarity(TC_SIGNAL_POLARITY polarity);

/**
 * @brief Enable specific TC0 interrupts.
 * @param source Interrupt source mask of type TC_INTERRUPT.
 * @return None
 */
void TC0_CAPTURE_16BIT_EnableInterrupt(TC_INTERRUPT source);

/**
 * @brief Set event input action.
 * @param action Event action.
 * @return None
 */
void TC0_CAPTURE_16BIT_SetEventInputAction(TC_EVENT_ACTION action);

/**
 * @brief Disable specific TC0 interrupts.
 * @param source Interrupt source mask of type TC_INTERRUPT.
 * @return None
 */
void TC0_CAPTURE_16BIT_DisableInterrupt(TC_INTERRUPT source);

/**
 * @brief Clear specific TC0 interrupt flags.
 * @param flag Interrupt flag mask.
 * @return None
 */
void TC0_CAPTURE_16BIT_ClearInterruptFlag(TC_INTERRUPT flag);

/**
 * @brief Get the current TC0 interrupt flags.
 * @param None
 * @return Interrupt flag mask.
 */
TC_INTERRUPT TC0_CAPTURE_16BIT_GetInterruptFlag(void);

/**
 * @brief Register a callback for capture interrupts.
 * @param callback Function pointer to callback.
 * @return None
 */
void TC0_CAPTURE_16BIT_SetCallbackHandler(TC0_16CAPTURE_CALLBACK_HANDLER callback);

#ifdef __cplusplus
}
#endif

#endif /* PLIB_TC0_CAPTURE16BIT_H */
