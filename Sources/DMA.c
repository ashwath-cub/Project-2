/*
 * DMA.c
 *
 *  Created on: 07-Nov-2016
 *      Author: Ashwath
 */
/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "MKL25Z4.h"
//#include "codeprofiler.h"
//#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include "mcg.h"
#include "dma.h"

//__enable_irq();

//#define buffer		5000
uint32_t count;
void print_character(int c)
{
	while(!(UART0->S1 & 0xC0));
	UART0->D = c;
}

void start_timer()
{
	// PLL clock select
	SIM_SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;
	SIM_SOPT2 &= ~(SIM_SOPT2_TPMSRC_MASK);

	// Select MCGPLLCLK/2
	SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1);

	// Enable TPM clock
	SIM_SCGC6 |= SIM_SCGC6_TPM0_MASK;

	//Nullify the control registers to ensure counter is not running

	TPM0_SC = 0;
	TPM0_CONF = 0;

	//Set prescalar to 1 when counter is disabled
	TPM0_SC = TPM_SC_PS(0);

	// Setting modulo value to set 10us as the execution timer
	TPM0_MOD = 480;


	//Enable the TPM Counter
	TPM0_SC |= TPM_SC_CMOD(1);

	//NVIC_ClearPendingIRQ(TPM0_IRQn);
	__enable_irq();
	NVIC_EnableIRQ(TPM0_IRQn);
	//Enable Interrupts for the Timer Overflow
	TPM0_SC |= TPM_SC_TOIE_MASK;

}

uint32_t stop_timer()
{
	uint32_t local_count=count;
	TPM0_SC&=TPM_SC_TOIE(0);
	return local_count;
}

void TPM0_IRQHandler()
{
	count++;//incrementing counter to note the number of overflows
	TPM0_SC |= TPM_SC_TOF_MASK;//clearing the overflow mask
	//TPM0_SC |= TPM_SC_TOIE_MASK;//enabling the interrupt again
}


void DMA_setup(char *source, char* destination)
{
	SIM_SCGC6 |=0x2;
	SIM_SCGC7 |=0x100;

	DMAMUX0_CHCFG0 |=0x80;

	DMA_SAR0=source;
	DMA_DAR0=destination;

	DMA_DSR_BCR0  |= DMA_DSR_BCR_BCR(5000);

	DMA_DCR0 |= (DMA_DCR_SSIZE(1) | DMA_DCR_DSIZE(1));
	DMA_DCR0 |= (DMA_DCR_SINC(1) | DMA_DCR_DINC(1));
	//NVIC_EnableIRQ(DMA0_IRQn);
	//DMA_DCR0 |= DMA_DCR_EINT(1);
}
void start_dma()
{
	DMA_DCR0 |= DMA_DCR_START(1);
	return;
}
void while_dma_over_wait(){
    while(!(DMA_DSR_BCR0 & DMA_DSR_BCR_DONE_MASK));
    return;
}
