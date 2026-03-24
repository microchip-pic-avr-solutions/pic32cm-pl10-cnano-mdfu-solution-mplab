/*******************************************************************************
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

/**
 * @file plib_sercom_common.h
 *
 * @brief Common definitions for SERCOM 
 *
 * @details The SERCOM common header defines enums and macros used
 *          by all SERCOM instances for configuration and operation.
 */

#ifndef PLIB_SERCOM_COMMON_H
#define PLIB_SERCOM_COMMON_H

#include <pic32c.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @typedef SERCOM_INTERRUPT_HANDLER
 * @brief Function pointer type for SERCOM1 interrupt handlers.
 *
 * This typedef defines a function pointer for interrupt handlers associated with SERCOM.
 * The handler function must take no parameters and return void.
 */
typedef void (*SERCOM_INTERRUPT_HANDLER)(void);

#ifdef __cplusplus
}
#endif

#endif /* PLIB_SERCOM_COMMON_H */