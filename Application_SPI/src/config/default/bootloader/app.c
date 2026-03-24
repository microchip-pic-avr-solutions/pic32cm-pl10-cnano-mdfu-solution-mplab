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

#define BTL_RAM_TRIGGER_START (0x20000000)

static uint32_t __attribute((address(BTL_RAM_TRIGGER_START))) ramArray[4U];

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

static uint16_t intCounter = 0U;

static void BlinkLED(TC_INTERRUPT callback)
{
    // Manually wait for 850 interrupt events to blink
    if ((intCounter % 850U) == 0U)
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
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_INIT;



    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}

/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks(void)
{

    /* Check the application's current state. */
    switch (appData.state)
    {
        /* Application's initial state. */
    case APP_STATE_INIT:
    {
        SYSTICK_TimerStart();
        SYSTICK_DelayMs(3000U);

        printf("\r\n############ Example Bootloader Application ############\r\n");

        TC0_CAPTURE_16BIT_SetCallbackHandler(&BlinkLED);
        TC0_CAPTURE_16BIT_Enable();

        appData.state = APP_STATE_SERVICE_TASKS;

        printf("\r\nApplication is running and the LED is blinking.\r\n");
        break;
    }

    case APP_STATE_SERVICE_TASKS:
    {
        if (SW0_Get() == 0U)
        {
            appData.state = TRIGGER_BOOTLOADER;
            printf("\r\n############ Switch was pressed, entering bootloader mode ############\r\n");
        }

        break;
    }

    case TRIGGER_BOOTLOADER:
    {

        /**
         * Trigger the bootloader using pattern in RAM
         */

        printf("\r\n############ Disconnect from the device port and load a new application using pymdfu ###############\r\n");
        while (!SERCOM1_USART_TxIsDone())
        {
        }

        Trigger_Bootloader(0x5048434DU);
        break;
    }


        /* The default state should never be executed. */
    default:
    {
        /* TODO: Handle error in application's state machine. */
        break;
    }
    }
}


/*******************************************************************************
 End of File
 */
