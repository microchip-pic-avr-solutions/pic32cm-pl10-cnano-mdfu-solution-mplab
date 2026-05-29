/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It
    implements the logic of the application's state machine and it may call
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include "app.h"
#include "peripheral/systick/plib_systick.h"
#include "peripheral/tc/plib_tc0_capture16bit.h"
#include "peripheral/sercom/usart/plib_sercom1_usart.h"
#include <stdio.h>
#include "peripheral/port/plib_port.h"
#include "../definitions.h"
// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.

    Application strings and buffers are be defined outside this structure.
 */

static APP_DATA appData;

#define BTL_RAM_TRIGGER_START     (0x20000000)
#define BTL_TRIGGER_ARRAY_SIZE    (4U)
#define BTL_TRIGGER_PATTERN       (0x5048434DU)
#define LED_BLINK_INTERRUPT_COUNT (500U)
#define APP_STARTUP_DELAY_MS      (3000U)

static uint32_t __attribute((address(BTL_RAM_TRIGGER_START))) ramArray[BTL_TRIGGER_ARRAY_SIZE];

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

static uint16_t intCounter = 0U;

static void BlinkLED(TC_INTERRUPT callback)
{
    // Wait for LED_BLINK_INTERRUPT_COUNT interrupt events to toggle LED (500ms period)
    if ((intCounter % LED_BLINK_INTERRUPT_COUNT) == 0U)
    {
        LED0_Toggle();
        intCounter = 0U;
    }
    intCounter++;
}

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************

static void Trigger_Bootloader(uint32_t triggerPattern)
{
    ramArray[0] = triggerPattern;
    ramArray[1] = triggerPattern;
    ramArray[2] = triggerPattern;
    ramArray[3] = triggerPattern;

    NVIC_SystemReset();
}


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Initialize(void)
{
    appData.state = APP_STATE_INIT;

}

/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks(void)
{
    switch (appData.state)
    {
    case APP_STATE_INIT:
    {
        TC0_CAPTURE_16BIT_SetCallbackHandler(&BlinkLED);
        TC0_CAPTURE_16BIT_Enable();
        appData.state = APP_STATE_SERVICE_TASKS;
        break;
    }

    case APP_STATE_SERVICE_TASKS:
    {
        if (SW0_Get() == 0U)
        {
            appData.state = TRIGGER_BOOTLOADER;
        }

        break;
    }

    case TRIGGER_BOOTLOADER:
    {
        Trigger_Bootloader(BTL_TRIGGER_PATTERN);
        break;
    }
    default:
    {
        /* Handle unexpected state */
        appData.state = APP_STATE_INIT;
        break;
    }
    }
}


/*******************************************************************************
 End of File
 */
