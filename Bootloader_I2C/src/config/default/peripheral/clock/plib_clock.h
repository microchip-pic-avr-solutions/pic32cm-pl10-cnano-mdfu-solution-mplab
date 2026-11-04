/*******************************************************************************
  CLOCK PLIB

  Company:
    Microchip Technology Inc.

  File Name:
    plib_clock.h

  Summary:
    CLOCK PLIB Header File.

  Description:
    The Clock PLIB initializes all the oscillators based on the requirements.

*******************************************************************************/

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

#ifndef PLIB_CLOCK_H
#define PLIB_CLOCK_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/* This section lists the other files that are included in this file.
*/
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// DOM-IGNORE-BEGIN
#ifdef __cplusplus // Provide C++ Compatibility
extern "C" {
#endif

// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Interface Routines
// *****************************************************************************
// *****************************************************************************
/* The following functions make up the methods (set of possible operations) of
this interface.
*/

// *****************************************************************************
/* Function:
    void CLOCK_Initialize (void);

  Summary:
    Initializes all the modules related to the system clock.

  Description:
    This function initializes the clock as defined by the MCC and Clock Manager
    selections.

    For each of the clock sources (OSCHF Oscillator, External 32KHz oscillator
    and the Internal 32KHz oscillator) enabled in MCC, the function will configure
    the clock settings and will then wait till the clock is ready.

    The function will then configure the Generic clock generators based on MCC
    configurations. If a Generic Clock is enabled in MCC, this will be enabled
    in the CLOCK_Initialize() function. The function will apply the CPU clock
    divider and will wait for the Main Clock module to get ready. If the Main
    Clock to the Peripheral APB and AHB interfaces was enabled in MCC, these
    will be enabled in the CLOCK_Initialize() function. If the Peripheral Clock
    Channels were enabled in MCC, these will be enabled in the
    CLOCK_Initialize() function.

    The peripheral AHB and APB main clock and peripheral channel clocks will be
    enabled when the peripheral specific initialize functions are called. This
    will override the setting in MCC. The Generic Clock Generator source for
    desired peripheral channel must be configured in MCC.

  Precondition:
    MCC GUI should be configured with the right values. Incorrect configuration
    of the Clock will result in incorrect peripheral behavior or a non
    functional device.

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
        CLOCK_Initialize();
    </code>

  Remarks:
    This function should be called before calling other Clock library functions.
*/

void CLOCK_Initialize (void);



#ifdef __cplusplus // Provide C++ Compatibility
}
#endif

#endif /* PLIB_CLOCK_H */

