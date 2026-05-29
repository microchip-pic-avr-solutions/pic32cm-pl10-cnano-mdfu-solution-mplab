/*******************************************************************************
  System Initialization File

  File Name:
    initialization.c

  Summary:
    This file contains source code necessary to initialize the system.

  Description:
    This file contains source code necessary to initialize the system.  It
    implements the "SYS_Initialize" function, defines the configuration bits,
    and allocates any necessary global system resources,
 *******************************************************************************/

// DOM-IGNORE-BEGIN
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
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include "definitions.h"
#include "device.h"

// ****************************************************************************
// ****************************************************************************
// Section: Configuration Bits
// ****************************************************************************
// ****************************************************************************
#pragma config SEQNUM_SEQNUM = 0x0U
#pragma config BOOTPROT_BOOTPROT = 0x7
#pragma config WDTCFG_ENABLE = CLEAR
#pragma config WDTCFG_WEN = CLEAR
#pragma config WDTCFG_ALWAYSON = CLEAR
#pragma config WDTCFG_PER = 0x0
#pragma config WDTCFG_WINDOW = 0x0
#pragma config WDTCFG_EWOFFSET = 0x0
#pragma config BODCFG_ENABLE = CLEAR
#pragma config BODCFG_STDBYCFG = CLEAR
#pragma config BODCFG_RUNSTDBY = CLEAR
#pragma config BODCFG_ACTCFG = 0x0
#pragma config BODCFG_SAMPFREQ = 0x0
#pragma config BODCFG_LEVEL = 0x0
#pragma config BODCFG_VLMLVL = 0x0
#pragma config BODCFG_VLMCFG = 0x0
#pragma config BODCFG_WRTLOCK = CLEAR
#pragma config USERCFG_MVIOMODE = 0x0
#pragma config USERCFG_CRCSEL = 0x1
#pragma config USERCFG_CRCBOOT = CLEAR
#pragma config USERCFG_SUT = 0x0
#pragma config BOOT_GPIOSEL_GPIOPINSEL = 0x00
#pragma config BOOT_GPIOSEL_ENABLE = CLEAR
#pragma config BOOT_GPIOSEL_GPIOPORTSEL = 0x0
#pragma config BOOT_GPIOSEL_POL = 0x0
#pragma config BOOT_GPIOSEL_ODRAIN = 0x0
#pragma config BOOT_GPIOSEL_SLEWLIM = 0x0




// *****************************************************************************
// *****************************************************************************
// Section: Driver Initialization Data
// *****************************************************************************
// *****************************************************************************
/* Following MISRA-C rules are deviated in the below code block */
/* MISRA C-2023 Rule 7.2 - Deviation record ID - H3_MISRAC_2023_R_7_2_DR_1 */
/* MISRA C-2023 Rule 11.1 - Deviation record ID - H3_MISRAC_2023_R_11_1_DR_1 */
/* MISRA C-2023 Rule 11.3 - Deviation record ID - H3_MISRAC_2023_R_11_3_DR_1 */
/* MISRA C-2023 Rule 11.8 - Deviation record ID - H3_MISRAC_2023_R_11_8_DR_1 */



// *****************************************************************************
// *****************************************************************************
// Section: System Data
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
// *****************************************************************************
// Section: Library/Stack Initialization Data
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: System Initialization
// *****************************************************************************
// *****************************************************************************



// *****************************************************************************
// *****************************************************************************
// Section: Local initialization functions
// *****************************************************************************
// *****************************************************************************

/* MISRAC 2023 deviation block end */

/*******************************************************************************
  Function:
    void SYS_Initialize ( void *data )

  Summary:
    Initializes the board, services, drivers, application and other modules.

  Remarks:
 */

void SYS_Initialize ( void* data )
{
    //PORT Initialize
    PORT_SetPeripheralMuxing(PORT_PIN_PA04, PORT_PERIPHERAL_FUNC_C);
    PORT_SetPeripheralMuxing(PORT_PIN_PA05, PORT_PERIPHERAL_FUNC_C);
    PORT_SetPeripheralMuxing(PORT_PIN_PA06, PORT_PERIPHERAL_FUNC_C);
    PORT_SetPeripheralMuxing(PORT_PIN_PA07, PORT_PERIPHERAL_FUNC_C);

    PORT_Setup(PORT_PIN_PB02);
    PORT_SetDirection(PORT_PIN_PB02, GPIO_OUTPUT);

    // Configure SW0 button (PB03) as input with pull-up
    PORT_Setup(PORT_PIN_PB03);
    PORT_SetDirection(PORT_PIN_PB03, GPIO_INPUT);
    PORT_SetPullResistor(PORT_PIN_PB03, GPIO_PULL_UP);

    //Clock Initialize
    //OSC32KCTRL Initialize
    OSC32KCTRL_OSC32K_EnableOnDemand();
    OSC32KCTRL_RTC_SelectClockSource(OSC32KCTRL_RTCSEL_OSC1K);
    
    //OSCCTRL Initialize
    OSCCTRL_OSCHF_SetFrequency(OSCCTRL_OSCHF_FREQ_24M);
    while (!OSCCTRL_OSCHF_IsReady());
    
    //GCLK Initialize
    //GCLK0: source = OSCHF (index 0), DIV = 1, enable
    GCLK_SetGeneratorSource(GCLK_GENERATOR_0, GCLK_SRC_OSCHF);
    GCLK_SetDivisionParameters(GCLK_GENERATOR_0, 1U, GCLK_DIVISION_INTEGER, false);
    GCLK_GeneratorEnable(GCLK_GENERATOR_0);

    //GCLK1: source = OSCHF, DIV = 48 ? 500 kHz, enable
    GCLK_SetGeneratorSource(GCLK_GENERATOR_1, GCLK_SRC_OSCHF);
    GCLK_SetDivisionParameters(GCLK_GENERATOR_1, 48U, GCLK_DIVISION_INTEGER, false);
    GCLK_GeneratorEnable(GCLK_GENERATOR_1);
    
    //SERCOM0_CORE peripheral channel (PCHCTRL[6]) -> GCLK1, then enable
    GCLK_SetPeripheralChannelGenSrc(GCLK_PCHCCTRL_6, GCLK_GENERATOR_1);
    GCLK_EnablePeripheralChannel(GCLK_PCHCCTRL_6);
    
    //MCLK Initialize
    MCLK_REGS->MCLK_APBBMASK = 0x2fU;
    MCLK_REGS->MCLK_APBCMASK = 0x802U;


    SERCOM0_SPI_Initialize();
	SYSTICK_TimerInitialize();
    DMAC_Initialize();
    NVIC_Initialize();
}

/*******************************************************************************
 End of File
*/
