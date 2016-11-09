/*
 * message.c
 *
 *  Created on: 08-Nov-2016
 *      Author: Ashwath
 */
#include "MKL25Z4.h"
#include<stdio.h>
#include <math.h>
#include <string.h>
#include "message_struct.h"



volatile int flag=0;
volatile uint8_t array[10];

volatile int counter=0;
CI_Msg msg;
//int Bright=500;


void uart_init()
{
	uint16_t baud_divisor;

    __disable_irq();
	//Sets gate clock  for PORTA
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;

	//Enables clock for UART0; source as MCGCLKFLL
	SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;
	SIM_SOPT2 |= SIM_SOPT2_UART0SRC(1);

	// Sets for UART0 mode
	PORTA_PCR1 = PORT_PCR_MUX(2);
	PORTA_PCR2 = PORT_PCR_MUX(2);

	// Disables tx and rx before editing registers
	UART0_C2=0x00;
	UART0_C1=0x00;

    /* Calculate baud_divisor for sbr register and set baud rate */
	//baud_divisor= (uint16_t)(DEFAULT_SYSTEM_CLOCK/(baudRate*16));
	UART0_BDH |= 0x00;//(baud_divisor >> 8) & UART0_BDH_SBR_MASK;
	UART0_BDL |= 0x17;//(baud_divisor & UART0_BDL_SBR_MASK);


	//UART_C2_REG(UART0_BASE_PTR) |= UART_C2_TIE_MASK;//Setup receiver interrupt
	UART_C2_REG(UART0_BASE_PTR) |= UART_C2_RIE_MASK;
	UART_C2_REG(UART0_BASE_PTR) |=  UART_C2_RE_MASK ;

	__enable_irq();

	//Enabling NVIC and CPU interrupts
	NVIC_EnableIRQ(UART0_IRQn);
	//Switch on transmitter and receiver
}

void structure_init(CI_Msg *msg1){

	msg1->command=array[0];
	msg1->length = array[1];
	msg1->data[0] = array[2];
	msg1->checksum =array[3];
	Decode_CI_Msg(&msg);
	counter=0;
	UART_C2_REG(UART0_BASE_PTR) |= UART_C2_RIE_MASK;
}
void Decode_CI_Msg(CI_Msg * msg1)
{
	switch(msg1->data[0]-48)
	{
	case LED_RED: Set_red_LED();
		break;
	case LED_BLUE:Set_blue_LED();
		break;
	case LED_GREEN:Set_green_LED();
		break;
	//case LED_DANCE:Set_LED_config();
	//	break;
	}
}
void Set_red_LED()
{
	 	    TPM2_BASE_PTR->CONTROLS[1].CnV = 0;
	 	    TPM0_BASE_PTR->CONTROLS[1].CnV = 0;
	 	    //TPM2_BASE_PTR->CONTROLS[0].CnV = Bright;
}


void Set_blue_LED()
{

			TPM2_BASE_PTR->CONTROLS[1].CnV = 0;
			TPM2_BASE_PTR->CONTROLS[0].CnV = 0;
			//TPM0_BASE_PTR->CONTROLS[1].CnV = Bright;
}

void Set_green_LED()
{
				//TPM2_BASE_PTR->CONTROLS[1].CnV = Bright;
			 	TPM2_BASE_PTR->CONTROLS[0].CnV = 0;
			 	TPM0_BASE_PTR->CONTROLS[1].CnV = 0;
}

void UART0_IRQHandler()
{
	__disable_irq();
	uint8_t status;
	char received;
	status = UART0_S1;

	if(status & UART_S1_RDRF_MASK)
	{
		received= UART0_D;
		if(received!='\r')
		{
			*(array+counter)= received;
			counter++;
		}
		else
		{
			UART_C2_REG(UART0_BASE_PTR) &= ~(UART_C2_RIE_MASK);
			flag=1;
		}
	}

	__enable_irq();
}
/*
void main()
{
	uart_init();
	while(1)
	{
		if(flag==1)
		{
			structure_init(&msg);
			flag=0;
		}
	}
	return;
}
*/
