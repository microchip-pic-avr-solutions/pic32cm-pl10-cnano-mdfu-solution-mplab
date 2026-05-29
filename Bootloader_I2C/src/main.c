// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes
#include "config/default/bootloader/library/core/ftp/bl_ftp.h"
#include "config/default/bootloader/library/core/bl_core.h"
#include "config/default/bootloader/library/core/bl_app_verify.h"
#define BL_INDICATOR_Set()               (PORT_REGS->GROUP[1].PORT_OUTSET = ((uint32_t)1U << 2U))
#define BL_INDICATOR_Clear()             (PORT_REGS->GROUP[1].PORT_OUTCLR = ((uint32_t)1U << 2U))

// Button definitions (SW0 on PB03)
#define SW0_PIN_GROUP                    (1U)
#define SW0_PIN_NUM                      (3U)
#define SW0_Get()                        ((PORT_REGS->GROUP[SW0_PIN_GROUP].PORT_IN & (1U << SW0_PIN_NUM)) == 0U)

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

int main(void)
{
    /* Initialize all modules */
    SYS_Initialize(NULL);

    // Check for software entry request or button press at startup
    bool forcedEntry = BL_CheckForcedEntry() || SW0_Get();

    // If no forced entry and app is valid, start the application
    if (!forcedEntry && BL_ImageVerify() == BL_PASS)
    {
        BL_INDICATOR_Set();
        BL_ApplicationStart();
    }

    // Stay in bootloader mode
    FTP_Initialize();
    BL_INDICATOR_Clear();
    while (true)
    {
        FTP_Task();
    }

    return (EXIT_FAILURE);
}


/*******************************************************************************
 End of File
 */