/*
 * SPI.c
 *
 *  Created on: 09-Nov-2016
 *      Author: Ashwath
 */

#include "MKL25Z4.h"
#include<stdint.h>
void spi_init(void);
void spi_send(char spiMsg);


/*
int main(void)
{
  char ch;
  spi_init();   //Init SPI0

  while(1)
  {
	  ch = in_char();  //Read char from terminal
	  spi_send(ch);    //Send char over SPI
	  out_char(ch);    //Echo char to terminal
  }
  return 0;
}
*/

void spi_init(void)
{
  SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;      //Turn on clock to C module
  SIM_SCGC4 |= SIM_SCGC4_SPI0_MASK;       //Enable SPI0 clock
  GPIOC_PDDR=(1<<4);
  GPIOC_PSOR=(1<<4);
  PORTC_PCR4 = PORT_PCR_MUX(0x2);    //Set PTC0 to mux 2 [SPI0_PCS0]
  PORTC_PCR5 = PORT_PCR_MUX(0x2);    //Set PTC1 to mux 2 [SPI0_SCK]
  PORTC_PCR6 = PORT_PCR_MUX(0x2);    //Set PTC2 to mux 2 [SPI0_MOSI]
  PORTC_PCR7 = PORT_PCR_MUX(0x2);    //Set PTC3 to mux 2 [SPIO_MISO]

  SPI0_C1 |= SPI_C1_MSTR_MASK;   //Set SPI0 to Master Mode

  //Set baud rate prescale divisor to 5 & set baud rate divisor to 64 for baud rate of 15625 hz
  SPI0_BR = (SPI_BR_SPPR(0x02) | SPI_BR_SPR(0x01));
  SPI0_C1 |= SPI_C1_SPE_MASK;    //Enable SPI0

  /*The SS pin reverts to GPIO because the MODFEN bit hasn't been written to*/
}

uint8_t spi_send(char spiMsg)
{
  GPIOC_PCOR = (1<<4);     //Pull SS low so as to activate slave device

  //Wait for the module to write ready
  while(!(SPI_S_SPTEF_MASK & SPI0_S));
  SPI0_D = spiMsg;    //Write char to SPI
  while(!(SPI_S_SPTEF_MASK & SPI0_S));
  GPIOC_PSOR = (1<<4);	  //Pull SS high back again
  return SPI0_D;
}
