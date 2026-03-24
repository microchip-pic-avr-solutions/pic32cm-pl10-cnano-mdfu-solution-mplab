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
 * @file plib_sercom0_i2c_client.h
 * @brief SERCOM0 I2C Client Peripheral Library Interface
 *
 * This file provides the interface for configuring and controlling the SERCOM I2C peripheral in Client mode.
 */

#ifndef PLIB_SERCOM0_I2C_CLIENT_H
#define PLIB_SERCOM0_I2C_CLIENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "plib_sercom_i2c_common.h"    
#include "plib_sercom_common.h"

/**
 * @brief Resets the SERCOM0 I2C client peripheral.
 */
void SERCOM0_I2CS_ResetSoftware(void);

/**
 * @brief Enables the SERCOM0 I2C client peripheral.
 */
void SERCOM0_I2CS_Enable(void);

/**
 * @brief Disables the SERCOM0 I2C client peripheral.
 */
void SERCOM0_I2CS_Disable(void);

/**
 * @brief Sets up the SERCOM0 I2C client mode.
 * @pre SERCOM0 module must be disabled before calling this API.
 */
void SERCOM0_I2CS_SetOperatingMode(void);

/**
 * @brief Sets the I2C client address.
 * @param addr 7-bit I2C address.
 * @pre SERCOM0 module must be disabled before calling this API.
 */
void SERCOM0_I2CS_Set7bitAddress(uint8_t addr);

/**
 * @brief Sets the I2C client address mask.
 * @param addr_mask 7-bit address mask.
 * @pre SERCOM0 module must be disabled before calling this API.
 */
void SERCOM0_I2CS_Set7bitAddressMask(uint8_t addr_mask);

/**
 * @brief Enables or disables general call address recognition.
 * @param value true to enable, false to disable.
 */
void SERCOM0_I2CS_SetGeneralCall(bool value);

/**
 * @brief Reads a byte of data from the I2C client.
 * @return Received data byte.
 */
uint8_t SERCOM0_I2CS_ReceiveData(void);

/**
 * @brief Writes a byte of data to the I2C client.
 * @param data Data byte to send.
 */
void SERCOM0_I2CS_SendData(uint8_t data);

/**
 * @brief Gets and clears error status for the I2C client.
 * @return Error status bits.
 */
uint32_t SERCOM0_I2C_GetError(void);

/**
 * @brief Gets the current transfer direction (read/write).
 * @return Transfer direction enum value.
 */
I2C_CLIENT_DIR SERCOM0_I2CS_GetTransferDirection(void);

/**
 * @brief Gets the ACK/NACK status for the last data packet sent.
 * @return ACK/NACK status enum value.
 */
I2C_CLIENT_ACK_STATUS SERCOM0_I2CS_GetLastByteAckStatus(void);

/**
 * @brief Sets a command for the I2C client.
 * @param command Command enum value.
 */
void SERCOM0_I2CS_SetCommand(I2C_CLIENT_COMMAND command);

/**
 * @brief Get current I2C bus status for SERCOM0.
 * @return Current bus event.
 */
I2C_CLIENT_TRANSFER_EVENT SERCOM0_I2CS_GetBusStatus(void);
/**
 * @brief Enables specific I2C client interrupts.
 * @param interrupts Interrupt mask.
 */
void SERCOM0_I2CS_EnableInterrupts(I2C_CLIENT_INTERRUPT interrupts);

/**
 * @brief Disables specific I2C client interrupts.
 * @param interrupts Interrupt mask.
 */
void SERCOM0_I2CS_DisableInterrupts(I2C_CLIENT_INTERRUPT interrupts);

/**
 * @brief Clears specific I2C client interrupt flags.
 * @param interrupt_flags Interrupt flag mask.
 */
void SERCOM0_I2CS_ClearInterruptFlags(I2C_CLIENT_INTFLAG interrupt_flags);
void SERCOM0_I2CS_SetCallbackHandler(SERCOM_I2C_CALLBACK_HANDLER callback);
void SERCOM0_I2CS_SetInterruptHandler(void);
#ifdef __cplusplus
}
#endif

#endif /* PLIB_SERCOM0_I2C_CLIENT_H */
