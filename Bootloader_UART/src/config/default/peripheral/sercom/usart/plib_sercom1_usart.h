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
 * @file plib_sercom1_usart.h
 * @brief SERCOM1 USART Peripheral Library Interface
 *
 * This file provides the interface for configuring and controlling the SERCOM USART peripheral.
 */

/// @addtogroup SERCOM1_USART_Driver

#ifndef PLIB_SERCOM1_USART_H
#define PLIB_SERCOM1_USART_H

#include <pic32c.h>
#include <stddef.h>
#include <stdbool.h>
#include "plib_sercom_usart_common.h"
#include "plib_sercom_common.h"

/* Example usage of the USART0 PLIB interface.*/

/**
 * @example
 * @brief Example usage of the USART0 PLIB interface.
 *
 * This example demonstrates how to configure the USART0, and how to read from and write to the USART0.
 * It also shows how to register a callback for USART0 interrupts and handle different USART0 events.
 * Additionally, it demonstrates the configuration and usage of a USART ring buffer.
 * @code
 *
 * #include  "plib_sercom1_usart.h"
 *
 * // CPU clock frequency
 * #define CPU_CLOCK_FREQUENCY 4000000U   // change the frequency based on the system clock
 * uint8_t rx_byte = 0;
 *
  * int main(void) {
 *    // PORT_Initialize();     // Initialize Port
 *    // CLOCK_Initialize();    // Initialize Clock
 *    // USART Configure
 *    SERCOM1_USART_SetOperatingMode(USART_INT);              // Set operating mode to USART with internal clock
 *    SERCOM1_USART_SetCommunicationMode(USART_ASYNC_MODE);      // Set communication mode to asynchronous
 *    SERCOM1_USART_SetDataOrder(USART_LSB_FIRST);         // Set the data order to be shifted out
 *    SERCOM1_USART_SetBaudrate(9600, CPU_CLOCK_FREQUENCY);           // Set baud rate to 9600
 *    // Configure RX and TX PADS
 *    SERCOM1_USART_SetTxDataPinout(USART_TX_PAD0);                   // Set transmit data pinout  - Set this based on the hardware
 *    SERCOM1_USART_SetRxDataPinout(USART_RX_PAD1);                   // Set receive data pinout  - Set this based on the hardware
 *    // Enable UART
 *    SERCOM1_USART_EnableReceiver();                                 // Enable usart receiver
 *    SERCOM1_USART_EnableTransmitter();                              // Enable usart transmitter
 *    SERCOM1_USART_Enable();                                         // Enable usart
 *    SERCOM1_USART_SetInterruptHandler();                            // Set Interrupt handler
 *
 *    // write byte
 *    while (SERCOM1_USART_TxIsReady() == 0U) {
 *        // wait for TX
 *    }
 *    SERCOM1_USART_Send((uint8_t)'A');
 *
 *    while (true) {
 *        // read byte
 *        if (SERCOM1_USART_RxIsReady() == 1U) {
 *            rx_byte = SERCOM1_USART_Receive();
 *        }
 *    }
 *
 *    return 0;
 * }
 * @endcode
 */

/**
 * @brief Enables the SERCOM USART peripheral.
 * @param None.
 * @return None.
 */
void SERCOM1_USART_Enable(void);

/**
 * @brief Disables the SERCOM USART peripheral.
 * @param None.
 * @return None.
 */
void SERCOM1_USART_Disable(void);

/**
 * @brief Enables the USART transmitter.
 * @param None.
 * @return None.
 */
void SERCOM1_USART_EnableTransmitter(void);

/**
 * @brief Disables the USART transmitter.
 * @param None.
 * @return None.
 */
void SERCOM1_USART_DisableTransmitter(void);

/**
 * @brief Enables the USART receiver.
 * @param None.
 * @return None.
 */
void SERCOM1_USART_EnableReceiver(void);

/**
 * @brief Disables the USART receiver.
 * @param None.
 * @return None.
 */
void SERCOM1_USART_DisableReceiver(void);

/**
 * @brief Sets the USART operating mode.
 * @param mode - The desired operating mode (see @ref USART_OPMODE).
 * @return None.
 */
void SERCOM1_USART_SetOperatingMode(USART_OPMODE mode);

/**
 * @brief Sets the USART communication mode.
 * @param comm_mode - The desired communication mode (see @ref USART_COMM_MODE).
 * @return None.
 */
void SERCOM1_USART_SetCommunicationMode(USART_COMM_MODE comm_mode);

/**
 * @brief Sets the USART TX data pinout.
 * @param tx_pinout - The desired TX pinout (see @ref USART_RXDATA_PINOUT).
 * @return None.
 */
void SERCOM1_USART_SetTxDataPinout(USART_TXDATA_PINOUT tx_pinout);

/**
 * @brief Sets the USART RX data pinout.
 * @param rx_pinout - The desired RX pinout (see @ref USART_TXDATA_PINOUT).
 * @return None.
 */
void SERCOM1_USART_SetRxDataPinout(USART_RXDATA_PINOUT rx_pinout);

/**
 * @brief Sets the USART data size.
 * @param char_size - The desired character size (see @ref USART_CHARSIZE).
 * @return None.
 */
void SERCOM1_USART_SetDataSize(USART_CHARSIZE char_size);

/**
 * @brief Sets the USART frame format.
 * @param frame_format - The desired frame format (see @ref USART_FRAME_FORMAT).
 * @return None.
 */
void SERCOM1_USART_SetFrameFormat(USART_FRAME_FORMAT frame_format);

/**
 * @brief Sets the USART parity mode.
 * @param parity - The desired parity mode (see @ref USART_PARITY_MODE).
 * @return None.
 */
void SERCOM1_USART_SetParityMode(USART_PARITY_MODE parity);

/**
 * @brief Sets the USART stop bits.
 * @param stop_bits - The desired number of stop bits (see @ref USART_STOPBITS).
 * @return None.
 */
void SERCOM1_USART_SetStopBits(USART_STOPBITS stop_bits);

/**
 * @brief Sets the USART data order.
 * @param data_order - The desired data order (see @ref USART_DATA_ORDER).
 * @return None.
 */
void SERCOM1_USART_SetDataOrder(USART_DATA_ORDER data_order);

/**
 * @brief Sets the USART baud rate.
 * @param baud - Desired baud rate.
 * @param clk_frequency - Clock frequency in Hz.
 * @return Status - of the operation (see @ref USART_HWREG_STATUS).
 */
USART_HWREG_STATUS SERCOM1_USART_SetBaudrate(uint32_t baud, uint32_t clk_frequency);

/**
 * @brief Disables the receive complete interrupt.
 * @param None.
 * @return None.
 */
void SERCOM1_USART_DisableRxCompleteInterrupt(void);

/**
 * @brief Enables the receive complete interrupt.
 * @param None.
 * @return None.
 */
void SERCOM1_USART_EnableRxCompleteInterrupt(void);

/**
 * @brief Disables the transmit complete interrupt.
 * @param None.
 * @return None.
 */
void SERCOM1_USART_DisableTxCompleteInterrupt(void);

/**
 * @brief Enables the transmit complete interrupt.
 * @param None.
 * @return None.
 */
void SERCOM1_USART_EnableTxCompleteInterrupt(void);

/**
 * @brief Disables the data register empty interrupt.
 * @param None.
 * @return None.
 */
void SERCOM1_USART_DisableDataRegEmptyInterrupt(void);

/**
 * @brief Enables the data register empty interrupt.
 * @param None.
 * @return None.
 */
void SERCOM1_USART_EnableDataRegEmptyInterrupt(void);

/**
 * @brief Disables the error interrupt.
 * @param None.
 * @return None.
 */
void SERCOM1_USART_DisableErrorInterrupt(void);

/**
 * @brief Enables the error interrupt.
 * @param None.
 * @return None.
 */
void SERCOM1_USART_EnableErrorInterrupt(void);

/**
 * @brief Enables or disables collision detection.
 * @param collision_detection - true to enable, false to disable.
 * @return None.
 */
void SERCOM1_USART_EnableCollisionDetection(bool collision_detection);

/**
 * @brief Sends a byte of data via USART.
 * @param data - Byte to send.
 * @return None.
 */
void SERCOM1_USART_Send(uint8_t data);

/**
 * @brief Receives a byte of data from USART.
 * @param None.
 * @return Received byte.
 */
uint8_t SERCOM1_USART_Receive(void);

/**
 * @brief Sends 9-bit data via USART.
 * @param data - 9-bit data to send.
 * @return None.
 */
void SERCOM1_USART_Send9Bit(uint16_t data);

/**
 * @brief Receives 9-bit data from USART.
 * @param None.
 * @return Received 9-bit data.
 */
uint16_t SERCOM1_USART_Receive9Bit(void);

/**
 * @brief Checks if the USART transmitter is ready.
 * @param None.
 * @return true if transmitter is ready, false otherwise.
 */
bool SERCOM1_USART_TxIsReady(void);

/**
 * @brief Checks if the USART receiver is ready.
 * @param None.
 * @return true if receiver is ready, false otherwise.
 */
bool SERCOM1_USART_RxIsReady(void);

/**
 * @brief Checks if the USART transmission is complete.
 * @param None.
 * @return true if transmission is complete, false otherwise.
 */
bool SERCOM1_USART_TxIsDone(void);

/**
 * @brief Gets the current USART error status and clears it.
 * @param None.
 * @return The current error status (see @ref USART_ERROR).
 */
USART_ERROR SERCOM1_USART_ErrorGet(void);

/**
 * @brief Registers callback for the USART interrupt events.
 * @param callback - Pointer to the callback function.
 * @return None.
 */
void SERCOM1_USART_SetCallbackHandler(SERCOM_USART_CALLBACK_HANDLER callback);

/**
 * @brief Performs a software reset of the USART peripheral.
 * @param None.
 * @return None.
 */
void SERCOM1_USART_ResetSoftware(void);

/**
 * @brief Assigns the interrupt handler for SERCOM1 SPI.
 * @note Call this API when the SERCOM1 SPI interrupt is enabled.
 */
void SERCOM1_USART_SetInterruptHandler(void);
#endif /* PLIB_SERCOM1_USART_H */
