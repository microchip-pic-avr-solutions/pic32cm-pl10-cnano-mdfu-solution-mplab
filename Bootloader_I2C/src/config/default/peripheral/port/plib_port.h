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
 *******************************************************************************/

/**
 * @file plib_port.h
 * @brief GPIO Peripheral Library Interface
 *
 * This file provides the interface for configuring and controlling the GPIO peripheral.
 */

#ifndef PLIB_PORT_H_
#define PLIB_PORT_H_

#include <stdint.h>
#include <stdbool.h>
#include <pic32c.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Example usage of the PORT PLIB interface for blinking an LED.*/

/**
 * @par Example
 * @code
 * #include "plib_port.h"
 * #include <stdio.h>
 *
 * #define LED_PIN  PIN_PB02  //PIC32CM-PL10(48 pin device) Cnano onboard LED pin
 * 
 * void delay_ms(uint32_t ms);
 * 
 * int main(void)
 * {
 *
 *     // Initialize the pin without a callback
 *     PORT_Setup(LED_PIN);
 *
 *     // Set the pin as output
 *     PORT_SetDirection(LED_PIN, GPIO_OUTPUT);
 *
 *     // Set output low (LED is active low, LED is turned ON)
 *     PORT_SetOutput(LED_PIN, 0);
 *       
 *     while (1)
 *      {
 *          delay_ms(250);
 *          PORT_Toggle(LED_PIN);
 *      }
 * }
 * 
 * // This assumes the core clock frequency is 4MHz(default frequency)
 * void delay_ms(uint32_t ms)
 * {
 *      uint32_t i,j;
 *      for(i = 0;i<ms;i++)
 *      {
 *          for(j = 0;j< 4000;j++);
 *      } 
 * }
 * @endcode
 */

/**
 * @enum PORT_PIN
 * @brief GPIO port pin identifiers.
 *
 * This enumeration lists all available GPIO port pins.
 * Use these values to refer to specific pins in the API functions.
 */
typedef enum
{
    PORT_PIN_PA00 = 0U,
    PORT_PIN_PA01 = 1U,
    PORT_PIN_PA02 = 2U,
    PORT_PIN_PA03 = 3U,
    PORT_PIN_PA04 = 4U,
    PORT_PIN_PA05 = 5U,
    PORT_PIN_PA06 = 6U,
    PORT_PIN_PA07 = 7U,
    PORT_PIN_PA08 = 8U,
    PORT_PIN_PA09 = 9U,
    PORT_PIN_PA10 = 10U,
    PORT_PIN_PA11 = 11U,
    PORT_PIN_PA12 = 12U,
    PORT_PIN_PA13 = 13U,
    PORT_PIN_PA14 = 14U,
    PORT_PIN_PA15 = 15U,
    PORT_PIN_PA16 = 16U,
    PORT_PIN_PA17 = 17U,
    PORT_PIN_PA18 = 18U,
    PORT_PIN_PA19 = 19U,
    PORT_PIN_PA20 = 20U,
    PORT_PIN_PA21 = 21U,
    PORT_PIN_PA22 = 22U,
    PORT_PIN_PA23 = 23U,
    PORT_PIN_PA24 = 24U,
    PORT_PIN_PA25 = 25U,
    PORT_PIN_PA27 = 27U,
    PORT_PIN_PA28 = 28U,
    PORT_PIN_PA30 = 30U,
    PORT_PIN_PA31 = 31U,

    PORT_PIN_PB00 = 32U,
    PORT_PIN_PB01 = 33U,
    PORT_PIN_PB02 = 34U,
    PORT_PIN_PB03 = 35U,
    PORT_PIN_PB04 = 36U,
    PORT_PIN_PB05 = 37U,
    PORT_PIN_PB06 = 38U,
    PORT_PIN_PB07 = 39U,
    PORT_PIN_PB08 = 40U,
    PORT_PIN_PB09 = 41U,
    PORT_PIN_PB10 = 42U,
    PORT_PIN_PB11 = 43U,
    PORT_PIN_PB12 = 44U,
    PORT_PIN_PB13 = 45U,
    PORT_PIN_PB14 = 46U,
    PORT_PIN_PB15 = 47U,
    PORT_PIN_PB16 = 48U,
    PORT_PIN_PB17 = 49U,
    PORT_PIN_PB18 = 50U,
    PORT_PIN_PB19 = 51U,
    PORT_PIN_PB20 = 52U,
    PORT_PIN_PB21 = 53U,
    PORT_PIN_PB22 = 54U,
    PORT_PIN_PB23 = 55U,
    PORT_PIN_PB24 = 56U,
    PORT_PIN_PB25 = 57U,
    PORT_PIN_PB30 = 62U,
    PORT_PIN_PB31 = 63U,

    PORT_PIN_PC00 = 64U,
    PORT_PIN_PC01 = 65U,
    PORT_PIN_PC02 = 66U,
    PORT_PIN_PC03 = 67U,
    PORT_PIN_PC05 = 69U,
    PORT_PIN_PC06 = 70U,
    PORT_PIN_PC07 = 71U,
    PORT_PIN_PC08 = 72U,
    PORT_PIN_PC09 = 73U,
    PORT_PIN_PC10 = 74U,
    PORT_PIN_PC11 = 75U,
    PORT_PIN_PC12 = 76U,
    PORT_PIN_PC13 = 77U,
    PORT_PIN_PC14 = 78U,
    PORT_PIN_PC15 = 79U,
    PORT_PIN_PC16 = 80U,
    PORT_PIN_PC17 = 81U,
    PORT_PIN_PC18 = 82U,
    PORT_PIN_PC19 = 83U,
    PORT_PIN_PC20 = 84U,
    PORT_PIN_PC21 = 85U,
    PORT_PIN_PC24 = 88U,
    PORT_PIN_PC25 = 89U,
    PORT_PIN_PC26 = 90U,
    PORT_PIN_PC27 = 91U,
    PORT_PIN_PC28 = 92U,

    PORT_PIN_NONE = 65535U ///< No pin selected
} PORT_PIN;

/**
 * @enum PORT_DIRECTION
 * @brief GPIO port pin direction.
 *
 * This enumeration defines the direction of a GPIO pin.
 */
typedef enum
{
    GPIO_INPUT,  ///< Input (default)
    GPIO_OUTPUT  ///< Output
} PORT_DIRECTION;

/**
 * @enum GPIO_OUTPUT_MODE
 * @brief GPIO output mode.
 *
 * This enumeration specifies the output mode for a GPIO pin.
 */
typedef enum
{
    GPIO_PUSH_PULL, ///< Push-pull (default)
    GPIO_OPEN_DRAIN ///< Open-drain
} GPIO_OUTPUT_MODE;

/**
 * @enum GPIO_PULL_RESISTOR
 * @brief GPIO pull resistor configuration.
 *
 * This enumeration specifies the pull resistor configuration for a GPIO pin.
 */
typedef enum
{
    GPIO_PULL_NONE, ///< None (default)
    GPIO_PULL_UP,   ///< Pull-up
    GPIO_PULL_DOWN  ///< Pull-down
} GPIO_PULL_RESISTOR;

/**
 * @enum PORT_EVENT_INPUT_CHANNEL
 * @brief GPIO port event input channel.
 *
 * This enumeration specifies the event input channels for the GPIO port.
 */
typedef enum
{
    PORT_EVENT_INPUT_CHANNEL_0 = PORT_EVCTRL_PORTEI0_Pos,
    PORT_EVENT_INPUT_CHANNEL_1 = PORT_EVCTRL_PORTEI1_Pos,
    PORT_EVENT_INPUT_CHANNEL_2 = PORT_EVCTRL_PORTEI2_Pos,
    PORT_EVENT_INPUT_CHANNEL_3 = PORT_EVCTRL_PORTEI3_Pos
} PORT_EVENT_INPUT_CHANNEL;

/**
 * @enum PORT_EVENT_ACTION
 * @brief GPIO port event action.
 *
 * This enumeration defines the possible actions triggered by a port event.
 */
typedef enum
{
    PORT_EVENT_ACTION_OUT,
    PORT_EVENT_ACTION_SET,
    PORT_EVENT_ACTION_CLR,
    PORT_EVENT_ACTION_TGL
} PORT_EVENT_ACTION;

/**
 * @enum PORT_PERIPHERAL_FUNCTION
 * @brief GPIO port peripheral function selection.
 *
 * This enumeration specifies the peripheral function assigned to a GPIO pin.
 */
typedef enum
{
    #if defined(PORT_PMUX_PMUXO_A)
        PORT_PERIPHERAL_FUNC_A,
    #endif
    #if defined(PORT_PMUX_PMUXO_B)
        PORT_PERIPHERAL_FUNC_B,
    #endif
    #if defined(PORT_PMUX_PMUXO_C)
        PORT_PERIPHERAL_FUNC_C,
    #endif
    #if defined(PORT_PMUX_PMUXO_D)
        PORT_PERIPHERAL_FUNC_D,
    #endif
    #if defined(PORT_PMUX_PMUXO_E)
        PORT_PERIPHERAL_FUNC_E,
    #endif
    #if defined(PORT_PMUX_PMUXO_F)
        PORT_PERIPHERAL_FUNC_F,
    #endif
    #if defined(PORT_PMUX_PMUXO_G)
        PORT_PERIPHERAL_FUNC_G,
    #endif
    #if defined(PORT_PMUX_PMUXO_H)
        PORT_PERIPHERAL_FUNC_H,
    #endif
    #if defined(PORT_PMUX_PMUXO_I)
        PORT_PERIPHERAL_FUNC_I,
    #endif
    #if defined(PORT_PMUX_PMUXO_J)
        PORT_PERIPHERAL_FUNC_J,
    #endif
    #if defined(PORT_PMUX_PMUXO_K)
        PORT_PERIPHERAL_FUNC_K,
    #endif
} PORT_PERIPHERAL_FUNCTION;
/**
 * @def PORT_PLIB_OK
 * @brief Operation completed successfully.
 */
#define PORT_PLIB_OK                (0)
/**
 * @def PORT_PLIB_ERROR
 * @brief Unspecified error occurred.
 */
#define PORT_PLIB_ERROR             (-1)
/**
 * @def PORT_PLIB_ERROR_BUSY
 * @brief Resource is busy.
 */
#define PORT_PLIB_ERROR_BUSY        (-2)
/**
 * @def PORT_PLIB_ERROR_TIMEOUT
 * @brief Operation timed out.
 */
#define PORT_PLIB_ERROR_TIMEOUT     (-3)
/**
 * @def PORT_PLIB_ERROR_UNSUPPORTED
 * @brief Operation is not supported.
 */
#define PORT_PLIB_ERROR_UNSUPPORTED (-4)
/**
 * @def PORT_PLIB_ERROR_PARAMETER
 * @brief Invalid parameter provided.
 */
#define PORT_PLIB_ERROR_PARAMETER   (-5)
/**
 * @def PORT_PLIB_ERROR_SPECIFIC
 * @brief Specific error code for driver implementation.
 */
#define PORT_PLIB_ERROR_SPECIFIC    (-6)
/** @} */

/**
 * @brief Initialize the specific pin to its default state.
 *
 * This function initializes the specified GPIO port pin to its default state.
 * Optionally, a callback function can be provided for pin events.
 *
 * @param pin GPIO port pin to initialize.
 * @return Status code (see GPIO_DRIVER_* macros).
 *
 */

int32_t PORT_Setup(PORT_PIN pin);

/**
 * @brief Set a specific pin direction.
 *
 * @param pin GPIO port pin
 * @param dir Direction (input/output)
 * @return Status code
 */
int32_t PORT_SetDirection(PORT_PIN pin, PORT_DIRECTION dir);

/**
 * @brief Set the output mode for a specific pin.
 *
 * @param pin GPIO port pin
 * @param mode Output mode (push-pull/open-drain)
 * @return Status code
 */
int32_t PORT_SetOutputMode(PORT_PIN pin, GPIO_OUTPUT_MODE mode);

/**
 * @brief Set the pull resistor configuration for a specific pin.
 *
 * @param pin GPIO port pin
 * @param resistor Pull resistor configuration
 * @return Status code
 */
int32_t PORT_SetPullResistor(PORT_PIN pin, GPIO_PULL_RESISTOR resistor);

/**
 * @brief Set the output value for a specific pin.
 *
 * @param pin GPIO port pin
 * @param val Output value (0 or 1)
 */
void PORT_SetOutput(PORT_PIN pin, uint32_t val);

/**
 * @brief Get the input state of a specific pin.
 *
 * @param pin GPIO port pin
 * @return Input state (1 if high, 0 if low)
 */
uint32_t PORT_GetInput(PORT_PIN pin);

/**
 * @brief Toggle the output state of a specific pin.
 *
 * @param pin GPIO port pin
 */
void PORT_Toggle(PORT_PIN pin);

/**
 * @brief Configure Event Actions for a specific pin.
 *
 * @param event_channel The input event channel to be configured.
 * @param event_action The action to be triggered by the event.
 * @param pin The GPIO port pin to associate with the event configuration.
 */
void PORT_ConfigureInputEvent(PORT_EVENT_INPUT_CHANNEL event_channel, PORT_EVENT_ACTION event_action, PORT_PIN pin);

/**
 * @brief Enable Event Actions for a specific channel and for the pin of 
 * particular port.
 *
 * @param event_channel The input event channel to be enabled.
 * @param pin The GPIO port pin associated with the event configuration.
 */
void PORT_EnableInputEvent(PORT_EVENT_INPUT_CHANNEL event_channel, PORT_PIN pin);

/**
 * @brief Disable Event Actions for a specific channel and for the pin of 
 * particular port.
 *
 * @param event_channel The input event channel to be disabled.
 * @param pin The GPIO port pin associated with the event configuration.
 */
void PORT_DisableInputEvent(PORT_EVENT_INPUT_CHANNEL event_channel, PORT_PIN pin);

/**
 * @brief Set the peripheral multiplexing function for a specific pin.
 * It also asserts Mux Enable (MUXEN) for the particular pin.
 * 
 * @param pin The GPIO port pin to be configured.
 * @param peripheral_function The peripheral function to be assigned to the pin. 
 */
void PORT_SetPeripheralMuxing(PORT_PIN pin, PORT_PERIPHERAL_FUNCTION peripheral_function);

#ifdef __cplusplus
}
#endif

#endif // PLIB_PORT_H_
