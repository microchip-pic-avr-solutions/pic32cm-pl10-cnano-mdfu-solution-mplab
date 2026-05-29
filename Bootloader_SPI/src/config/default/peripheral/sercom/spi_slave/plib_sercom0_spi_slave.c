/*******************************************************************************
  SERIAL COMMUNICATION SERIAL PERIPHERAL INTERFACE(SERCOM0_SPI) PLIB

  Company
    Microchip Technology Inc.

  File Name
    plib_sercom0_spi_slave.c

  Summary
    SERCOM0_SPI PLIB Slave Implementation File.

  Description
    This file defines the interface to the SERCOM SPI Slave peripheral library.
    This library provides access to and control of the associated
    peripheral instance.

  Remarks:
    None.

*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2020 Microchip Technology Inc. and its subsidiaries.
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
// DOM-IGNORE-END


#include "interrupts.h"
#include "plib_sercom0_spi_slave.h"
#include "peripheral/port/plib_port.h"
#include <string.h>

// *****************************************************************************
// *****************************************************************************
// Section: MACROS Definitions
// *****************************************************************************
// *****************************************************************************
#define SERCOM0_SPI_READ_BUFFER_SIZE            256U
#define SERCOM0_SPI_WRITE_BUFFER_SIZE           256U

static volatile uint8_t SERCOM0_SPI_ReadBuffer[SERCOM0_SPI_READ_BUFFER_SIZE];
static volatile uint8_t SERCOM0_SPI_WriteBuffer[SERCOM0_SPI_WRITE_BUFFER_SIZE];


/* Global object to save SPI Exchange related data  */
static volatile SPI_SLAVE_OBJECT sercom0SPISObj;

// *****************************************************************************
// *****************************************************************************
// Section: SERCOM0_SPI Slave Implementation
// *****************************************************************************
// *****************************************************************************
// *****************************************************************************

static void mem_copy(volatile void* pDst, volatile void* pSrc, uint32_t nBytes)
{
    volatile uint8_t* pSource = (volatile uint8_t*)pSrc;
    volatile uint8_t* pDest = (volatile uint8_t*)pDst;

    for (uint32_t i = 0U; i < nBytes; i++)
    {
        pDest[i] = pSource[i];
    }
}

void SERCOM0_SPI_Initialize(void)
{
    /* CHSIZE - 8_BIT
     * PLOADEN - 1
     *  SSDE - 1 
     * RXEN - 1
     */
    SERCOM0_REGS->SPI.SERCOM_CTRLB = SERCOM_SPI_CTRLB_CHSIZE_8_BIT | SERCOM_SPI_CTRLB_PLOADEN_Msk | SERCOM_SPI_CTRLB_RXEN_Msk | SERCOM_SPI_CTRLB_SSDE_Msk;

    /* Wait for synchronization */
    while(SERCOM0_REGS->SPI.SERCOM_SYNCBUSY != 0U)
    {
        /* Do nothing */
    }

    /* Mode - SPI Slave
     * IBON - 1 (Set immediately upon buffer overflow)
     * DOPO - MUX2 (MISO on PAD3/PA07)
     * DIPO - MUX0 (MOSI on PAD0/PA04)
     * CPHA - LEADING_EDGE
     * COPL - IDLE_LOW
     * DORD - MSB
     * ENABLE - 1
     */
    SERCOM0_REGS->SPI.SERCOM_CTRLA = SERCOM_SPI_CTRLA_MODE_SPI_SLAVE |
            SERCOM_SPI_CTRLA_IBON_Msk |
            SERCOM_SPI_CTRLA_DOPO_MUX2 |
            SERCOM_SPI_CTRLA_DIPO_MUX0 |
            SERCOM_SPI_CTRLA_CPOL_IDLE_LOW |
            SERCOM_SPI_CTRLA_CPHA_LEADING_EDGE |
            SERCOM_SPI_CTRLA_DORD_MSB ;
            //| SERCOM_SPI_CTRLA_ENABLE_Msk ;

    /* Wait for synchronization */
    while(SERCOM0_REGS->SPI.SERCOM_SYNCBUSY != 0U)
    {
        /* Do nothing */
    }
}

bool SERCOM0_Open(void)
{
    bool enabled = false;
    SERCOM0_REGS->SPI.SERCOM_CTRLA |= SERCOM_SPI_CTRLA_ENABLE_Msk;
     // Wait for synchronization
    while (SERCOM0_REGS->SPI.SERCOM_SYNCBUSY != 0U)
    {
        // Do nothing
    }
    enabled = true;
    
    return enabled;
}

// Read a byte from SPI (blocking until RX is ready)
uint8_t SERCOM0_ByteRead(void)
{
    while ((SERCOM0_REGS->SPI.SERCOM_INTFLAG & SERCOM_SPI_INTFLAG_RXC_Msk) == 0U)
    {
        // Wait for RX ready
    }
    return SERCOM0_REGS->SPI.SERCOM_DATA;
}

// Write a byte to SPI (blocking until TX data register is empty)
void SERCOM0_ByteWrite(uint8_t data)
{
    while ((SERCOM0_REGS->SPI.SERCOM_INTFLAG & SERCOM_SPI_INTFLAG_DRE_Msk) == 0U)
    {
        // Wait for TX register empty
    }
    SERCOM0_REGS->SPI.SERCOM_DATA = data;
}

// Returns 1 if TX is busy (data register not empty), 0 if ready
uint8_t SERCOM0_IsTxReady(void)
{
    return ((SERCOM0_REGS->SPI.SERCOM_INTFLAG & SERCOM_SPI_INTFLAG_DRE_Msk) == 0U) ? 1 : 0;
}

// Returns 1 if RX has data available, 0 if not
uint8_t SERCOM0_IsRxReady(void)
{
    return ((SERCOM0_REGS->SPI.SERCOM_INTFLAG & SERCOM_SPI_INTFLAG_RXC_Msk) != 0U) ? 1 : 0;
}

/* For 9-bit mode, the "size" must be specified in terms of 16-bit words */
size_t SERCOM0_SPI_Read(void* pRdBuffer, size_t size)
{
    uint8_t intState = SERCOM0_REGS->SPI.SERCOM_INTENSET;
    size_t rdSize = size;
    uint8_t* pDstBuffer = (uint8_t*)pRdBuffer;

    SERCOM0_REGS->SPI.SERCOM_INTENCLR = intState;

    if (rdSize > sercom0SPISObj.rdInIndex)
    {
        rdSize = sercom0SPISObj.rdInIndex;
    }

    (void) mem_copy(pDstBuffer, SERCOM0_SPI_ReadBuffer, rdSize);

    SERCOM0_REGS->SPI.SERCOM_INTENSET = intState;

    return rdSize;
}

/* For 9-bit mode, the "size" must be specified in terms of 16-bit words */
size_t SERCOM0_SPI_Write(void* pWrBuffer, size_t size )
{
    uint8_t intState = SERCOM0_REGS->SPI.SERCOM_INTENSET;
    size_t wrSize = size;
    bool writeReady = false;
    uint32_t wrOutIndex = 0;
    uint8_t* pSrcBuffer = (uint8_t*)pWrBuffer;

    SERCOM0_REGS->SPI.SERCOM_INTENCLR = intState;

    if (wrSize > SERCOM0_SPI_WRITE_BUFFER_SIZE)
    {
        wrSize = SERCOM0_SPI_WRITE_BUFFER_SIZE;
    }

   (void) mem_copy(SERCOM0_SPI_WriteBuffer, pSrcBuffer, wrSize);

    sercom0SPISObj.nWrBytes = wrSize;

    writeReady = (wrOutIndex < sercom0SPISObj.nWrBytes);
    writeReady = ((SERCOM0_REGS->SPI.SERCOM_INTFLAG & SERCOM_SPI_INTFLAG_DRE_Msk) == SERCOM_SPI_INTFLAG_DRE_Msk) && writeReady;
    while (writeReady)
    {
        SERCOM0_REGS->SPI.SERCOM_DATA = SERCOM0_SPI_WriteBuffer[wrOutIndex];
        wrOutIndex++;
        writeReady = (wrOutIndex < sercom0SPISObj.nWrBytes);
        writeReady = ((SERCOM0_REGS->SPI.SERCOM_INTFLAG & SERCOM_SPI_INTFLAG_DRE_Msk) == SERCOM_SPI_INTFLAG_DRE_Msk) && writeReady;
    }

    sercom0SPISObj.wrOutIndex = wrOutIndex;

    /* Restore interrupt enable state and also enable DRE interrupt to start pre-loading of DATA register */
    SERCOM0_REGS->SPI.SERCOM_INTENSET = (intState | (uint8_t)SERCOM_SPI_INTENSET_DRE_Msk);

    return wrSize;
}

/* For 9-bit mode, the return value is in terms of 16-bit words */
size_t SERCOM0_SPI_ReadCountGet(void)
{
    return sercom0SPISObj.rdInIndex;
}

/* For 9-bit mode, the return value is in terms of 16-bit words */
size_t SERCOM0_SPI_ReadBufferSizeGet(void)
{
    return SERCOM0_SPI_READ_BUFFER_SIZE;
}

/* For 9-bit mode, the return value is in terms of 16-bit words */
size_t SERCOM0_SPI_WriteBufferSizeGet(void)
{
    return SERCOM0_SPI_WRITE_BUFFER_SIZE;
}

void SERCOM0_SPI_CallbackRegister(SERCOM_SPI_SLAVE_CALLBACK callBack, uintptr_t context )
{
    sercom0SPISObj.callback = callBack;

    sercom0SPISObj.context = context;
}

/* The status is returned busy during the period the chip-select remains asserted */
bool SERCOM0_SPI_IsBusy(void)
{
    return sercom0SPISObj.transferIsBusy;
}

/* Drive the GPIO pin to indicate to SPI Master that the slave is ready now */
void SERCOM0_SPI_Ready(void)
{
    PORT_SetOutput(PORT_PIN_PA00, 0U);
}