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
 ******************************************************************************/

/**
 * @file plib_sercom1_usart.c
 * @brief SERCOM1 USART Peripheral Library Interface
 *
 * This file implements the interface for configuring and controlling the SERCOM USART peripheral.
 */

#include "plib_sercom1_usart.h"

extern volatile SERCOM_INTERRUPT_HANDLER SERCOM1_InterruptHandler;

static SERCOM_USART_CALLBACK_HANDLER sercom1_usart_callback_handler = NULL;

static USART_ERROR usart1_error_status = USART_ERROR_NONE;

void SERCOM1_USART_Enable(void)
{
    SERCOM1_REGS->USART.SERCOM_CTRLA |= SERCOM_USART_CTRLA_ENABLE_Msk;
    // Wait for synchronization to complete
    while ((SERCOM1_REGS->USART.SERCOM_SYNCBUSY & SERCOM_USART_SYNCBUSY_ENABLE_Msk) == SERCOM_USART_SYNCBUSY_ENABLE_Msk) {
	 
        // Wait for the enable operation to complete
    }
}

void SERCOM1_USART_Disable(void)
{
    SERCOM1_REGS->USART.SERCOM_CTRLA &= ~SERCOM_USART_CTRLA_ENABLE_Msk;
    // Wait for synchronization to complete
    while ((SERCOM1_REGS->USART.SERCOM_SYNCBUSY & SERCOM_USART_SYNCBUSY_ENABLE_Msk) == SERCOM_USART_SYNCBUSY_ENABLE_Msk) {
	 
        // Wait for the disable operation to complete
    }
}

void SERCOM1_USART_EnableTransmitter(void)
{
    SERCOM1_REGS->USART.SERCOM_CTRLB |= SERCOM_USART_CTRLB_TXEN_Msk;
    // Wait for synchronization to complete
    while ((SERCOM1_REGS->USART.SERCOM_SYNCBUSY & SERCOM_USART_SYNCBUSY_CTRLB_Msk) == SERCOM_USART_SYNCBUSY_CTRLB_Msk) {
	 
        // Wait for the enable operation to complete
    }
}

void SERCOM1_USART_DisableTransmitter(void)
{
    SERCOM1_REGS->USART.SERCOM_CTRLB &= ~SERCOM_USART_CTRLB_TXEN_Msk;
    // Wait for synchronization to complete
    while ((SERCOM1_REGS->USART.SERCOM_SYNCBUSY & SERCOM_USART_SYNCBUSY_CTRLB_Msk) == SERCOM_USART_SYNCBUSY_CTRLB_Msk) {
	 
        // Wait for the disable operation to complete
    }
}

void SERCOM1_USART_EnableReceiver(void)
{
    SERCOM1_REGS->USART.SERCOM_CTRLB |= SERCOM_USART_CTRLB_RXEN_Msk;
    // Wait for synchronization to complete
    while ((SERCOM1_REGS->USART.SERCOM_SYNCBUSY & SERCOM_USART_SYNCBUSY_CTRLB_Msk) == SERCOM_USART_SYNCBUSY_CTRLB_Msk) {
	 
        // Wait for the enable operation to complete
    }
}

void SERCOM1_USART_DisableReceiver(void)
{
    SERCOM1_REGS->USART.SERCOM_CTRLB &= ~SERCOM_USART_CTRLB_RXEN_Msk;
    // Wait for synchronization to complete
    while ((SERCOM1_REGS->USART.SERCOM_SYNCBUSY & SERCOM_USART_SYNCBUSY_CTRLB_Msk) == SERCOM_USART_SYNCBUSY_CTRLB_Msk) {
	 
        // Wait for the disable operation to complete
    }
}

void SERCOM1_USART_SetOperatingMode(USART_OPMODE mode)
{
    SERCOM1_REGS->USART.SERCOM_CTRLA = (SERCOM1_REGS->USART.SERCOM_CTRLA & ~SERCOM_USART_CTRLA_MODE_Msk) | SERCOM_USART_CTRLA_MODE(mode);
}

void SERCOM1_USART_SetCommunicationMode(USART_COMM_MODE comm_mode)
{
    SERCOM1_REGS->USART.SERCOM_CTRLA = (SERCOM1_REGS->USART.SERCOM_CTRLA & ~SERCOM_USART_CTRLA_CMODE_Msk) | SERCOM_USART_CTRLA_CMODE(comm_mode);
}

void SERCOM1_USART_SetTxDataPinout(USART_TXDATA_PINOUT tx_pinout)
{
    SERCOM1_REGS->USART.SERCOM_CTRLA = (SERCOM1_REGS->USART.SERCOM_CTRLA & ~SERCOM_USART_CTRLA_TXPO_Msk) | SERCOM_USART_CTRLA_TXPO(tx_pinout);
}

void SERCOM1_USART_SetRxDataPinout(USART_RXDATA_PINOUT rx_pinout)
{
    SERCOM1_REGS->USART.SERCOM_CTRLA = (SERCOM1_REGS->USART.SERCOM_CTRLA & ~SERCOM_USART_CTRLA_RXPO_Msk) | SERCOM_USART_CTRLA_RXPO(rx_pinout);
}

void SERCOM1_USART_SetDataOrder(USART_DATA_ORDER data_order)
{
    SERCOM1_REGS->USART.SERCOM_CTRLA = (SERCOM1_REGS->USART.SERCOM_CTRLA & ~SERCOM_USART_CTRLA_DORD_Msk) | SERCOM_USART_CTRLA_DORD(data_order);
}

void SERCOM1_USART_SetFrameFormat(USART_FRAME_FORMAT frame_format)
{
    SERCOM1_REGS->USART.SERCOM_CTRLA = (SERCOM1_REGS->USART.SERCOM_CTRLA & ~SERCOM_USART_CTRLA_FORM_Msk) | SERCOM_USART_CTRLA_FORM(frame_format);
}

void SERCOM1_USART_SetParityMode(USART_PARITY_MODE parity)
{
    SERCOM1_REGS->USART.SERCOM_CTRLB = (SERCOM1_REGS->USART.SERCOM_CTRLB & ~SERCOM_USART_CTRLB_PMODE_Msk) | SERCOM_USART_CTRLB_PMODE(parity);
    // Wait for synchronization to complete
    while ((SERCOM1_REGS->USART.SERCOM_SYNCBUSY & SERCOM_USART_SYNCBUSY_CTRLB_Msk) == SERCOM_USART_SYNCBUSY_CTRLB_Msk) {
	 
        // Wait for the operation to complete
    }
}

void SERCOM1_USART_SetDataSize(USART_CHARSIZE char_size)
{
    SERCOM1_REGS->USART.SERCOM_CTRLB = (SERCOM1_REGS->USART.SERCOM_CTRLB & ~SERCOM_USART_CTRLB_CHSIZE_Msk) | SERCOM_USART_CTRLB_CHSIZE(char_size);
    // Wait for synchronization to complete
    while ((SERCOM1_REGS->USART.SERCOM_SYNCBUSY & SERCOM_USART_SYNCBUSY_CTRLB_Msk) == SERCOM_USART_SYNCBUSY_CTRLB_Msk) {	 
        // Wait for the operation to complete
    }
}

void SERCOM1_USART_SetStopBits(USART_STOPBITS stop_bits)
{
    SERCOM1_REGS->USART.SERCOM_CTRLB = (SERCOM1_REGS->USART.SERCOM_CTRLB & ~SERCOM_USART_CTRLB_SBMODE_Msk) | SERCOM_USART_CTRLB_SBMODE(stop_bits);
    // Wait for synchronization to complete
    while ((SERCOM1_REGS->USART.SERCOM_SYNCBUSY & SERCOM_USART_SYNCBUSY_CTRLB_Msk) == SERCOM_USART_SYNCBUSY_CTRLB_Msk) {
        // Wait for the operation to complete
    }
}

USART_HWREG_STATUS SERCOM1_USART_SetBaudrate(uint32_t baud, uint32_t clk_frequency)
{
    USART_HWREG_STATUS status = USART_HWREG_OK;
    uint32_t baud_value = 0UL;
    uint32_t sample_count = 0UL;
    uint32_t sampleRate = 0U;
    uint32_t ref_clk_frequency = 0UL;

    if (clk_frequency == 0UL) {
        // Consider default clock frequency if clock frequency is not defined
        return USART_HWREG_ERROR;
    } else {
        ref_clk_frequency = clk_frequency;
    }

    if (clk_frequency >= (16UL * baud)) {
        sample_count = 16UL;
        sampleRate = 0U;
    } else if (clk_frequency >= (8UL * baud)) {
        sample_count = 8UL;
        sampleRate = 2U;
    } else if (clk_frequency >= (3UL * baud)) {
        sample_count = 3UL;
        sampleRate = 4U;
    } else {
        return USART_HWREG_ERROR;
    }

    baud_value = 65536UL - (uint32_t) (((uint64_t) 65536UL * sample_count * baud) / ref_clk_frequency);
    SERCOM1_REGS->USART.SERCOM_BAUD = (uint16_t) SERCOM_USART_BAUD_ARITH_BAUD(baud_value);
    SERCOM1_REGS->USART.SERCOM_CTRLA = (SERCOM1_REGS->USART.SERCOM_CTRLA & (~SERCOM_USART_CTRLA_SAMPR_Msk)) | SERCOM_USART_CTRLA_SAMPR((uint32_t)sampleRate);   
    
    return status;
}

void SERCOM1_USART_Send(uint8_t data)
{
    SERCOM1_REGS->USART.SERCOM_DATA = (uint8_t)data;
}

uint8_t SERCOM1_USART_Receive(void)
{
    return ((uint8_t)SERCOM1_REGS->USART.SERCOM_DATA);
}

void SERCOM1_USART_Send9Bit(uint16_t data)
{
    SERCOM1_REGS->USART.SERCOM_DATA = data;
}

uint16_t SERCOM1_USART_Receive9Bit(void)
{
    return SERCOM1_REGS->USART.SERCOM_DATA;
}

bool SERCOM1_USART_TxIsReady(void)
{
    bool transmitter_status = false;
    if ((SERCOM1_REGS->USART.SERCOM_INTFLAG & SERCOM_USART_INTFLAG_DRE_Msk) == SERCOM_USART_INTFLAG_DRE_Msk) {
        transmitter_status = true;
    }
    return transmitter_status;
}

bool SERCOM1_USART_RxIsReady(void)
{
    bool receiver_status = false;
    if ((SERCOM1_REGS->USART.SERCOM_INTFLAG & SERCOM_USART_INTFLAG_RXC_Msk) == SERCOM_USART_INTFLAG_RXC_Msk) {
        receiver_status = true;
    }
    return receiver_status;
}

bool SERCOM1_USART_TxIsDone(void)
{
    bool transmit_complete = false;
    if ((SERCOM1_REGS->USART.SERCOM_INTFLAG & SERCOM_USART_INTFLAG_TXC_Msk) == SERCOM_USART_INTFLAG_TXC_Msk) {
        transmit_complete = true;
    }
    return transmit_complete;
}

void SERCOM1_USART_DisableRxCompleteInterrupt(void)
{
    SERCOM1_REGS->USART.SERCOM_INTENCLR = SERCOM_USART_INTENCLR_RXC_Msk;
}

void SERCOM1_USART_EnableRxCompleteInterrupt(void)
{
    SERCOM1_REGS->USART.SERCOM_INTENSET |= SERCOM_USART_INTENSET_RXC_Msk;
}

void SERCOM1_USART_DisableTxCompleteInterrupt(void)
{
    SERCOM1_REGS->USART.SERCOM_INTENCLR = SERCOM_USART_INTENCLR_TXC_Msk;
}

void SERCOM1_USART_EnableTxCompleteInterrupt(void)
{
    SERCOM1_REGS->USART.SERCOM_INTENSET |= SERCOM_USART_INTENSET_TXC_Msk;
}

void SERCOM1_USART_DisableDataRegEmptyInterrupt(void)
{
    SERCOM1_REGS->USART.SERCOM_INTENCLR = SERCOM_USART_INTENCLR_DRE_Msk;
}

void SERCOM1_USART_EnableDataRegEmptyInterrupt(void)
{
    SERCOM1_REGS->USART.SERCOM_INTENSET |= SERCOM_USART_INTENSET_DRE_Msk;
}

void SERCOM1_USART_DisableErrorInterrupt(void)
{
    SERCOM1_REGS->USART.SERCOM_INTENCLR = SERCOM_USART_INTENCLR_ERROR_Msk;
}

void SERCOM1_USART_EnableErrorInterrupt(void)
{
    SERCOM1_REGS->USART.SERCOM_INTENSET |= SERCOM_USART_INTENSET_ERROR_Msk;
}

void SERCOM1_USART_EnableCollisionDetection(bool collision_detection)
{
    SERCOM1_REGS->USART.SERCOM_CTRLB = (SERCOM1_REGS->USART.SERCOM_CTRLB & ~SERCOM_USART_CTRLB_COLDEN_Msk) | SERCOM_USART_CTRLB_COLDEN(collision_detection);
    // Wait for synchronization to complete
    while ((SERCOM1_REGS->USART.SERCOM_SYNCBUSY & SERCOM_USART_SYNCBUSY_CTRLB_Msk) == SERCOM_USART_SYNCBUSY_CTRLB_Msk) {
        // Wait for the operation to complete
    }
}

void SERCOM1_USART_ResetSoftware(void)
{
    SERCOM1_REGS->USART.SERCOM_CTRLA |= SERCOM_USART_CTRLA_SWRST_Msk;
    // Wait for synchronization to complete
    while ((SERCOM1_REGS->USART.SERCOM_SYNCBUSY & SERCOM_USART_SYNCBUSY_SWRST_Msk) == SERCOM_USART_SYNCBUSY_SWRST_Msk) {
        // Wait for the software reset operation to complete
    }
}

void SERCOM1_USART_SetCallbackHandler(SERCOM_USART_CALLBACK_HANDLER callback)
{
    // sercom1_usart_callback_handler is allowed to dereference after use
    sercom1_usart_callback_handler = callback;
}

static void  SERCOM1_USART_InterruptHandler(void) 
{
    bool interrupt_flag_status = false;
    bool interrupt_enable_status = false;

    if (SERCOM1_REGS->USART.SERCOM_INTENSET != 0U) {
        
        /* Checks for error flag */
        interrupt_flag_status = ((SERCOM1_REGS->USART.SERCOM_INTFLAG & SERCOM_USART_INTFLAG_ERROR_Msk) == SERCOM_USART_INTFLAG_ERROR_Msk);
        interrupt_enable_status = ((SERCOM1_REGS->USART.SERCOM_INTENSET & SERCOM_USART_INTENSET_ERROR_Msk) == SERCOM_USART_INTENSET_ERROR_Msk);
        if (interrupt_flag_status && interrupt_enable_status) {		 																																  
            usart1_error_status = (USART_ERROR) (SERCOM1_REGS->USART.SERCOM_STATUS & (uint16_t) (SERCOM_USART_STATUS_PERR_Msk | SERCOM_USART_STATUS_FERR_Msk | SERCOM_USART_STATUS_BUFOVF_Msk | SERCOM_USART_STATUS_COLL_Msk));
            // Call the registered error callback
            if (sercom1_usart_callback_handler != NULL) {			 
                sercom1_usart_callback_handler(USART_EVENT_ERROR);
            }
            /* Clear error flag */
            SERCOM1_REGS->USART.SERCOM_INTFLAG = (uint8_t) SERCOM_USART_INTFLAG_ERROR_Msk;
            /* Clear all errors */
            SERCOM1_REGS->USART.SERCOM_STATUS = (uint16_t) (SERCOM_USART_STATUS_PERR_Msk | SERCOM_USART_STATUS_FERR_Msk | SERCOM_USART_STATUS_BUFOVF_Msk | SERCOM_USART_STATUS_COLL_Msk);																																			 
        }

        interrupt_flag_status = ((SERCOM1_REGS->USART.SERCOM_INTFLAG & SERCOM_USART_INTFLAG_TXC_Msk) == SERCOM_USART_INTFLAG_TXC_Msk);
        interrupt_enable_status = ((SERCOM1_REGS->USART.SERCOM_INTENSET & SERCOM_USART_INTENSET_TXC_Msk) == SERCOM_USART_INTENSET_TXC_Msk);
        /* Checks for transmission complete flag */
        if (interrupt_flag_status && interrupt_enable_status) {
            // Call the registered transmit callback
             if (sercom1_usart_callback_handler != NULL) {			 
                sercom1_usart_callback_handler(USART_EVENT_TRANSMIT_COMPLETE);
            }
            /* Clear error flag */
            SERCOM1_REGS->USART.SERCOM_INTFLAG = (uint8_t) SERCOM_USART_INTFLAG_TXC_Msk;
        }

        interrupt_flag_status = ((SERCOM1_REGS->USART.SERCOM_INTFLAG & SERCOM_USART_INTFLAG_DRE_Msk) == SERCOM_USART_INTFLAG_DRE_Msk);
        interrupt_enable_status = ((SERCOM1_REGS->USART.SERCOM_INTENSET & SERCOM_USART_INTENSET_DRE_Msk) == SERCOM_USART_INTENSET_DRE_Msk);
        /* Checks for data register empty flag */
        if (interrupt_flag_status && interrupt_enable_status) {
            // Call the registered data register empty callback
            if (sercom1_usart_callback_handler != NULL) {			 
                sercom1_usart_callback_handler(USART_EVENT_REGISTER_EMPTY);
            }
            // Interrupt flag is cleared by writing new data to DATA register.
        }

        interrupt_flag_status = ((SERCOM1_REGS->USART.SERCOM_INTFLAG & SERCOM_USART_INTFLAG_RXC_Msk) == SERCOM_USART_INTFLAG_RXC_Msk);
        interrupt_enable_status = ((SERCOM1_REGS->USART.SERCOM_INTENSET & SERCOM_USART_INTENSET_RXC_Msk) == SERCOM_USART_INTENSET_RXC_Msk);
        /* Checks for receive complete flag */
        if (interrupt_flag_status && interrupt_enable_status) {
            // Call the registered Receive callback
            if (sercom1_usart_callback_handler != NULL) {			 
                sercom1_usart_callback_handler(USART_EVENT_RECEIVE_COMPLETE);
            }
            // Interrupt flag is cleared by reading the DATA register.
        }
        
    }else {
        //unhandled intererupt
    }
}

USART_ERROR SERCOM1_USART_ErrorGet(void)
{
    USART_ERROR status = usart1_error_status;
    usart1_error_status = USART_ERROR_NONE;
    return status;
}

void SERCOM1_USART_SetInterruptHandler(void)
{
    SERCOM1_InterruptHandler = SERCOM1_USART_InterruptHandler;
}