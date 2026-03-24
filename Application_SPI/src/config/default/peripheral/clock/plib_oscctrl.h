/*******************************************************************************
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
*********************************************************************************/
/********************************************************************************
* @file plib_oscctrl.h
* @brief Oscillator Controller Peripheral Library (PLIB) interface.
*
* @details This file provides function interface to configure, control, and 
* monitor the internal high-frequency oscillator (OSCHF) using the OSCCTRL hardware 
* module. It includes register definitions, interrupt and event handling, frequency 
* selection, autotune, on-demand operation, and write protection mechanisms.
***********************************************************************************/

#ifndef PLIB_OSCCTRL_H
#define PLIB_OSCCTRL_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <pic32c.h>

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************************
 * @brief Example: Initialize and Configure OSCHF Oscillator and Wait for Readiness
 *
 * This example demonstrates how to configure the internal high-frequency oscillator (OSCHF),
 * and wait for the oscillator to become ready usingthe PLIB OSCHF APIs. 
 * It sets the frequency and waits for the oscillator to indicate readiness before proceeding.
 *
 * ```c
 * #include "plib_oscctrl.h"
 *
 * int main(void)
 * {
 *     OSCCTRL_OSCHF_EnableAutotune();
 *     OSCCTRL_OSCHF_DisableOnDemand();
 *     OSCCTRL_OSCHF_SetFrequency(OSCCTRL_OSCHF_FREQ_1M);
 *
 *     while(!OSCCTRL_OSCHF_IsReady())
 *     {
 *         // Wait for the oscillator to become ready
 *     }
 *
 *     return 0;
 * }
 * ```
 ******************************************************************************************/

/** @brief Write protection key for OSCCTRL registers */
#define OSCCTRL_WP_KEY                (0x4F5343U)

/** 
 * @brief OSCHF ready event callback function type
 * @param None.
 */
typedef void (*OSCCTRL_OSCHF_READY_CALLBACK)(void);

/** 
 * @brief OSCHF frequency selection enumeration 
 */
typedef enum
{
    OSCCTRL_OSCHF_FREQ_1M  = 0x00U,
    OSCCTRL_OSCHF_FREQ_2M  = 0x01U,
    OSCCTRL_OSCHF_FREQ_3M  = 0x02U,
    OSCCTRL_OSCHF_FREQ_4M  = 0x03U,
    OSCCTRL_OSCHF_FREQ_8M  = 0x05U,
    OSCCTRL_OSCHF_FREQ_12M = 0x06U,
    OSCCTRL_OSCHF_FREQ_16M = 0x07U,
    OSCCTRL_OSCHF_FREQ_20M = 0x08U,
    OSCCTRL_OSCHF_FREQ_24M = 0x09U
} OSCCTRL_OSCHF_FREQ;

/**
 * @brief Initializes the OSCHF oscillator.
 * @param None.
 * @return None.
 */
void OSCCTRL_OSCHF_Initialize(void);

/**
 * @brief This function sets the frequency selection value for the internal OSCHF Oscillator.
 * @param freq_sel Frequency selection value to be set.
 * @return None.
 */
void OSCCTRL_OSCHF_SetFrequency(OSCCTRL_OSCHF_FREQ freq_sel);

/**
 * @brief Returns the current frequency of the internal OSCHF Oscillator.
 * @param None.
 * @return The current frequency as per the frequency selection.
 */
uint32_t OSCCTRL_OSCHF_GetFrequency(void);

/**
 * @brief Enables automatic tuning for the OSCHF Oscillator.
 * @param None.
 * @return None.
 */
void OSCCTRL_OSCHF_EnableAutotune(void);

/**
 * @brief Disables automatic tuning for the OSCHF Oscillator.
 * @param None.
 * @return None.
 */
void OSCCTRL_OSCHF_DisableAutotune(void);

/**
 * @brief Checks if the autotune feature is enabled for the OSCHF oscillator.
 * @param None.
 * @return true if automatic tuning is enabled, false otherwise.
 */
bool OSCCTRL_OSCHF_AutotuneIsEnabled(void);

/**
 * @brief Enables On-Demand mode for the OSCHF Oscillator.
 * @param None.
 * @return None.
 */
void OSCCTRL_OSCHF_EnableOnDemand(void);

/**
 * @brief Disables On-Demand mode for the OSCHF Oscillator.
 * @param None.
 * @return None.
 */
void OSCCTRL_OSCHF_DisableOnDemand(void);

/**
 * @brief Checks if the On-Demand feature is enabled for the OSCHF oscillator.
 * @param None.
 * @return true if On-Demand mode is enabled, false otherwise.
 */
bool OSCCTRL_OSCHF_OnDemandIsEnabled(void);

/**
 * @brief Enables write protection for the OSCHF Oscillator registers.
 * @param None.
 * @return None.
 */
void OSCCTRL_EnableWriteProtection(void);

/**
 * @brief Disables write protection for the OSCHF Oscillator registers.
 * @param None.
 * @return None.
 */
void OSCCTRL_DisableWriteProtection(void);

/**
 * @brief Checks if write protection is enabled for the OSCHF oscillator registers.
 * @param None.
 * @return true if write protection is enabled, false otherwise.
 */
bool OSCCTRL_WriteProtectionIsEnabled(void);

/**
 * @brief Enables the write protection lock for the WPCTRL register.
 * @param None.
 * @return None.
 */
void OSCCTRL_WPCTRL_EnableWriteLock(void);

/**
 * @brief Checks if the Write Protection Lock is enabled for the WPCTRL register.
 * @param None.
 * @return true if write protection lock is enabled, false otherwise.
 */
bool OSCCTRL_WPCTRL_WriteLockIsEnabled(void);

/**
 * @brief Sets the manual tuning value for the OSCHF Oscillator.
 * Note that Autotune must be disabled to use manual tuning. Failing to do so 
 * will issue a pslverr.
 * @param tune_value The manual tuning value to be set (2's complement format).
 * @return None
 */
void OSCCTRL_OSCHF_SetManualTune(uint8_t tune_value);

/**
 * @brief Gets the current manual tuning value of the OSCHF oscillator.
 * @param None.
 * @return The current manual tuning value.
 */
uint8_t OSCCTRL_OSCHF_GetFrequencyTune(void);

/**
 * @brief Checks if the OSCHF Oscillator is ready.
 * @param None.
 * @return true if the oscillator is ready, false otherwise.
 */
bool OSCCTRL_OSCHF_IsReady(void);


/**
 * @brief Enables the ready interrupt for the OSCHF Oscillator.
 * @param None.
 * @return None.
 */
void OSCCTRL_OSCHF_EnableReadyInterrupt(void);

/**
 * @brief Checks if the ready interrupt is enabled for the OSCHF oscillator.
 * @param None.
 * @return true if interrupt is enabled, false otherwise.
 */
bool OSCCTRL_OSCHF_ReadyInterruptIsEnabled(void);


/**
 * @brief Disables the ready interrupt for the OSCHF Oscillator.
 * @param None.
 * @return None.
 */
void OSCCTRL_OSCHF_DisableReadyInterrupt(void);

/**
 * @brief Checks if the ready interrupt flag is set for the OSCHF oscillator.
 * @param None.
 * @return true if interrupt flag is set, false otherwise.
 */
bool OSCCTRL_OSCHF_InterruptFlagIsSet(void);

/**
 * @brief Clears the ready interrupt flag for the OSCHF oscillator.
 * @param None.
 * @return None.
 */
void OSCCTRL_OSCHF_ClearInterruptFlag(void);

/**
 * @brief Asserts the ready interrupt flag for the OSCHF Oscillator.
 * It is used for testing purposes to simulate the interrupt condition.
 * @param None.
 * @return None.
 */
void OSCCTRL_OSCHF_SetReadyInterruptFlag(void);

/**
 * @brief Registers a callback function for the OSCHF ready interrupt.
 * This function stores a user-provided callback to be called when the 
 * OSCHF Oscillator ready interrupt occurs.
 * @param callback Pointer to the callback function to be registered.
 * @return None.
 */
void OSCCTRL_OSCHF_SetReadyCallbackHandler(OSCCTRL_OSCHF_READY_CALLBACK callback);

#ifdef __cplusplus
}
#endif

#endif /* PLIB_OSCCTRL_H */
