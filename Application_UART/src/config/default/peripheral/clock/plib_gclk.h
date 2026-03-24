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
 * @file plib_gclk.h
 * @brief Generic Clock Controller(GCLK) Peripheral Library Interface
 *
 * @details This header file provides the interface definitions, enumerations, 
 * structures, and function prototypes for configuring and controlling the Generic 
 * Clock (GCLK) module in supported microcontrollers. The API allows for flexible 
 * clock generator and peripheral channel management, including source selection, 
 * division configuration, output control, standby operation, and synchronization 
 * status checking.
 ******************************************************************************/

#ifndef PLIB_GCLK_H
#define PLIB_GCLK_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <pic32c.h>

/**************************************************************************************
 * @brief Example: Initialize GCLK Generator 2
 *
 * This example demonstrates how to configure and initialize GCLK Generator 2
 * using the PLIB GCLK APIs. It sets the generator source to 32K Internal oscillator, 
 * division parameters, output value, enables output, enables standby run, and finally 
 * enables the generator. It also waits for synchronization to complete.
 *
 * ```c
 * #include "plib_gclk.h"
 *
 * int main(void)
 * {
 *     uint16_t divide_factor = 8; // Example division factor
 *     bool output_off_value = false; // Output low when generator is off
 *
 *     // Set GCLK Generator 2 source to External 32kHz Oscillator
 *     GCLK_SetGeneratorSource(GCLK_GENERATOR_2, GCLK_SRC_OSC32K);
 *
 *     // Set division parameters: integer division, no improved duty cycle
 *     GCLK_SetDivisionParameters(GCLK_GENERATOR_2, divide_factor, GCLK_DIVISION_INTEGER, false);
 *
 *     // Set output value when generator is off (false = low)
 *     GCLK_SetOutputOffValue(GCLK_GENERATOR_2, output_off_value);
 *
 *     // Enable output for GCLK Generator 2
 *     GCLK_SetOutputEnable(GCLK_GENERATOR_2, true);
 *
 *     // Enable standby run for GCLK Generator 2
 *     GCLK_EnableStandbyRun(GCLK_GENERATOR_2);
 *
 *     // Enable GCLK Generator 2
 *     GCLK_GeneratorEnable(GCLK_GENERATOR_2);
 *
 *     // Application code can proceed here
 *
 *     return 0;
 * }
 * ```
 **************************************************************************************/

/**
 * @brief Select a specific Generic Clock Generator in the GCLK module.
 */
typedef enum
{
    #if defined(GCLK_GENCTRL0_REG_OFST)
    GCLK_GENERATOR_0,
    #endif
    #if defined(GCLK_GENCTRL1_REG_OFST)
    GCLK_GENERATOR_1,
    #endif
    #if defined(GCLK_GENCTRL2_REG_OFST)
    GCLK_GENERATOR_2,
    #endif
    #if defined(GCLK_GENCTRL3_REG_OFST)
    GCLK_GENERATOR_3,
    #endif
    #if defined(GCLK_GENCTRL4_REG_OFST)
    GCLK_GENERATOR_4,
    #endif
    #if defined(GCLK_GENCTRL5_REG_OFST)
    GCLK_GENERATOR_5,
    #endif
    #if defined(GCLK_GENCTRL6_REG_OFST)
    GCLK_GENERATOR_6,
    #endif
    #if defined(GCLK_GENCTRL7_REG_OFST)
    GCLK_GENERATOR_7,
    #endif
    #if defined(GCLK_GENCTRL8_REG_OFST)
    GCLK_GENERATOR_8,
    #endif
} GCLK_GENERATOR_ID;

/**
 * @brief Select a specific Peripheral control in the GCLK module.
 */
typedef enum{
    #if defined(GCLK_PCHCTRL0_REG_OFST)
        GCLK_PCHCCTRL_0 = 0,
    #endif
    #if defined(GCLK_PCHCTRL1_REG_OFST)
        GCLK_PCHCCTRL_1,
    #endif
    #if defined(GCLK_PCHCTRL2_REG_OFST)
        GCLK_PCHCCTRL_2,
    #endif
    #if defined(GCLK_PCHCTRL3_REG_OFST)
        GCLK_PCHCCTRL_3,
    #endif
    #if defined(GCLK_PCHCTRL4_REG_OFST)
        GCLK_PCHCCTRL_4,
    #endif
    #if defined(GCLK_PCHCTRL5_REG_OFST)
        GCLK_PCHCCTRL_5,
    #endif
    #if defined(GCLK_PCHCTRL6_REG_OFST)
        GCLK_PCHCCTRL_6,
    #endif
    #if defined(GCLK_PCHCTRL7_REG_OFST)
        GCLK_PCHCCTRL_7,
    #endif
    #if defined(GCLK_PCHCTRL8_REG_OFST)
        GCLK_PCHCCTRL_8,
    #endif
    #if defined(GCLK_PCHCTRL9_REG_OFST)
        GCLK_PCHCCTRL_9,
    #endif
    #if defined(GCLK_PCHCTRL10_REG_OFST)
        GCLK_PCHCCTRL_10,
    #endif
    #if defined(GCLK_PCHCTRL11_REG_OFST)
        GCLK_PCHCCTRL_11,
    #endif
    #if defined(GCLK_PCHCTRL12_REG_OFST)
        GCLK_PCHCCTRL_12,
    #endif
    #if defined(GCLK_PCHCTRL13_REG_OFST)
        GCLK_PCHCCTRL_13,
    #endif
    #if defined(GCLK_PCHCTRL14_REG_OFST)
        GCLK_PCHCCTRL_14,
    #endif
    #if defined(GCLK_PCHCTRL15_REG_OFST)
        GCLK_PCHCCTRL_15,
    #endif
    #if defined(GCLK_PCHCTRL16_REG_OFST)
        GCLK_PCHCCTRL_16,
    #endif
    #if defined(GCLK_PCHCTRL17_REG_OFST)
        GCLK_PCHCCTRL_17,
    #endif
    #if defined(GCLK_PCHCTRL18_REG_OFST)
        GCLK_PCHCCTRL_18,
    #endif
    #if defined(GCLK_PCHCTRL19_REG_OFST)
        GCLK_PCHCCTRL_19,
    #endif
    #if defined(GCLK_PCHCTRL20_REG_OFST)
        GCLK_PCHCCTRL_20,
    #endif
    #if defined(GCLK_PCHCTRL21_REG_OFST)
        GCLK_PCHCCTRL_21,
    #endif
    #if defined(GCLK_PCHCTRL22_REG_OFST)
        GCLK_PCHCCTRL_22,
    #endif
    #if defined(GCLK_PCHCTRL23_REG_OFST)
        GCLK_PCHCCTRL_23,
    #endif
    #if defined(GCLK_PCHCTRL24_REG_OFST)
        GCLK_PCHCCTRL_24,
    #endif
    #if defined(GCLK_PCHCTRL25_REG_OFST)
        GCLK_PCHCCTRL_25,
    #endif
    #if defined(GCLK_PCHCTRL26_REG_OFST)
        GCLK_PCHCCTRL_26,
    #endif
    #if defined(GCLK_PCHCTRL27_REG_OFST)
        GCLK_PCHCCTRL_27,
    #endif
    #if defined(GCLK_PCHCTRL28_REG_OFST)
        GCLK_PCHCCTRL_28,
    #endif
    #if defined(GCLK_PCHCTRL29_REG_OFST)
        GCLK_PCHCCTRL_29,
    #endif
    #if defined(GCLK_PCHCTRL30_REG_OFST)
        GCLK_PCHCCTRL_30,
    #endif
    #if defined(GCLK_PCHCTRL31_REG_OFST)
        GCLK_PCHCCTRL_31,
    #endif
    #if defined(GCLK_PCHCTRL32_REG_OFST)
        GCLK_PCHCCTRL_32,
    #endif
    #if defined(GCLK_PCHCTRL33_REG_OFST)
        GCLK_PCHCCTRL_33,
    #endif
    #if defined(GCLK_PCHCTRL34_REG_OFST)
        GCLK_PCHCCTRL_34,
    #endif
    #if defined(GCLK_PCHCTRL35_REG_OFST)
        GCLK_PCHCCTRL_35,
    #endif
    #if defined(GCLK_PCHCTRL36_REG_OFST)
        GCLK_PCHCCTRL_36,
    #endif
    #if defined(GCLK_PCHCTRL37_REG_OFST)
        GCLK_PCHCCTRL_37,
    #endif
    #if defined(GCLK_PCHCTRL38_REG_OFST)
        GCLK_PCHCCTRL_38,
    #endif
    #if defined(GCLK_PCHCTRL39_REG_OFST)
        GCLK_PCHCCTRL_39,
    #endif
    #if defined(GCLK_PCHCTRL40_REG_OFST)
        GCLK_PCHCCTRL_40,
    #endif
    #if defined(GCLK_PCHCTRL41_REG_OFST)
        GCLK_PCHCCTRL_41,
    #endif
    #if defined(GCLK_PCHCTRL42_REG_OFST)
        GCLK_PCHCCTRL_42,
    #endif
} GCLK_PERIPHERAL_CHANNEL_ID;

/**
 * @brief Specifies the method used to divide the clock source frequency for a GCLK generator.
 */
typedef enum
{
    GCLK_DIVISION_INTEGER               = GCLK_GENCTRL_DIVSEL_DIV1_Val,/**< Integer division: fGCLK = fSRC / DIV */
    GCLK_DIVISION_POWER_OF_TWO_PLUS_ONE = GCLK_GENCTRL_DIVSEL_DIV2_Val /**< Power-of-two-plus-one division: fGCLK = fSRC / 2^(DIV+1) */
} GCLK_DIVIDE_TYPE;

/**
 * @brief GCLK generator clock source selection
 */
typedef enum
{
    #if defined(GCLK_GENCTRL_SRC_OSCHF_Val)
    GCLK_SRC_OSCHF         = GCLK_GENCTRL_SRC_OSCHF_Val, /**< Internal High-Frequency Oscillator */
    #endif
    #if defined(GCLK_GENCTRL_SRC_XOSC_Val)
    GCLK_SRC_XOSC          = GCLK_GENCTRL_SRC_XOSC_Val, /** XOSC oscillator output */
    #endif
    #if defined(GCLK_GENCTRL_SRC_GCLKIN_Val)
    GCLK_SRC_GCLKIN        = GCLK_GENCTRL_SRC_GCLKIN_Val, /** Generator input pad */
    #endif
    #if defined(GCLK_GENCTRL_SRC_GCLKGEN1_Val)
    GCLK_SRC_GCLKGEN1      = GCLK_GENCTRL_SRC_GCLKGEN1_Val, /** Generator 1 Output */
    #endif
    #if defined(GCLK_GENCTRL_SRC_OSC32K_Val)
    GCLK_SRC_OSC32K        = GCLK_GENCTRL_SRC_OSC32K_Val,/** Internal 32kHz Oscillator */
    #endif
    #if defined(GCLK_GENCTRL_SRC_OSCULP32K_Val)
    GCLK_SRC_OSCULP32K     = GCLK_GENCTRL_SRC_OSCULP32K_Val, /** OSCULP32K oscillator output */
    #endif
    #if defined(GCLK_GENCTRL_SRC_XOSC32K_Val)
    GCLK_SRC_XOSC32K       = GCLK_GENCTRL_SRC_XOSC32K_Val, /** External 32kHz Oscillator */
    #endif
    #if defined(GCLK_GENCTRL_SRC_OSC48M_Val)
    GCLK_SRC_OSC48M        = GCLK_GENCTRL_SRC_OSC48M_Val, /** OSC48M oscillator output */
    #endif
    #if defined(GCLK_GENCTRL_SRC_FDPLL96M_Val)
    GCLK_SRC_FDPLL96M      = GCLK_GENCTRL_SRC_FDPLL96M_Val, /**< FDPLL96M output */
    #endif
} GCLK_SOURCE;


/**
 * @brief Initializes the GCLK module.
 * @param None.
 * @return None.
 */
void GCLK_Initialize(void);

/**
 * @brief Checks synchronization status of a GCLK generator control register.
 * @param generator_id The GCLK generator ID to check.
 * @return true if synchronization is ongoing for the selected generator, false otherwise.
 */
bool GCLK_GetGeneratorControlSyncStatus(GCLK_GENERATOR_ID generator_id);

/**
 * @brief Sets the clock source for a specified GCLK generator.
 * Before changing the source in GENERATOR 0, ensure that the ONDEMAND feature 
 * of the source is enabled.
 * @param generator_id The GCLK generator to configure.
 * @param source The clock source to select for the generator.
 * @return None.
 */
void GCLK_SetGeneratorSource(GCLK_GENERATOR_ID generator_id, GCLK_SOURCE source);

/**
 * @brief Gets the clock source for a specified GCLK generator.
 * @param generator_id The GCLK generator to query.
 * @return The current clock source of the specified generator.
 */
GCLK_SOURCE GCLK_GetGeneratorSource(GCLK_GENERATOR_ID generator_id);

/**
 * @brief Sets the division factor and type for a GCLK generator.
 * @param generator_id The GCLK generator to configure.
 * @param divide_factor The division factor to set.
 * @param divide_type The division selection type to set.
 * @param improve_duty_cycle Set to true to enable improved duty cycle, false to disable.
 * @return None.
 */
void GCLK_SetDivisionParameters(GCLK_GENERATOR_ID generator_id, uint16_t divide_factor, GCLK_DIVIDE_TYPE divide_type, bool improve_duty_cycle);

/**
 * @brief Returns the division type for a specified GCLK generator.
 * @param generator_id The GCLK generator to query.
 * @return The current division type of the specified generator.
 */
GCLK_DIVIDE_TYPE GCLK_GetDivideType(GCLK_GENERATOR_ID generator_id);

/**
 * @brief Returns the division factor for a specified GCLK generator.
 * @param generator_id The GCLK generator to query.
 * @return The current division factor of the specified generator.
 */
uint16_t GCLK_GetDivideFactor(GCLK_GENERATOR_ID generator_id);

/**
 * @brief Sets the output value when the GCLK generator is off.
 * @param generator_id The GCLK generator to configure.
 * @param output_off_value Value to set when the generator is off (true for high, false for low).
 * @return None.
 */
void GCLK_SetOutputOffValue(GCLK_GENERATOR_ID generator_id, bool output_off_value);

/**
 * @brief Enables or disables output for a GCLK generator.
 * @param generator_id The GCLK generator to configure.
 * @param output_enable Set to true to enable output, false to disable.
 * @return None.
 */
void GCLK_SetOutputEnable(GCLK_GENERATOR_ID generator_id, bool output_enable);

/**
 * @brief Enables GCLK generator operation in standby mode.
 * @param generator_id The GCLK generator to configure.
 * @return None.
 */
void GCLK_EnableStandbyRun(GCLK_GENERATOR_ID generator_id);

/**
 * @brief Disables GCLK generator operation in standby mode.
 * @param generator_id The GCLK generator to configure.
 * @return None.
 */
void GCLK_DisableStandbyRun(GCLK_GENERATOR_ID generator_id);

/**
 * @brief Enables the specified GCLK generator.
 * @param generator_id The GCLK generator to enable.
 * @return None.
 */
void GCLK_GeneratorEnable(GCLK_GENERATOR_ID generator_id);

/**
 * @brief Disables the specified GCLK generator.
 * @param generator_id The GCLK generator to disable.
 * @return None.
 */
void GCLK_GeneratorDisable(GCLK_GENERATOR_ID generator_id);

/**
 * @brief Assigns a GCLK generator to a peripheral channel.
 * @param channel_id The peripheral channel to configure.
 * @param generator_id The GCLK generator to assign to the channel.
 * @return None.
 */
void GCLK_SetPeripheralChannelGenSrc(GCLK_PERIPHERAL_CHANNEL_ID channel_id, GCLK_GENERATOR_ID generator_id);

/**
 * @brief Enables a GCLK peripheral channel.
 * @param channel_id The peripheral channel to enable.
 * @return None.
 */
void GCLK_EnablePeripheralChannel(GCLK_PERIPHERAL_CHANNEL_ID channel_id);

/**
 * @brief Disables a GCLK peripheral channel.
 * @param channel_id The peripheral channel to disable.
 * @return None.
 */
void GCLK_PeripheralChannelDisable(GCLK_PERIPHERAL_CHANNEL_ID channel_id);

/**
 * @brief Checks if a GCLK peripheral channel is enabled.
 * @param channel_id The peripheral channel to check.
 * @return true if the channel is enabled, false otherwise.
 */
bool GCLK_PeripheralChannelIsEnabled(GCLK_PERIPHERAL_CHANNEL_ID channel_id);

/**
 * @brief Enables write lock for a GCLK peripheral channel.
 * @param channel_id The peripheral channel to lock.
 * @return None.
 */
void GCLK_EnablePeripheralChannelWriteLock(GCLK_PERIPHERAL_CHANNEL_ID channel_id);

#ifdef __cplusplus
}
#endif

#endif /* PLIB_GCLK_H */