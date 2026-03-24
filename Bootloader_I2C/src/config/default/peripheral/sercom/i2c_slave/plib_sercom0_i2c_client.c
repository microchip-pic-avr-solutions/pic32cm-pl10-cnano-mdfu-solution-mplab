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
 * @file plib_sercom0_i2c_client.c
 * @brief SERCOM0 I2C Client Peripheral Library Interface
 *
 * This file implements the interface for configuring and controlling the SERCOM I2C peripheral in client mode.
 */

#include "plib_sercom0_i2c_client.h"

extern volatile SERCOM_INTERRUPT_HANDLER SERCOM0_InterruptHandler;
static SERCOM_I2C_CALLBACK_HANDLER sercom0_i2cs_callback_handler = NULL;

void SERCOM0_I2CS_ResetSoftware(void)
{
    SERCOM0_REGS->I2CS.SERCOM_CTRLA |= SERCOM_I2CS_CTRLA_SWRST_Msk;
    while (SERCOM0_REGS->I2CS.SERCOM_SYNCBUSY != 0U)
    {
        // Wait for synchronization
    }
}

void SERCOM0_I2CS_Enable(void)
{
    SERCOM0_REGS->I2CS.SERCOM_CTRLA |= SERCOM_I2CS_CTRLA_ENABLE_Msk;
    while (SERCOM0_REGS->I2CS.SERCOM_SYNCBUSY != 0U)
    {
        // Wait for synchronization
    }
}

void SERCOM0_I2CS_Disable(void)
{
    SERCOM0_REGS->I2CS.SERCOM_CTRLA &= ~SERCOM_I2CS_CTRLA_ENABLE_Msk;
    while (SERCOM0_REGS->I2CS.SERCOM_SYNCBUSY != 0U)
    {
        // Wait for synchronization
    }
}

void SERCOM0_I2CS_SetOperatingMode(void)
{
    SERCOM0_REGS->I2CS.SERCOM_CTRLA = SERCOM_I2CS_CTRLA_MODE(CLIENT_MODE);
    while (SERCOM0_REGS->I2CS.SERCOM_SYNCBUSY != 0U)
    {
        // Wait for synchronization
    }
}

void SERCOM0_I2CS_Set7bitAddress(uint8_t addr)
{
    SERCOM0_REGS->I2CS.SERCOM_ADDR = (SERCOM0_REGS->I2CS.SERCOM_ADDR & ~SERCOM_I2CS_ADDR_SEVENBIT_ADDR_Msk) | SERCOM_I2CS_ADDR_SEVENBIT_ADDR(addr);
}

void SERCOM0_I2CS_Set7bitAddressMask(uint8_t addr_mask)
{
    SERCOM0_REGS->I2CS.SERCOM_ADDR = (SERCOM0_REGS->I2CS.SERCOM_ADDR & ~SERCOM_I2CS_ADDR_SEVENBIT_ADDRMASK_Msk) | SERCOM_I2CS_ADDR_SEVENBIT_ADDRMASK(addr_mask);
}

void SERCOM0_I2CS_SetGeneralCall(bool value)
{
    if (value)
    {
        SERCOM0_REGS->I2CS.SERCOM_ADDR |= SERCOM_I2CS_ADDR_GENCEN_Msk;
    }
    else
    {
        SERCOM0_REGS->I2CS.SERCOM_ADDR &= ~SERCOM_I2CS_ADDR_GENCEN_Msk;
    }
}

uint8_t SERCOM0_I2CS_ReceiveData(void)
{
    while ((SERCOM0_REGS->I2CS.SERCOM_SYNCBUSY) != 0U)
    {
        /* Do nothing */
    }
    return (uint8_t) SERCOM0_REGS->I2CS.SERCOM_DATA;
}

void SERCOM0_I2CS_SendData(uint8_t data)
{
    SERCOM0_REGS->I2CS.SERCOM_DATA = data;
    while ((SERCOM0_REGS->I2CS.SERCOM_SYNCBUSY) != 0U)
    {
        /* Do nothing */
    }
}

uint32_t SERCOM0_I2C_GetError(void)
{
    uint32_t error;
    error = ((uint32_t) SERCOM0_REGS->I2CS.SERCOM_STATUS & I2C_CLIENT_ERROR_ALL);

    SERCOM0_REGS->I2CS.SERCOM_STATUS = (uint16_t) I2C_CLIENT_ERROR_ALL;

    return error;
}

I2C_CLIENT_DIR SERCOM0_I2CS_GetTransferDirection(void)
{
    if (SERCOM0_REGS->I2CS.SERCOM_STATUS & SERCOM_I2CS_STATUS_DIR_Msk)
    {
        return I2C_CLIENT_DIR_READ;
    }else
    {
        return I2C_CLIENT_DIR_WRITE;
    }
}

I2C_CLIENT_ACK_STATUS SERCOM0_I2CS_GetLastByteAckStatus(void)
{
    if (SERCOM0_REGS->I2CS.SERCOM_STATUS & SERCOM_I2CS_STATUS_RXNACK_Msk)
    {
        return I2C_CLIENT_NACK_RECEIVED;
    }
    else
    {
        return I2C_CLIENT_ACK_RECEIVED;
    }
}

void SERCOM0_I2CS_SetCommand(I2C_CLIENT_COMMAND command)
{
    if(command == I2C_CLIENT_COMMAND_SEND_ACK)
    {
        SERCOM0_REGS->I2CS.SERCOM_CTRLB = (SERCOM0_REGS->I2CS.SERCOM_CTRLB | SERCOM_I2CS_CTRLB_CMD(0x03UL)) & (~SERCOM_I2CS_CTRLB_ACKACT_Msk);
    }
    else if(command == I2C_CLIENT_COMMAND_SEND_NAK)
    {
        SERCOM0_REGS->I2CS.SERCOM_CTRLB |= (SERCOM_I2CS_CTRLB_CMD(0x03UL) | SERCOM_I2CS_CTRLB_ACKACT_Msk);
    }
    else if(command == I2C_CLIENT_COMMAND_RECEIVE_ACK_NAK)
    {
        SERCOM0_REGS->I2CS.SERCOM_CTRLB = (SERCOM0_REGS->I2CS.SERCOM_CTRLB | SERCOM_I2CS_CTRLB_CMD(0x03UL));
    }else if(command == I2C_CLIENT_COMMAND_WAIT_FOR_START)
    {
        SERCOM0_REGS->I2CS.SERCOM_CTRLB = (SERCOM0_REGS->I2CS.SERCOM_CTRLB & ~SERCOM_I2CS_CTRLB_CMD_Msk) | SERCOM_I2CS_CTRLB_CMD(0x02UL);
    }
    else
    {
        /* Do nothing, return */
    }
}

I2C_CLIENT_TRANSFER_EVENT SERCOM0_I2CS_GetBusStatus(void)
{
    uint8_t interrupt_flag = SERCOM0_REGS->I2CS.SERCOM_INTFLAG;

    if (interrupt_flag & SERCOM_I2CS_INTFLAG_AMATCH_Msk)
    {
        return I2C_CLIENT_TRANSFER_EVENT_ADDR_MATCH;
    }
    else if (interrupt_flag & SERCOM_I2CS_INTFLAG_DRDY_Msk)
    {
        if (SERCOM0_I2CS_GetTransferDirection() == I2C_CLIENT_DIR_WRITE)
        {
            return I2C_CLIENT_TRANSFER_EVENT_RX_READY;
        }
        else
        {
            return I2C_CLIENT_TRANSFER_EVENT_TX_READY;
        }
    }
    else if (interrupt_flag & SERCOM_I2CS_INTFLAG_PREC_Msk)
    {
        return I2C_CLIENT_TRANSFER_EVENT_STOP_BIT_RECEIVED;
    }
    else if (interrupt_flag & SERCOM_I2CS_INTFLAG_ERROR_Msk)
    {
        return I2C_CLIENT_TRANSFER_EVENT_ERROR;
    }
    else
    {
        return I2C_CLIENT_TRANSFER_EVENT_NONE;
    }
}

void SERCOM0_I2CS_EnableInterrupts(I2C_CLIENT_INTERRUPT interrupts)
{
    SERCOM0_REGS->I2CS.SERCOM_INTENSET = interrupts;
}

void SERCOM0_I2CS_DisableInterrupts(I2C_CLIENT_INTERRUPT interrupts) 
{
    SERCOM0_REGS->I2CS.SERCOM_INTENCLR = interrupts;
}

void SERCOM0_I2CS_ClearInterruptFlags(I2C_CLIENT_INTFLAG interrupt_flags)
{
    SERCOM0_REGS->I2CS.SERCOM_INTFLAG = (SERCOM0_REGS->I2CS.SERCOM_INTFLAG & ~interrupt_flags) | interrupt_flags;
}

void SERCOM0_I2CS_SetCallbackHandler(SERCOM_I2C_CALLBACK_HANDLER callback)
{
    sercom0_i2cs_callback_handler = callback;
}

static void SERCOM0_I2CS_InterruptHandler(void)
{
    if (sercom0_i2cs_callback_handler != NULL)
    {
        sercom0_i2cs_callback_handler();
    }
}

void SERCOM0_I2CS_SetInterruptHandler(void)
{
    SERCOM0_InterruptHandler = SERCOM0_I2CS_InterruptHandler;
}