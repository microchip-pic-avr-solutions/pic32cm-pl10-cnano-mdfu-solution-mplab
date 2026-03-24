/*******************************************************************************
* Copyright  2025 Microchip Technology Inc. and its subsidiaries.
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
 * @file plib_sercom_usart_common.h
 * @brief SERCOM USART Peripheral Library Common Definitions
 *
 * This file provides the common definitions for Macros, Enums, Structures, Variables etc.
 */

#ifndef PLIB_SERCOM_USART_COMMON_H
#define	PLIB_SERCOM_USART_COMMON_H

#ifdef	__cplusplus
extern "C" {
#endif

/**
 * @def USART_ERROR_NONE
 * @brief Error status when no error has occurred.
 */
#define USART_ERROR_NONE 0U

/**
 * @def USART_ERROR_PARITY
 * @brief Error status when a parity error has occurred.
 */
#define USART_ERROR_PARITY SERCOM_USART_STATUS_PERR_Msk

/**
 * @def USART_ERROR_FRAMING
 * @brief Error status when a framing error has occurred.
 */
#define USART_ERROR_FRAMING SERCOM_USART_STATUS_FERR_Msk

/**
 * @def USART_ERROR_OVERRUN
 * @brief Error status when an overrun error has occurred.
 */
#define USART_ERROR_OVERRUN SERCOM_USART_STATUS_BUFOVF_Msk

/**
 * @def USART_ERROR_COLLISION
 * @brief Error status when a collision detection has occurred.
 */
#define USART_ERROR_COLLISION SERCOM_USART_STATUS_COLL_Msk

/**
 * @typedef USART_ERROR
 * @brief Type for representing USART error status.
 */
typedef uint16_t USART_ERROR;

/**
 * @brief Global variable to hold the current USART error status.
 */
//extern USART_ERROR usart0_srror_status;

/**
 * @enum USART_HWREG_STATUS
 * @brief Status codes for USART hardware register operations.
 */
typedef enum {
 
    USART_HWREG_OK = 0,           /**< Operation successful */
    USART_HWREG_ERROR,            /**< Generic error */
    USART_HWREG_INVALID_PARAM,    /**< Invalid parameter passed */
    USART_HWREG_TIMEOUT,          /**< Operation timed out */
    USART_HWREG_BUSY,             /**< Hardware is busy */
    USART_HWREG_UNSUPPORTED       /**< Operation not supported */
} USART_HWREG_STATUS;

/**
 * @enum USART_OPMODE
 * @brief USART operating mode selection.
 */
typedef enum {
 
    USART_EXT = 0,           /**< External clock mode */
    USART_INT = 1            /**< Internal clock mode */
} USART_OPMODE;

/**
 * @enum USART_CHARSIZE
 * @brief USART character size selection.
 */
typedef enum {
 
    USART_DATA_8_BIT = 0,    /**< 8-bit data */
    USART_DATA_9_BIT = 1,    /**< 9-bit data */
    USART_DATA_5_BIT = 5,    /**< 5-bit data */
    USART_DATA_6_BIT = 6,    /**< 6-bit data */
    USART_DATA_7_BIT = 7     /**< 7-bit data */
} USART_CHARSIZE;

/**
 * @enum USART_FRAME_FORMAT
 * @brief USART frame format selection.
 */
typedef enum {
 
    USART_FRAME = 0,                 /**< Standard frame */
    USART_FRAME_WITH_PARITY = 1      /**< Frame with parity */
} USART_FRAME_FORMAT;

/**
 * @enum USART_PARITY_MODE
 * @brief USART parity mode selection.
 */
typedef enum {
 
    USART_EVEN_PARITY = 0,   /**< Even parity */
    USART_ODD_PARITY = 1     /**< Odd parity */
} USART_PARITY_MODE;

/**
 * @enum USART_COMM_MODE
 * @brief USART communication mode selection.
 */
typedef enum {
 
    USART_ASYNC_MODE = 0,    /**< Asynchronous mode */
    USART_SYNC_MODE = 1      /**< Synchronous mode */
} USART_COMM_MODE;

/**
 * @enum USART_STOPBITS
 * @brief USART stop bits selection.
 */
typedef enum {
 
    USART_STOP_1_BIT = 0,    /**< 1 stop bit */
    USART_STOP_2_BIT = 1     /**< 2 stop bits */
} USART_STOPBITS;

/**
 * @enum USART_DATA_ORDER
 * @brief USART data order selection.
 */
typedef enum {
 
    USART_MSB_FIRST = 0,     /**< MSB first */
    USART_LSB_FIRST = 1      /**< LSB first */
} USART_DATA_ORDER;

/**
 * @enum USART_RXDATA_PINOUT
 * @brief USART RX data pinout selection.
 */
typedef enum {
 
    USART_RX_PAD0 = 0,       /**< RX on PAD0 */
    USART_RX_PAD1 = 1,       /**< RX on PAD1 */
    USART_RX_PAD2 = 2,       /**< RX on PAD2 */
    USART_RX_PAD3 = 3        /**< RX on PAD3 */
} USART_RXDATA_PINOUT;

/**
 * @enum USART_TXDATA_PINOUT
 * @brief USART TX data pinout selection.
 */
typedef enum {
 
    USART_TX_PAD0 = 0,                   /**< TX on PAD0 */
    USART_TX_PAD2 = 1,                   /**< TX on PAD2 */
    USART_TX_PAD0_WITH_RTS_CTS = 2,      /**< TX on PAD0 with RTS/CTS */
    USART_TX_PAD0_WITH_TE = 3            /**< TX on PAD0 with TE */    
} USART_TXDATA_PINOUT;

/**
 * @enum USART_EVENT
 * @brief USART interrupt event list.
 */
typedef enum {
 
    USART_EVENT_REGISTER_EMPTY = 0,
    USART_EVENT_TRANSMIT_COMPLETE,
    USART_EVENT_RECEIVE_COMPLETE,
    USART_EVENT_ERROR 
} USART_EVENT;

/**
 * @typedef SERCOM_USART_CALLBACK_HANDLER
 * @brief Function pointer type for SERCOM USART event callback handler.
 *
 * This typedef defines a callback function type that is called when a USART event occurs.
 * The callback receives a single parameter indicating the event type.
 *
 * @param event The USART event that triggered the callback.
 *
 * @see USART_EVENT
 */
typedef void (*SERCOM_USART_CALLBACK_HANDLER)(USART_EVENT event);

#ifdef	__cplusplus
}
#endif

#endif	/* PLIB_SERCOM_USART_COMMON_H */

