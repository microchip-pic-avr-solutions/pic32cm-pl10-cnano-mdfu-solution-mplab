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
// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

int main(void)
{
    /* Initialize all modules */
    SYS_Initialize(NULL);

    /**
     * Check to see if a bootload is requested.
     * If not, then validate the image before running it.
     */
    if (BL_CheckForcedEntry() == false && BL_ImageVerify() == BL_PASS)
    {
        BL_INDICATOR_Set();
        BL_ApplicationStart();
    }

    // When a bootload is needed; Initialize the FTP layer and run the FTP task to download the new data
    FTP_Initialize();

    BL_INDICATOR_Clear();
    while (true)
    {
        FTP_Task();
    }

    /* Execution should not come here during normal operation */
    return ( EXIT_FAILURE);
}


/*******************************************************************************
 End of File
 */