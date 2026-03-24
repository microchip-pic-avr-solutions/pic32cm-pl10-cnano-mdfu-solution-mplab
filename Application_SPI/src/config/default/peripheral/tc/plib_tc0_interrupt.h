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
/******************************************************************************
* @file plib_tc0_interrupt.h
*
* @brief TC0 Interrupt Callback Interface
*
* @details Public API declarations for TC0 interrupt callback registration 
* and handler.
*******************************************************************************/

#ifndef PLIB_TC0_INTERRUPT_H
#define PLIB_TC0_INTERRUPT_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif
    
/**
 * @brief Registers the TC0 interrupt callback function.
 * The callback function can be called from main.c for direct
 * callback registration.
 *
 * @param[in] callback Pointer to user-defined TC0 interrupt handler function.
 *                     Pass NULL to unregister any existing callback.
 */
void TC0_SetInterruptHandler(void(*callback)(void));

#ifdef	__cplusplus
}
#endif

#endif	/* PLIB_TC0_INTERRUPT_H */