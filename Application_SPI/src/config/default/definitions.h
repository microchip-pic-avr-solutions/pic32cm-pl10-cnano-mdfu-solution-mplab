/*******************************************************************************
  System Definitions

  File Name:
    definitions.h

  Summary:
    project system definitions.

  Description:
    This file contains the system-wide prototypes and definitions for a project.

 *******************************************************************************/

//DOM-IGNORE-BEGIN
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
//DOM-IGNORE-END

#ifndef DEFINITIONS_H
#define DEFINITIONS_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "peripheral/nvmctrl/plib_nvmctrl.h"
#include "peripheral/sercom/usart/plib_sercom1_usart.h"
#include "peripheral/evsys/plib_evsys.h"
#include "peripheral/port/plib_port.h"
#include "peripheral/clock/plib_gclk.h"
#include "peripheral/clock/plib_mclk.h"
#include "peripheral/clock/plib_osc32kctrl.h"
#include "peripheral/clock/plib_oscctrl.h"
#include "peripheral/nvic/plib_nvic.h"
#include "peripheral/systick/plib_systick.h"
#include "peripheral/tc/plib_tc0_capture16bit.h"
#include "peripheral/tc/plib_tc0_interrupt.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END

/* Device Information */
#define DEVICE_NAME          "PIC32CM6408PL10048"
#define DEVICE_ARCH          "CORTEX-M0PLUS"
#define DEVICE_FAMILY        "PIC32CMPL"
#define DEVICE_SERIES        "PIC32CMPL10"

/* CPU clock frequency */
#define CPU_CLOCK_FREQUENCY 24000000U
    
/*** Macros for LED0 pin ***/
#define LED0_Set()               (PORT_REGS->GROUP[1].PORT_OUTSET = ((uint32_t)1U << 2U))
#define LED0_Clear()             (PORT_REGS->GROUP[1].PORT_OUTCLR = ((uint32_t)1U << 2U))
#define LED0_Toggle()            (PORT_REGS->GROUP[1].PORT_OUTTGL = ((uint32_t)1U << 2U))
#define LED0_OutputEnable()      (PORT_REGS->GROUP[1].PORT_DIRSET = ((uint32_t)1U << 2U))
#define LED0_InputEnable()       (PORT_REGS->GROUP[1].PORT_DIRCLR = ((uint32_t)1U << 2U))
#define LED0_Get()               (((PORT_REGS->GROUP[1].PORT_IN >> 2U)) & 0x01U)
#define LED0_PIN                  PORT_PIN_PB02

/*** Macros for SW0 pin ***/
#define SW0_Set()               (PORT_REGS->GROUP[1].PORT_OUTSET = ((uint32_t)1U << 3U))
#define SW0_Clear()             (PORT_REGS->GROUP[1].PORT_OUTCLR = ((uint32_t)1U << 3U))
#define SW0_Toggle()            (PORT_REGS->GROUP[1].PORT_OUTTGL = ((uint32_t)1U << 3U))
#define SW0_OutputEnable()      (PORT_REGS->GROUP[1].PORT_DIRSET = ((uint32_t)1U << 3U))
#define SW0_InputEnable()       (PORT_REGS->GROUP[1].PORT_DIRCLR = ((uint32_t)1U << 3U))
#define SW0_Get()               (((PORT_REGS->GROUP[1].PORT_IN >> 3U)) & 0x01U)
#define SW0_PIN                  PORT_PIN_PB03
// *****************************************************************************
// *****************************************************************************
// Section: System Functions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* System Initialization Function

  Function:
    void SYS_Initialize( void *data )

  Summary:
    Function that initializes all modules in the system.

  Description:
    This function initializes all modules in the system, including any drivers,
    services, middleware, and applications.

  Precondition:
    None.

  Parameters:
    data            - Pointer to the data structure containing any data
                      necessary to initialize the module. This pointer may
                      be null if no data is required and default initialization
                      is to be used.

  Returns:
    None.

  Example:
    <code>
    SYS_Initialize ( NULL );

    while ( true )
    {
        SYS_Tasks ( );
    }
    </code>

  Remarks:
    This function will only be called once, after system reset.
*/

void SYS_Initialize( void *data );

/* Nullify SYS_Tasks() if only PLIBs are used. */
#define     SYS_Tasks()

// *****************************************************************************
// *****************************************************************************
// Section: extern declarations
// *****************************************************************************
// *****************************************************************************




//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif /* DEFINITIONS_H */
/*******************************************************************************
 End of File
*/

