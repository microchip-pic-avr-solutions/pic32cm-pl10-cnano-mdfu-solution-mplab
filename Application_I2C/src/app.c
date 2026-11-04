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
#include "config/default/definitions.h"
#include "config/default/peripheral/port/plib_port.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************
#define SWITCH_PRESSED   0
#define SWITCH_RELEASED  1

#define APP_LED_COUNTER          500 /* systick int : 50ms */

/* Application Footer Data

  Description:
    Holds application footer data

  Remarks:
    This variable reserves the space needed for the application hash
*/

const APP_HASH __attribute__((address(0x0C00FFFC), keep)) applicationHash = 0xFFFFFFFFU;

// *****************************************************************************
/* Application Data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.

    Application strings and buffers are be defined outside this structure.
*/

APP_DATA appData;

/* Application Data

  Description:
    This section defines the bootloader trigger pattern and the RAM address it
    it should be stored at

  Remarks:
    The Bootloader Trigger pattern is 16 bytes long and stored at the end of 
    non-secure RAM
*/
#define BTL_TRIGGER_ARRAY_SIZE    (4U)
#define BTL_TRIGGER_RAM_START (0x20000000U + (0x0002000U - 16U))
#define BTL_TRIGGER_PATTERN (0x5048434DU)


uint32_t __attribute__((persistent, address(BTL_TRIGGER_RAM_START), keep)) ramArray[BTL_TRIGGER_ARRAY_SIZE];

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

void APP_Systick_Callback(uintptr_t context)
{
    if (appData.counterLedBlink-- == 0)
    {
        LED_Toggle();
        appData.counterLedBlink = APP_LED_COUNTER;
    }
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

void APP_Initialize ( void )
{
   
    appData.state = APP_STATE_INIT;
    appData.counterLedBlink = APP_LED_COUNTER;

    SYSTICK_TimerStart();
    
    (void)printf("\r\n\r\n####### Application loaded from Bootloader #######\r\n");
}

/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */


void APP_Tasks ( void )
{ 
    
    /* Check the application's current state. */
    switch ( appData.state )
    {
        /* Application's initial state. */
        case APP_STATE_INIT:
        {
            (void)printf("\r\n####### Press and Hold the Switch to trigger Bootloader #######\r\n");
            
            SYSTICK_TimerCallbackSet(APP_Systick_Callback, (uintptr_t) NULL);
            SYSTICK_TimerStart();
            
            appData.state = APP_STATE_SWITCH_PRESS_WAIT;

            break;
        }

        case APP_STATE_SWITCH_PRESS_WAIT:
        {
            (void)printf("\r\n####### Still Waiting for the button #######\r\n");
            
            if (BL_ENTRY_Get() == SWITCH_PRESSED)
            {
                appData.state = APP_STATE_TRIGGER_BOOTLOADER;
            }

            break;
        }

        case APP_STATE_TRIGGER_BOOTLOADER:
        {
           (void)printf("\r\n####### Bootloader Triggered #######\r\n");
           
            ramArray[0] = BTL_TRIGGER_PATTERN;
            ramArray[1] = BTL_TRIGGER_PATTERN;
            ramArray[2] = BTL_TRIGGER_PATTERN;
            ramArray[3] = BTL_TRIGGER_PATTERN;
            
            NVIC_SystemReset();
            
        }

        default:
        {
            /* Define application error handling */
            break;
        }
    }
}


/*******************************************************************************
 End of File
 */
