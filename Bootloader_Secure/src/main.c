/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

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
#include "config/default/bootloader/library/core/bl_sha256.h"
#include "cryptoauthlib.h"

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

ATCA_STATUS status;
extern ATCAIfaceCfg atecc608_0_init_data;
ATCAIfaceCfg* device_cfg = &atecc608_0_init_data;

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize(NULL);
    
    /* Status check for secure element initialization*/
    status = atcab_init(device_cfg);
    /**
     * Check to see if a bootload is requested.
     * If not, then validate the image before running it.
     */
    if (ATCA_SUCCESS == status)
    {
        if(BL_CheckForcedEntry() == false && BL_ImageVerify() == BL_PASS)
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
    }

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

