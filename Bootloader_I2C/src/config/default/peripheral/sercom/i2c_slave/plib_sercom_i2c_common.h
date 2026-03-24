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
 * @file plib_sercom_i2c_common.h
 * @brief SERCOM I2C Peripheral Library Common Definitions
 *
 * This file provides the common definitions for Host and Client data types.
 */
#ifndef PLIB_SERCOM_I2C_COMMON_H
#define	PLIB_SERCOM_I2C_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

#include <pic32c.h>

/**
 * @def I2C_CLIENT_ERROR_BUSERR
 * @brief Bus error detected on the I2C bus.
 */
#define I2C_CLIENT_ERROR_BUSERR  SERCOM_I2CS_STATUS_BUSERR_Msk

/**
 * @def I2C_CLIENT_ERROR_COLL
 * @brief Collision detected on the I2C bus.
 */
#define I2C_CLIENT_ERROR_COLL SERCOM_I2CS_STATUS_COLL_Msk

/**
 * @def I2C_CLIENT_ERROR_LOWTOUT
 * @brief SCL low timeout error detected.
 */
#define I2C_CLIENT_ERROR_LOWTOUT SERCOM_I2CS_STATUS_LOWTOUT_Msk

/**
 * @def I2C_CLIENT_ERROR_SEXTTOUT
 * @brief Slave SCL extend timeout error detected.
 */
#define I2C_CLIENT_ERROR_SEXTTOUT SERCOM_I2CS_STATUS_SEXTTOUT_Msk

/**
 * @def I2C_CLIENT_ERROR_ALL
 * @brief Mask for all I2C client error conditions.
 */
#define I2C_CLIENT_ERROR_ALL (I2C_CLIENT_ERROR_BUSERR | I2C_CLIENT_ERROR_COLL  | I2C_CLIENT_ERROR_LOWTOUT  | I2C_CLIENT_ERROR_SEXTTOUT)

/**
 * @enum I2C_OPMODE
 * @brief I2C operating mode selection.
 */
typedef enum {
    CLIENT_MODE = 0x4U, /**< I2C Slave mode*/
    HOST_MODE = 0x5U /**< I2C Host mode*/
} I2C_OPMODE;

/**
 * @enum I2C_HOST_HWREG_STATUS
 * @brief Status codes for USART hardware register operations.
 */
typedef enum {
    I2C_HOST_HWREG_OK = 0, /**< Operation successful */
    I2C_HOST_HWREG_ERROR, /**< Generic error */
    I2C_HOST_HWREG_INVALID_PARAM, /**< Invalid parameter passed */
    I2C_HOST_HWREG_TIMEOUT, /**< Operation timed out */
    I2C_HOST_HWREG_BUSY, /**< Hardware is busy */
    I2C_HOST_HWREG_UNSUPPORTED /**< Operation not supported */
} I2C_HOST_HWREG_STATUS;

/**
 * @enum I2C_HOST_EVENT
 * @brief I2C interrupt event codes.
 */
typedef enum {
    I2C_HOST_EVENT_BUS_ERROR = 1U,
    I2C_HOST_EVENT_ARBITRATION_LOST = 2U,
    I2C_HOST_EVENT_NACK = 4U,
    I2C_HOST_EVENT_TRANSFER = 8U
} I2C_HOST_EVENT;

/**
 * @enum I2C_HOST_INTERRUPT
 * @brief I2C Interrupts selection.
 */
typedef enum {
    HOST_ON_BUS_INTERRUPT = SERCOM_I2CM_INTENSET_MB_Msk, /**< Host on Bus Interrupt Enable */
    CLIENT_ON_BUS_INTERRUPT = SERCOM_I2CM_INTENSET_SB_Msk, /**< Client on Bus Interrupt Enable */
    ERROR_INTERRUPT = SERCOM_I2CM_INTENSET_ERROR_Msk, /**< Error Interrupt Enable */
    HOST_INTERRUPT_ALL = SERCOM_I2CM_INTENSET_Msk
} I2C_HOST_INTERRUPT;

/**
 * @enum I2C_HOST_TRANSFER_SPEED_MODE
 * @brief I2C Speed mode selection.
 */
typedef enum {
    I2C_HOST_STANDARD_MODE = 0UL, /**< Standard-mode (Sm) up to 100 kHz and Fast-mode (Fm) up to 400 kHz */
    I2C_HOST_FAST_MODE = 0UL,    /**< Standard-mode (Sm) up to 100 kHz and Fast-mode (Fm) up to 400 kHz */
    I2C_HOST_FAST_MODE_PLUS = 1UL, /**< Fast-mode Plus (Fm+) up to 1 MHz */
    I2C_HOST_HIGH_SPEED_MODE = 2UL, /**< High-speed mode (Hs-mode) up to 3.4 MHz */
} I2C_HOST_TRANSFER_SPEED_MODE;

/**
 * @enum I2C_HOST_ACK_ACTION
 * @brief Acknowledge Action selection.
 */
typedef enum {
    I2C_HOST_SEND_ACK = 0, /**< Send ACK when a command is written to CTRLB.CMD */
    I2C_HOST_SEND_NACK = 1, /**< Send NACK when a command is written to CTRLB.CMD */
} I2C_HOST_ACK_ACTION;
    
/**
 * @enum I2C_HOST_SDA_HOLD_TIME
 * @brief SDA Hold time selection.
 */
typedef enum {
    I2C_HOST_HOLD_TIME_DISABLE = 0x0, /**< Disabled*/
    I2C_HOST_HOLD_TIME_75NS = 0x1, /**< 50-100ns hold time*/
    I2C_HOST_HOLD_TIME_450NS = 0x2, /**< 300-600ns hold time*/
    I2C_HOST_HOLD_TIME_600NS = 0x3 /**< 400-800ns hold time*/
} I2C_HOST_SDA_HOLD_TIME;

/**
 * @enum I2C_HOST_SCL_CLK_STRETCH_MODE
 * @brief Selection for stretching SCL for software interaction.
 */
typedef enum {
    SLC_STRETCH_BEFORE_OR_AFTER_ACK = 0, /**< SCL stretch before or after ACK*/
    SLC_STRETCH_ONLY_AFTER_ACK = 1 /**< SCL stretch only after ACK bit*/
} I2C_HOST_SCL_CLK_STRETCH_MODE;

/**
 * @enum I2C_CLIENT_DIR
 * @brief I2C client transfer direction.
 */
typedef enum {
    I2C_CLIENT_DIR_WRITE = 0, /**< I2C Host is writing to client. */
    I2C_CLIENT_DIR_READ = 1 /**< I2C Host is reading from client. */
} I2C_CLIENT_DIR;

/**
 * @enum I2C_CLIENT_ACK_STATUS
 * @brief ACK/NACK status for last data packet sent.
 */
typedef enum {
    I2C_CLIENT_ACK_RECEIVED = 0, /**< Host responded with ACK. */
    I2C_CLIENT_NACK_RECEIVED = 1 /**< Host responded with NACK. */
} I2C_CLIENT_ACK_STATUS;

/**
 * @enum I2C_CLIENT_COMMAND
 * @brief I2C client command actions.
 */
typedef enum {
    I2C_CLIENT_COMMAND_SEND_ACK = 0, /**< Send ACK to the host. */
    I2C_CLIENT_COMMAND_SEND_NAK, /**< Send NAK to the host. */
    I2C_CLIENT_COMMAND_RECEIVE_ACK_NAK, /**< Receive ACK/NAK from the host (no ACKACT update). */
    I2C_CLIENT_COMMAND_WAIT_FOR_START /**< Wait for a new START condition. */
} I2C_CLIENT_COMMAND;

/**
 * @enum I2C_CLIENT_TRANSFER_EVENT
 * @brief I2C client transfer event types.
 */
typedef enum {
    I2C_CLIENT_TRANSFER_EVENT_NONE = 0, /**< No event. */
    I2C_CLIENT_TRANSFER_EVENT_ADDR_MATCH, /**< Address match event. */
    I2C_CLIENT_TRANSFER_EVENT_RX_READY, /**< Data sent by I2C Host is available. */
    I2C_CLIENT_TRANSFER_EVENT_TX_READY, /**< I2C client can respond to data read request from I2C Host. */
    I2C_CLIENT_TRANSFER_EVENT_STOP_BIT_RECEIVED, /**< Stop bit received event. */
    I2C_CLIENT_TRANSFER_EVENT_ERROR /**< Error event. */
} I2C_CLIENT_TRANSFER_EVENT;

/**
 * @enum I2C_CLIENT_INTERRUPT
 * @brief I2C Client Interrupt options.
 */
typedef enum {
    I2C_CLIENT_INT_ERROR = SERCOM_I2CS_INTENSET_ERROR_Msk, /**< I2C Client Error Interrupt. */
    I2C_CLIENT_INT_DRDY = SERCOM_I2CS_INTENSET_DRDY_Msk, /**< I2C Client Data Ready Interrupt. */
    I2C_CLIENT_INT_AMATCH = SERCOM_I2CS_INTENSET_AMATCH_Msk, /**< I2C Client Address Match Interrupt. */
    I2C_CLIENT_INT_PREC = SERCOM_I2CS_INTENSET_PREC_Msk, /**< I2C Client Stop Received Interrupt. */
    I2C_CLIENT_INT_ALL = SERCOM_I2CS_INTENSET_Msk /**< I2C Client all Interrupts. */
} I2C_CLIENT_INTERRUPT;

/**
 * @enum I2C_CLIENT_INTFLAG
 * @brief SERCOM I2C interrupt flag bits.
 */
typedef enum {
    I2C_CLIENT_INTFLAG_PREC = SERCOM_I2CS_INTFLAG_PREC_Msk, /**< Stop Received */
    I2C_CLIENT_INTFLAG_AMATCH = SERCOM_I2CS_INTFLAG_AMATCH_Msk, /**< Address Match */
    I2C_CLIENT_INTFLAG_DRDY = SERCOM_I2CS_INTFLAG_DRDY_Msk, /**< Data Ready */
    I2C_CLIENT_INTFLAG_ERROR = SERCOM_I2CS_INTFLAG_ERROR_Msk, /**< Error */
    I2C_CLIENT_INTFLAG_ALL = SERCOM_I2CS_INTFLAG_Msk        
} I2C_CLIENT_INTFLAG;

/**
 * @typedef SERCOM_I2C_CALLBACK_HANDLER
 * @brief Function pointer type for SERCOM I2C event callback handler.
 */
typedef void (*SERCOM_I2C_CALLBACK_HANDLER)(void);

#ifdef __cplusplus
}
#endif

#endif	/* PLIB_SERCOM_I2C_COMMON_H */

