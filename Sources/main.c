#include<stdio.h>
#include <math.h>
#include <string.h>
#include "message_struct.h"
#include "dma.h"
#include "MKL25Z4.h"
#include "mcg.h"
#include "SPI.h"

void main()
{
/*
	uint32_t counter;
	uint32_t x;
	double y;
	uint32_t index;
	char source[5000];
	char destination[5000];

	for(index=0; index<5000; index++)
		*(source+index)='A';

	DMA_setup(source, destination);
    //DMA_DCR0 |= DMA_DCR_EINT(1);
	pll_init(8000000, LOW_POWER, CRYSTAL,4,24,MCGOUT);
    start_timer();
    start_dma();
    while_dma_over_wait();
   	counter=stop_timer();
   	x = counter*480 + TPM0_CNT;
   	y = (x / 48000000.00);

    start_timer();
    my_memmove(source,destination, 5000);
   	counter=stop_timer();
   	x = counter*480 + TPM0_CNT;
   	y = (x / 48000000.00);

    //print_character(y);
	 Never leave main
*/
    char ch;
    spi_init();   //Init SPI0
    ch='A';
    while(1)
    {
  	    spi_send(ch);    //Send char over SPI
	}

    return;
}

/*
void DMA0_IRQHandler()
{
   	counter=stop_timer();
   	x = counter*480 + TPM0_CNT;
   	y = (x / 48000000.00);
}
*/
