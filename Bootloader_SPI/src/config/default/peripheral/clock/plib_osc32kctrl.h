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
* @file plib_osc32kctrl.h
* @brief 32Khz Oscillator Controller Peripheral Library (PLIB) Interface.
*
* @details This file interface for the OSC32KCTRL peripheral, providing
* configuration, control, status, interrupt, and callback management
* for the XOSC32K and OSC32K oscillators, clock failure detection,
* RTC clock source selection, and write protection.
*******************************************************************************/

#ifndef PLIB_OSC32KCTRL_H
#define PLIB_OSC32KCTRL_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <pic32c.h>

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * @brief Example: Initialize and Use OSC32KCTRL Peripheral
 *
 * This example demonstrates how to configure the 32 kHz oscillator (OSC32KCTRL) 
 * using the PLIB OSC32KCTRL APIs. It enables on-demand mode, enables interrupt 
 * for clock failure detection, sets the prescaler, startup time, and selects the 
 * external crystal source. The code then enables the oscillator and waits until 
 * it is ready before proceeding.
 *
 * ```c
 * #include "plib_osc32kctrl.h"
 * 
 * int main(void)
 * {
 *      
 *      OSC32KCTRL_OSC32K_EnableOnDemand();
 *      
 *      OSC32KCTRL_EnableInterrupt(OSC32KCTRL_IRQ_CLKFAIL);
 *       
 *      OSC32KCTRL_CFD_SetOsc32kPrescaler(OSC32K_DIV_1);
 *
 *      OSC32KCTRL_XOSC32K_SetStartUpTime(XOSC23K_32K_CYCLES);
 * 
 *      OSC32KCTRL_XOSC32K_DisableOnDemand();
 *
 *      OSC32KCTRL_XOSC32K_SelectClockSource(XOSC32K_CRYSTAL);
 *
 *      OSC32KCTRL_XOSC32K_Enable();
 *
 *      //( Once the CSUT is elapsed, the ready status will be true) 
 *      while(!OSC32KCTRL_XOSC32K_IsReady());
 *
 * }
 *
 * ```
 ******************************************************************************/

/** @brief Write Protection Key (device-specific, example value) */
#define OSC32KCTRL_WP_KEY                (0x4F5343U)

/**
 * @brief RTC Clock Source Selection
 */
typedef enum
{
    OSC32KCTRL_RTCSEL_OSC1K    = 0x02U,
    OSC32KCTRL_RTCSEL_OSC32K   = 0x03U,
    OSC32KCTRL_RTCSEL_XOSC1K   = 0x04U,
    OSC32KCTRL_RTCSEL_XOSC32K  = 0x05U
} OSC32KCTRL_RTC_CLOCK;

/**
 * @brief XOSC32K Clock Source Selection
 */
typedef enum
{
    XOSC32K_EXTCLK     = 0x00U,
    XOSC32K_CRYSTAL    = 0x04U
}OSC32KCTRL_XTAL_SOURCE;

/**
 * @brief CFD XOSC32K Prescaler Selection
 */
typedef enum
{
    OSC32K_DIV_1     = 0x0U,
    OSC32K_DIV_2     = 0x1U
}OSC32K_CFD_PRESCALER;
/**
 * @brief XOSC32K Startup Time Selection
 */
typedef enum
{
    XOSC23K_1K_CYCLES   = 0x0U,
    XOSC23K_16K_CYCLES  = 0x1U,
    XOSC23K_32K_CYCLES  = 0x2U

}OSC32KCTRL_CSUT;

/**
 * @brief Interrupt Source Enumeration
 */
typedef enum
{
    OSC32KCTRL_IRQ_XOSC32KRDY  = 0U,
    OSC32KCTRL_IRQ_OSC32KRDY   = 1U,
    OSC32KCTRL_IRQ_CLKFAIL     = 2U
} OSC32KCTRL_IRQ_SOURCE;

/**
 * @brief Callback function type for OSC32KCTRL events
 * @param source  Interrupt source
 */
typedef void (*OSC32KCTRL_CALLBACK)(OSC32KCTRL_IRQ_SOURCE source);

/**
 * @brief Initializes the OSC32KCTRL peripheral.
 * @param None.
 * @return None.
 */
void OSC32KCTRL_Initialize(void);

/**
 * @brief Checks if the OSC32K oscillator is ready.
 * @param None.
 * @return true if the OSC32K oscillator is ready, false otherwise.
 */
bool OSC32KCTRL_OSC32K_IsReady(void);

/**
 * @brief Enables On-Demand mode for the OSC32K oscillator.
 * @param None.
 * @return None.
 */
void OSC32KCTRL_OSC32K_EnableOnDemand(void);

/**
 * @brief Disables On-Demand mode for the OSC32K oscillator.
 * @param None.
 * @return None.
 */
void OSC32KCTRL_OSC32K_DisableOnDemand(void);

/**
 * @brief Reads the On-Demand mode status of the OSC32K oscillator.
 * @param None.
 * @return true if On-Demand mode is enabled, false otherwise.
 */
bool OSC32KCTRL_OSC32K_OnDemandIsEnabled(void);

/**
 * @brief Sets the RTC clock source.
 * @param rtc_sel The clock source selection for the RTC.
 * @return None.
 */
void OSC32KCTRL_RTC_SelectClockSource(OSC32KCTRL_RTC_CLOCK rtc_sel);

/**
 * @brief Gets the current RTC clock source selection.
 * @param None.
 * @return The current RTC clock source selection as an OSC32KCTRL_RTC_CLOCK value.
 */
OSC32KCTRL_RTC_CLOCK OSC32KCTRL_RTC_GetClockSource(void);

/**
 * @brief Checks if the XOSC32K oscillator is ready.
 * @param None.
 * @return true if the XOSC32K oscillator is ready, false otherwise.
 */
bool OSC32KCTRL_XOSC32K_IsReady(void);

/**
 * @brief Selects the external source for the XOSC32K oscillator.
 * @param xtal_source The external crystal or clock source selection for XOSC32K.
 * @return None.
 */
void OSC32KCTRL_XOSC32K_SelectClockSource(OSC32KCTRL_XTAL_SOURCE xtal_source);

/**
 * @brief Enables the XOSC32K oscillator.
 * @param None.
 * @return None.
 */
void OSC32KCTRL_XOSC32K_Enable(void);

/**
 * @brief Disables the XOSC32K oscillator.
 * @param None.
 * @return None.
 */
void OSC32KCTRL_XOSC32K_Disable(void);

/**
 * @brief Enables On-Demand mode for the XOSC32K oscillator.
 * @param None.
 * @return None.
 */
void OSC32KCTRL_XOSC32K_EnableOnDemand(void);

/**
 * @brief Disables On-Demand mode for the XOSC32K oscillator.
 * @param None.
 * @return None.
 */
void OSC32KCTRL_XOSC32K_DisableOnDemand(void);

/**
 * @brief Reads the On-Demand mode status of the XOSC32K oscillator.
 * @param None.
 * @return true if On-Demand mode is enabled, false otherwise.
 */
bool OSC32KCTRL_XOSC32K_OnDemandIsEnabled(void);

/**
 * @brief Sets the startup time for the XOSC32K oscillator.
 * @param startup_time The desired startup time (OSC32KCTRL_CSUT).
 * @return None.
 */
void OSC32KCTRL_XOSC32K_SetStartUpTime(OSC32KCTRL_CSUT startup_time);

/**
 * @brief Gets the current startup time setting for the XOSC32K oscillator.
 * @param None.
 * @return The current startup time setting as an OSC32KCTRL_CSUT value.
 */
OSC32KCTRL_CSUT OSC32KCTRL_XOSC32K_GetStartUpTime(void);

/**
 * @brief Enables Low Power mode for the XOSC32K oscillator.
 * @param None.
 * @return None.
 */
void OSC32KCTRL_XOSC32K_EnableLowPowerMode(void);

/**
 * @brief Disables Low Power mode for the XOSC32K oscillator.
 * @param None.
 * @return None.
 */
void OSC32KCTRL_XOSC32K_DisableLowPowerMode(void);

/**
 * @brief Reads the Low Power mode status of the XOSC32K oscillator.
 * @param None.
 * @return true if Low Power mode is enabled, false otherwise.
 */
bool OSC32KCTRL_XOSC32K_LowPowerIsEnabled(void);

/**
 * @brief Enables the Clock Failure Detection (CFD) feature for XOSC32K.
 * Make sure the XOSC32K oscillator is disabled before calling this function.
 * Not following this guideline can lead to a false clock failure detection.
 * @param None.
 * @return None.
 */
void OSC32KCTRL_CFD_Enable(void);

/**
 * @brief Disables the Clock Failure Detection (CFD) feature.
 * @param None.
 * @return None.
 */
void OSC32KCTRL_CFD_Disable(void);

/**
 * @brief Reads the clock failure status.
 * @param None.
 * @return true if clock failure detected, false otherwise.
 */
bool OSC32KCTRL_CFD_GetClockFailureStatus(void);

/**
 * @brief Enables the clock failure event output for CFD.
 * @param None.
 * @return None.
 */
void OSC32KCTRL_CFD_EnableEventOutput(void);

/**
 * @brief Disabled the clock failure event output for CFD.
 * @param None.
 * @return None.
 */
void OSC32KCTRL_CFD_DisableEventOutput(void);

/**
 * @brief Gets the switch back status for CFD.
 * @param None.
 * @return true if switch back occurred, false otherwise.
 */
bool OSC32KCTRL_CFD_ClockIsSwitched(void);

/**
 * @brief Sets the switch back for CFD if CFD is enabled.
 * @param None.
 * @return None.
 */
void OSC32KCTRL_CFD_SetSwitchBack(void);

/**
 * @brief Returns the status of the switch back field in CFDCTRL.
 * @param None.
 * @return true if switch back is completed, false otherwise.
 */
bool OSC32KCTRL_CFD_GetSwitchBack(void);

/**
 * @brief Sets the OSC32K prescaler for CFD.
 * @param prescaler The prescaler value to set (OSC32K_CFD_PRESCALER).
 * @return None.
 */
void OSC32KCTRL_CFD_SetOsc32kPrescaler(OSC32K_CFD_PRESCALER prescaler);

/**
 * @brief Gets the current OSC32K prescaler setting for CFD.
 * @param None.
 * @return The current OSC32K prescaler setting (OSC32K_CFD_PRESCALER).
 */
OSC32K_CFD_PRESCALER OSC32KCTRL_CFD_GetOsc32kPrescaler(void);

/**
 * @brief Enables the specified OSC32KCTRL interrupt source.
 * @param irq_source The interrupt source to enable (OSC32KCTRL_IRQ_SOURCE).
 * @return None.
 */
void OSC32KCTRL_EnableInterrupt(OSC32KCTRL_IRQ_SOURCE irq_source);

/**
 * @brief Disables the specified OSC32KCTRL interrupt source.
 * @param irq_source The interrupt source to disable (OSC32KCTRL_IRQ_SOURCE).
 * @return None.
 */
void OSC32KCTRL_DisableInterrupt(OSC32KCTRL_IRQ_SOURCE irq_source);

/**
 * @brief Reads the interrupt enable status for the specified OSC32KCTRL interrupt source.
 * @param irq_source The interrupt source to check (OSC32KCTRL_IRQ_SOURCE).
 * @return true if the interrupt is enabled, false otherwise.
 */
bool OSC32KCTRL_InterruptIsEnabled(OSC32KCTRL_IRQ_SOURCE irq_source);

/**
 * @brief Sets the ready flag for the specified OSC32KCTRL interrupt source.
 * @param irq_source The interrupt source for which to set the ready flag (OSC32KCTRL_IRQ_SOURCE).
 * @return None.
 */
void OSC32KCTRL_SetReadyFlag(OSC32KCTRL_IRQ_SOURCE irq_source);

/**
 * @brief Reads the INTFLAGSET register for the specified OSC32KCTRL interrupt source.
 * @param irq_source The interrupt source to check (OSC32KCTRL_IRQ_SOURCE).
 * @return true if the interrupt flag is set, false otherwise.
 */
bool OSC32KCTRL_IntFlagSetIsEnabled(OSC32KCTRL_IRQ_SOURCE irq_source);

/**
 * @brief Reads the INTFLAG register for the specified OSC32KCTRL interrupt source.
 * @param irq_source The interrupt source to check (OSC32KCTRL_IRQ_SOURCE).
 * @return true if the interrupt flag is set, false otherwise.
 */
bool OSC32KCTRL_InterruptFlagIsSet(OSC32KCTRL_IRQ_SOURCE irq_source);

/**
 * @brief Clears the interrupt flag for the specified OSC32KCTRL interrupt source.
 * @param irq_source The interrupt source for which to clear the flag (OSC32KCTRL_IRQ_SOURCE).
 * @return None.
 */
void OSC32KCTRL_ClearInterruptFlag(OSC32KCTRL_IRQ_SOURCE irq_source);

/**
 * @brief Enables write protection for the OSC32KCTRL peripheral.
 * @param None.
 * @return None.
 */
void OSC32KCTRL_EnableWriteProtection(void);

/**
 * @brief Disables write protection for the OSC32KCTRL peripheral.
 * @param None.
 * @return None.
 */
void OSC32KCTRL_DisableWriteProtection(void);

/**
 * @brief Reads the current write protection status for the OSC32KCTRL peripheral.
 * @param None.
 * @return true if write protection is enabled, false otherwise.
 */
bool OSC32KCTRL_WriteProtectionIsEnabled(void);

/**
 * @brief Enables the write lock for the OSC32KCTRL write protection register.
 * @param None.
 * @return None.
 */
void OSC32KCTRL_WPCTRL_EnableWriteLock(void);

/**
 * @brief Registers a callback function for OSC32KCTRL interrupt events.
 * @param callback Pointer to the callback function to be registered.
 * @return None.
 */
void OSC32KCTRL_SetCallbackHandler(OSC32KCTRL_CALLBACK callback);

#ifdef __cplusplus
}
#endif

#endif /* PLIB_OSC32KCTRL_H */
