/*******************************************************************************
 * Copyright ? 2025 Microchip Technology Inc. and its subsidiaries.
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
 ******************************************************************************/

#include "plib_port.h"

#define GPIO_PINS_PER_GROUP    (32U)
#define GPIO_MAX_PINS          (GPIO_PINS_PER_GROUP * PORT_GROUP_NUMBER)

#define PIN_IS_AVAILABLE(pin)  ((uint32_t)(pin) < GPIO_MAX_PINS)
#define PIN_MASK(pin)          (1UL << ((uint32_t)(pin) % GPIO_PINS_PER_GROUP))
#define PIN_GROUP(pin)         ((uint32_t)(pin) / GPIO_PINS_PER_GROUP)
#define PIN_INDEX(pin)         ((uint32_t)(pin) % GPIO_PINS_PER_GROUP)


int32_t PORT_Setup(PORT_PIN pin)
{
    int32_t result = PORT_PLIB_OK;   

    if (PIN_IS_AVAILABLE(pin))
    {
        PORT_REGS->GROUP[PIN_GROUP(pin)].PORT_PINCFG[PIN_INDEX(pin)] = 0x6U;
        PORT_REGS->GROUP[PIN_GROUP(pin)].PORT_OUT |= PIN_MASK(pin);
    }
    else
    {
        result = PORT_PLIB_ERROR;
    }

    return result;
}


int32_t PORT_SetDirection(PORT_PIN pin, PORT_DIRECTION direction)
{
    int32_t result = PORT_PLIB_OK;

    if (PIN_IS_AVAILABLE(pin))
    {
        switch (direction)
        {
            case GPIO_INPUT:
                PORT_REGS->GROUP[PIN_GROUP(pin)].PORT_DIRCLR = PIN_MASK(pin);
                PORT_REGS->GROUP[PIN_GROUP(pin)].PORT_PINCFG[PIN_INDEX(pin)] |= 0x6U;
                PORT_REGS->GROUP[PIN_GROUP(pin)].PORT_OUTSET = PIN_MASK(pin);
                break;
            case GPIO_OUTPUT:
                PORT_REGS->GROUP[PIN_GROUP(pin)].PORT_DIRSET = PIN_MASK(pin);
                PORT_REGS->GROUP[PIN_GROUP(pin)].PORT_OUTCLR = PIN_MASK(pin);
                break;
            default:
                result = PORT_PLIB_ERROR_PARAMETER;
                break;
        }
    }
    else
    {
        result = PORT_PLIB_ERROR;
    }

    return result;
}


int32_t PORT_SetOutputMode(PORT_PIN pin, GPIO_OUTPUT_MODE mode)
{
    int32_t result = PORT_PLIB_OK;

    if (PIN_IS_AVAILABLE(pin))
    {
        switch (mode)
        {
            case GPIO_PUSH_PULL:
                PORT_REGS->GROUP[PIN_GROUP(pin)].PORT_DIRSET = PIN_MASK(pin); // Output
                PORT_REGS->GROUP[PIN_GROUP(pin)].PORT_PINCFG[PIN_INDEX(pin)] &= ~(1U << 2);
                break;
            case GPIO_OPEN_DRAIN:
                PORT_REGS->GROUP[PIN_GROUP(pin)].PORT_DIRCLR = PIN_MASK(pin);               // Input (high-Z)
                PORT_REGS->GROUP[PIN_GROUP(pin)].PORT_PINCFG[PIN_INDEX(pin)] &= ~(1U << 2); // PULLEN = 0
                break;
            default:
                result = PORT_PLIB_ERROR_PARAMETER;
                break;
        }
    }
    else
    {
        result = PORT_PLIB_ERROR;
    }

    return result;
}


int32_t PORT_SetPullResistor(PORT_PIN pin, GPIO_PULL_RESISTOR resistor)
{
    int32_t result = PORT_PLIB_OK;

    if (PIN_IS_AVAILABLE(pin))
    {
        switch (resistor)
        {
            case GPIO_PULL_NONE:
                PORT_REGS->GROUP[PIN_GROUP(pin)].PORT_PINCFG[PIN_INDEX(pin)] &= ~(1U << 2);
                break;
            case GPIO_PULL_UP:
                PORT_REGS->GROUP[PIN_GROUP(pin)].PORT_PINCFG[PIN_INDEX(pin)] |= (1U << 2); // PULLEN
                PORT_REGS->GROUP[PIN_GROUP(pin)].PORT_OUTSET = PIN_MASK(pin);
                break;
            case GPIO_PULL_DOWN:
                PORT_REGS->GROUP[PIN_GROUP(pin)].PORT_PINCFG[PIN_INDEX(pin)] |= (1U << 2); // PULLEN
                PORT_REGS->GROUP[PIN_GROUP(pin)].PORT_OUTCLR = PIN_MASK(pin);
                break;
            default:
                result = PORT_PLIB_ERROR_PARAMETER;
                break;
        }
    }
    else
    {
        result = PORT_PLIB_ERROR;
    }

    return result;
}


void PORT_SetOutput(PORT_PIN pin, uint32_t value)
{
    if (PIN_IS_AVAILABLE(pin))
    {
        if (value != 0U)
        {
            PORT_REGS->GROUP[PIN_GROUP(pin)].PORT_OUTSET = PIN_MASK(pin);
        }
        else
        {
            PORT_REGS->GROUP[PIN_GROUP(pin)].PORT_OUTCLR = PIN_MASK(pin);
        }
    }
}

uint32_t PORT_GetInput(PORT_PIN pin)
{
    uint32_t value = 0U;
    if (PIN_IS_AVAILABLE(pin))
    {
        value = (PORT_REGS->GROUP[PIN_GROUP(pin)].PORT_IN >> PIN_INDEX(pin)) & 0x1;
    }
    return value;
}


void PORT_Toggle(PORT_PIN pin)
{
    if (PIN_IS_AVAILABLE(pin))
    {
        PORT_REGS->GROUP[PIN_GROUP(pin)].PORT_OUTTGL = PIN_MASK(pin);
    }
}

void PORT_ConfigureInputEvent(PORT_EVENT_INPUT_CHANNEL event_channel, PORT_EVENT_ACTION event_action, PORT_PIN pin)
{
    if (PIN_IS_AVAILABLE(pin))
    {
        uint32_t port_event_mask = ((uint32_t)0xFF << (event_channel-7U));
        uint32_t port_event_ctrl_reg =  ((uint32_t)event_action << (event_channel-2U)) |
                                        (PIN_INDEX(pin) << (event_channel-7U));

        PORT_REGS->GROUP[PIN_GROUP(pin)].PORT_EVCTRL = (PORT_REGS->GROUP[PIN_GROUP(pin)].PORT_EVCTRL & ~port_event_mask) 
                                                        | port_event_ctrl_reg;
    }
}

void PORT_EnableInputEvent(PORT_EVENT_INPUT_CHANNEL event_channel, PORT_PIN pin)
{
    uint32_t port_event_enable_mask = ((uint32_t)1U << event_channel);
    PORT_REGS->GROUP[PIN_GROUP(pin)].PORT_EVCTRL |= port_event_enable_mask; 
}

void PORT_DisableInputEvent(PORT_EVENT_INPUT_CHANNEL event_channel, PORT_PIN pin)
{
    uint32_t port_event_enable_mask = ((uint32_t)1U << event_channel);
    PORT_REGS->GROUP[PIN_GROUP(pin)].PORT_EVCTRL &= ~port_event_enable_mask;
}

void PORT_SetPeripheralMuxing(PORT_PIN pin, PORT_PERIPHERAL_FUNCTION peripheral_function)
{
    
    if(PIN_IS_AVAILABLE(pin))
    {
        uint32_t mux_reg_n = PIN_INDEX(pin) >> 1;

        PORT_REGS->GROUP[PIN_GROUP(pin)].PORT_PINCFG[PIN_INDEX(pin)] |= PORT_PINCFG_PMUXEN_Msk;

        if(((PIN_INDEX(pin)) & 0x1) == 0U)
        {
            PORT_REGS->GROUP[PIN_GROUP(pin)].PORT_PMUX[mux_reg_n] = (PORT_REGS->GROUP[PIN_GROUP(pin)].PORT_PMUX[mux_reg_n] & ~PORT_PMUX_PMUXE_Msk) 
                                                                    | PORT_PMUX_PMUXE(peripheral_function);
        }
        else
        {
            PORT_REGS->GROUP[PIN_GROUP(pin)].PORT_PMUX[mux_reg_n] = (PORT_REGS->GROUP[PIN_GROUP(pin)].PORT_PMUX[mux_reg_n] & ~PORT_PMUX_PMUXO_Msk) 
                                                                    | PORT_PMUX_PMUXO(peripheral_function);
        }
    }
}