/********************************************************************************
* Copyright © 2025 Microchip Technology Inc. and its subsidiaries.
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
/******************************************************************************
* @file plib_mclk.h
* @brief Main Clock (MCLK) Controller Peripheral Library Interface.
*
* @details This file provides the Interface of the Main Clock (MCLK) peripheral 
* library, including functions to initialize the MCLK, configure CPU clock 
* division, and enable/disable AHB and APB clocks for various modules. It also 
* provides interrupt handling and callback registration for the Clock Ready event.
*******************************************************************************/

#ifndef PLIB_MCLK_H
#define PLIB_MCLK_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <pic32c.h>

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
* @brief Example: Initialize Main Clock (MCLK) and Wait for Readiness
*
* This example demonstrates how to configure the Main Clock (MCLK) CPU divider,
* wait for the clock to become ready, and then clear the clock ready flag using
* the PLIB MCLK APIs. It sets the CPU clock divider, waits for the clock ready
* status, and clears the ready flag once the clock is stable.
*
* ```c
* #include "plib_mclk.h"
*
* int main(void)
* {
*     // Set CPU clock divider to DIV1 (no division)
*     MCLK_SetCPUClockDivider(MCLK_CPU_CLK_DIV_1);
*
*     // Wait until the main clock is ready
*     while(!(MCLK_ClockIsReady()))
*     {
*         // Wait for the clock to become ready
*     }
*
*     // Clear the clock ready flag
*     MCLK_ClearClockReadyFlag();
*
*     // Application code can proceed here
*
*     return 0;
* }
* ```
*******************************************************************************/

/**
* @brief Callback type for clock ready event
*/
typedef void (*MCLK_CALLBACK)(void);

/**
 * @brief CPU clock division factors for MCLK
 */
typedef enum
{
    MCLK_CPU_CLK_DIV_1   = 0x01U,
    MCLK_CPU_CLK_DIV_2   = 0x02U,
    MCLK_CPU_CLK_DIV_4   = 0x04U,
    MCLK_CPU_CLK_DIV_8   = 0x08U,
    MCLK_CPU_CLK_DIV_16  = 0x10U,
    MCLK_CPU_CLK_DIV_32  = 0x20U,
    MCLK_CPU_CLK_DIV_64  = 0x40U,
    MCLK_CPU_CLK_DIV_128 = 0x80U
} MCLK_CPU_CLOCK_DIVIDER;

/**
 * @brief AHB module identifiers for clock gating
 */
typedef enum
{
    #if defined(MCLK_AHBMASK_APBA_Msk)
        MCLK_AHB_APBA           = MCLK_AHBMASK_APBA_Msk,      
    #endif
    #if defined(MCLK_AHBMASK_APBB_Msk)
        MCLK_AHB_APBB           = MCLK_AHBMASK_APBB_Msk,   
    #endif
    #if defined(MCLK_AHBMASK_APBC_Msk)
        MCLK_AHB_APBC           = MCLK_AHBMASK_APBC_Msk,     
    #endif
    #if defined(MCLK_AHBMASK_DSU_Msk)
        MCLK_AHB_DSU            = MCLK_AHBMASK_DSU_Msk,      
    #endif
    #if defined(MCLK_AHBMASK_HMATRIXHS_Msk)
        MCLK_AHB_HMATRIXHS      = MCLK_AHBMASK_HMATRIXHS_Msk, 
    #endif
    #if defined(MCLK_AHBMASK_NVMCTRL_Msk)
        MCLK_AHB_NVMCTRL        = MCLK_AHBMASK_NVMCTRL_Msk,  
    #endif
    #if defined(MCLK_AHBMASK_HSRAM_Msk)
        MCLK_AHB_HSRAM          = MCLK_AHBMASK_HSRAM_Msk,    
    #endif
    #if defined(MCLK_AHBMASK_MCRAMC_Msk)
        MCLK_AHB_MCRAMC         = MCLK_AHBMASK_MCRAMC_Msk,    
    #endif
    #if defined(MCLK_AHBMASK_DMAC_Msk)
        MCLK_AHB_DMAC           = MCLK_AHBMASK_DMAC_Msk,      
    #endif
    #if defined(MCLK_AHBMASK_CAN0_Msk)
        MCLK_AHB_CAN0           = MCLK_AHBMASK_CAN0_Msk,      
    #endif
    #if defined(MCLK_AHBMASK_BROMC_Msk)
        MCLK_AHB_BROMC           = MCLK_AHBMASK_BROMC_Msk,    
    #endif
    #if defined(MCLK_AHBMASK_CAN1_Msk)
        MCLK_AHB_CAN1           = MCLK_AHBMASK_CAN1_Msk,      
    #endif
    #if defined(MCLK_AHBMASK_PAC_Msk)
        MCLK_AHB_PAC            = MCLK_AHBMASK_PAC_Msk,       
    #endif
    #if defined(MCLK_AHBMASK_DIVAS_Msk)
        MCLK_AHB_DIVAS          = MCLK_AHBMASK_DIVAS_Msk,    
    #endif
    #if defined(MCLK_AHBMASK_APBD_Msk)
        MCLK_AHB_APBD           = MCLK_AHBMASK_APBD_Msk,    
    #endif
    #if defined(MCLK_AHBMASK_ICM_Msk)
        MCLK_AHB_ICM            = MCLK_AHBMASK_ICM_Msk       
    #endif
} MCLK_AHB_MODULE;

/**
 * @brief APBA module identifiers for clock gating
 */
typedef enum
{
    #if defined(MCLK_APBAMASK_PAC_Msk)
        MCLK_APBA_PAC           = MCLK_APBAMASK_PAC_Msk,         
    #endif
    #if defined(MCLK_APBAMASK_PM_Msk)
        MCLK_APBA_PM            = MCLK_APBAMASK_PM_Msk,         
    #endif
    #if defined(MCLK_APBAMASK_MCLK_Msk)
        MCLK_APBA_MCLK          = MCLK_APBAMASK_MCLK_Msk,        
    #endif
    #if defined(MCLK_APBAMASK_RSTC_Msk)
        MCLK_APBA_RSTC          = MCLK_APBAMASK_RSTC_Msk,        
    #endif
    #if defined(MCLK_APBAMASK_OSCCTRL_Msk)
        MCLK_APBA_OSCCTRL       = MCLK_APBAMASK_OSCCTRL_Msk,     
    #endif
    #if defined(MCLK_APBAMASK_OSC32KCTRL_Msk)
        MCLK_APBA_OSC32KCTRL    = MCLK_APBAMASK_OSC32KCTRL_Msk, 
    #endif
    #if defined(MCLK_APBAMASK_SUPC_Msk)
        MCLK_APBA_SUPC          = MCLK_APBAMASK_SUPC_Msk,        
    #endif
    #if defined(MCLK_APBAMASK_GCLK_Msk)
        MCLK_APBA_GCLK          = MCLK_APBAMASK_GCLK_Msk,        
    #endif
    #if defined(MCLK_APBAMASK_WDT_Msk)
        MCLK_APBA_WDT           = MCLK_APBAMASK_WDT_Msk,         
    #endif
    #if defined(MCLK_APBAMASK_RTC_Msk)
        MCLK_APBA_RTC           = MCLK_APBAMASK_RTC_Msk,         
    #endif
    #if defined(MCLK_APBAMASK_EIC_Msk)
        MCLK_APBA_EIC           = MCLK_APBAMASK_EIC_Msk,         
    #endif
    #if defined(MCLK_APBAMASK_FREQM_Msk)
        MCLK_APBA_FREQM         = MCLK_APBAMASK_FREQM_Msk,       
    #endif
    #if defined(MCLK_APBAMASK_MCRAMC_Msk)
        MCLK_APBA_MCRAMC        = MCLK_APBAMASK_MCRAMC_Msk      
    #endif
} MCLK_APBA_MODULE;

/**
 * @brief APBB module identifiers for clock gating
 */
typedef enum
{
    #if defined(MCLK_APBBMASK_PORT_Msk)
        MCLK_APBB_PORT          = MCLK_APBBMASK_PORT_Msk,         
    #endif
    #if defined(MCLK_APBBMASK_DSU_Msk)
        MCLK_APBB_DSU           = MCLK_APBBMASK_DSU_Msk,          
    #endif
    #if defined(MCLK_APBBMASK_NVMCTRL_Msk)
        MCLK_APBB_NVMCTRL       = MCLK_APBBMASK_NVMCTRL_Msk,      
    #endif
    #if defined(MCLK_APBBMASK_DMAC_Msk)
        MCLK_APBB_DMAC          = MCLK_APBBMASK_DMAC_Msk,        
    #endif
    #if defined(MCLK_APBBMASK_MTB_Msk)
        MCLK_APBB_MTB           = MCLK_APBBMASK_MTB_Msk,          
    #endif
    #if defined(MCLK_APBBMASK_HMATRIXHS_Msk)
        MCLK_APBB_HMATRIXHS     = MCLK_APBBMASK_HMATRIXHS_Msk    
    #endif
} MCLK_APBB_MODULE;

/**
 * @brief APBC module identifiers for clock gating
 */
typedef enum
{
    #if defined(MCLK_APBCMASK_EVSYS_Msk)
        MCLK_APBC_EVSYS         = MCLK_APBCMASK_EVSYS_Msk,         
    #endif
    #if defined(MCLK_APBCMASK_SERCOM0_Msk)
        MCLK_APBC_SERCOM0       = MCLK_APBCMASK_SERCOM0_Msk,       
    #endif
    #if defined(MCLK_APBCMASK_SERCOM1_Msk)
        MCLK_APBC_SERCOM1       = MCLK_APBCMASK_SERCOM1_Msk,       
    #endif
    #if defined(MCLK_APBCMASK_SERCOM2_Msk)
        MCLK_APBC_SERCOM2       = MCLK_APBCMASK_SERCOM2_Msk,      
    #endif
    #if defined(MCLK_APBCMASK_SERCOM3_Msk)
        MCLK_APBC_SERCOM3       = MCLK_APBCMASK_SERCOM3_Msk,       
    #endif
    #if defined(MCLK_APBCMASK_SERCOM4_Msk)
        MCLK_APBC_SERCOM4       = MCLK_APBCMASK_SERCOM4_Msk,       
    #endif
    #if defined(MCLK_APBCMASK_SERCOM5_Msk)
        MCLK_APBC_SERCOM5       = MCLK_APBCMASK_SERCOM5_Msk,       
    #endif
    #if defined(MCLK_APBCMASK_TCC0_Msk)
        MCLK_APBC_TCC0          = MCLK_APBCMASK_TCC0_Msk,          
    #endif
    #if defined(MCLK_APBCMASK_TCC1_Msk)
        MCLK_APBC_TCC1          = MCLK_APBCMASK_TCC1_Msk,         
    #endif
    #if defined(MCLK_APBCMASK_TCC2_Msk)
        MCLK_APBC_TCC2          = MCLK_APBCMASK_TCC2_Msk,          
    #endif
    #if defined(MCLK_APBCMASK_TC0_Msk)
        MCLK_APBC_TC0           = MCLK_APBCMASK_TC0_Msk,           
    #endif
    #if defined(MCLK_APBCMASK_TC1_Msk)
        MCLK_APBC_TC1           = MCLK_APBCMASK_TC1_Msk,           
    #endif
    #if defined(MCLK_APBCMASK_TC2_Msk)
        MCLK_APBC_TC2           = MCLK_APBCMASK_TC2_Msk,           
    #endif
    #if defined(MCLK_APBCMASK_TC3_Msk)
        MCLK_APBC_TC3           = MCLK_APBCMASK_TC3_Msk,           
    #endif
    #if defined(MCLK_APBCMASK_TC4_Msk)
        MCLK_APBC_TC4           = MCLK_APBCMASK_TC4_Msk,           
    #endif
    #if defined(MCLK_APBCMASK_ADC0_Msk)
        MCLK_APBC_ADC0          = MCLK_APBCMASK_ADC0_Msk,          
    #endif
    #if defined(MCLK_APBCMASK_ADC1_Msk)
        MCLK_APBC_ADC1          = MCLK_APBCMASK_ADC1_Msk,          
    #endif
    #if defined(MCLK_APBCMASK_AC_Msk)
        MCLK_APBC_AC            = MCLK_APBCMASK_AC_Msk,            
    #endif
    #if defined(MCLK_APBCMASK_DAC_Msk)
        MCLK_APBC_DAC           = MCLK_APBCMASK_DAC_Msk,           
    #endif
    #if defined(MCLK_APBCMASK_PTC_Msk)
        MCLK_APBC_PTC           = MCLK_APBCMASK_PTC_Msk,           
    #endif
    #if defined(MCLK_APBCMASK_CCL_Msk)
        MCLK_APBC_CCL           = MCLK_APBCMASK_CCL_Msk,           
    #endif
    #if defined(MCLK_APBCMASK_ICM_Msk)
        MCLK_APBC_ICM           = MCLK_APBCMASK_ICM_Msk,           
    #endif
    #if defined(MCLK_APBCMASK_PDEC_Msk)
        MCLK_APBC_PDEC          = MCLK_APBCMASK_PDEC_Msk,          
    #endif
    #if defined(MCLK_APBCMASK_SMBIST_Msk)
        MCLK_APBC_SMBIST        = MCLK_APBCMASK_SMBIST_Msk,        
    #endif
    #if defined(MCLK_APBCMASK_SYSCTRL_Msk)
        MCLK_APBC_SYSCTRL        = MCLK_APBCMASK_SYSCTRL_Msk       
    #endif
} MCLK_APBC_MODULE;

#if defined(MCLK_APBDMASK_Msk)
/**
 * @brief APBD module identifiers for clock gating
 */
typedef enum
{
    #if defined(MCLK_APBDMASK_SERCOM6_Msk)
        MCLK_APBD_SERCOM6      = MCLK_APBDMASK_SERCOM6_Msk,    
    #endif
    #if defined(MCLK_APBDMASK_SERCOM7_Msk)
        MCLK_APBD_SERCOM7      = MCLK_APBDMASK_SERCOM7_Msk,    
    #endif
    #if defined(MCLK_APBDMASK_TC5_Msk)
        MCLK_APBD_TC5          = MCLK_APBDMASK_TC5_Msk,        
    #endif
    #if defined(MCLK_APBDMASK_TC6_Msk)
        MCLK_APBD_TC6          = MCLK_APBDMASK_TC6_Msk,        
    #endif
    #if defined(MCLK_APBDMASK_TC7_Msk)
        MCLK_APBD_TC7          = MCLK_APBDMASK_TC7_Msk         
    #endif
} MCLK_APBD_MODULE;
#endif //MCLK_APBDMASK_Msk

/**
 * @brief Initializes the MCLK peripheral.
 * @param None.
 * @return None.
 */
void MCLK_Initialize(void);

/**
 * @brief Gets the current CPU clock division factor.
 * @param None.
 * @return MCLK_CPU_CLOCK_DIVIDER Current CPU clock division factor.
 */
MCLK_CPU_CLOCK_DIVIDER MCLK_GetCPUClockDivider(void);

/**
 * @brief Sets the CPU clock division factor.
 * @param div Division factor to set for the CPU clock.
 * @return None.
 */
void MCLK_SetCPUClockDivider(MCLK_CPU_CLOCK_DIVIDER div);

/**
 * @brief Enables the AHB clock for a specific module.
 * @param module The AHB module to enable the clock for.
 * @return None.
 */
void MCLK_EnableAHBClock(MCLK_AHB_MODULE module);

/**
 * @brief Disables the AHB clock for a specific module.
 * @param module The AHB module to disable the clock for.
 * @return None.
 */
void MCLK_DisableAHBClock(MCLK_AHB_MODULE module);

/**
 * @brief Enables the APB clock for a module with APBA bus.
 * @param module The APBA module to enable the clock for.
 * @return None.
 */
void MCLK_EnableAPBAClock(MCLK_APBA_MODULE module);

/**
 * @brief Enables the APB clock for a module with APBB bus.
 * @param module The APBB module to enable the clock for.
 * @return None.
 */
void MCLK_EnableAPBBClock(MCLK_APBB_MODULE module);

/**
 * @brief Enables the APB clock for a module with APBC bus.
 * @param module The APBC module to enable the clock for.
 * @return None.
 */
void MCLK_EnableAPBCClock(MCLK_APBC_MODULE module);

#if defined(MCLK_APBDMASK_Msk)
/**
 * @brief Enables the APB clock for a module with APBD bus.
 * @param module The APBD module to enable the clock for.
 * @return None.
 */
void MCLK_EnableAPBDClock(MCLK_APBD_MODULE module);
#endif

/**
 * @brief Disables the APB clock for a module with APBA bus.
 * @param module The APBA module to disable the clock for.
 * @return None.
 */
void MCLK_DisableAPBAClock(MCLK_APBA_MODULE module);

/**
 * @brief Disables the APB clock for a module with APBB bus.
 * @param module The APBB module to disable the clock for.
 * @return None.
 */
void MCLK_DisableAPBBClock(MCLK_APBB_MODULE module);

/**
 * @brief Disables the APB clock for a module with APBC bus.
 * @param module The APBC module to disable the clock for.
 * @return None.
 */
void MCLK_DisableAPBCClock(MCLK_APBC_MODULE module);

#if defined(MCLK_APBDMASK_Msk)
/**
 * @brief Disables the APB clock for a module with APBD bus.
 * @param module The APBD module to disable the clock for.
 * @return None.
 */
void MCLK_DisableAPBDClock(MCLK_APBD_MODULE module);
#endif

/**
 * @brief Checks if the clock is ready (CKRDY flag).
 * @param None.
 * @return true if the clock is ready, false otherwise.
 */
bool MCLK_ClockIsReady(void);

/**
 * @brief Enables the Clock Ready interrupt.
 * @param None.
 * @return None.
 */
void MCLK_EnableClockReadyInterrupt(void);

/**
 * @brief Disables the Clock Ready interrupt.
 * @param None.
 * @return None.
 */
void MCLK_DisableClockReadyInterrupt(void);

/**
 * @brief Clears the Clock Ready interrupt flag.
 * @param None.
 * @return None.
 */
void MCLK_ClearClockReadyFlag(void);

/**
 * @brief Registers a callback for the Clock Ready event.
 * @param callback Function pointer to the callback to be registered.
 * @return None.
 */
void MCLK_SetCallbackHandler(MCLK_CALLBACK callback);



#ifdef __cplusplus
}
#endif

#endif /* PLIB_MCLK_H */
