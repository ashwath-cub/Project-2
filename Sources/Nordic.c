/*
 * Nordic.c
 *
 *  Created on: 09-Nov-2016
 *      Author: Ashwath
 */
#include "Nordic.h"
#include "SPI.h"
#include "stdint.h"
uint8_t nrf_read_register(uint8_t regName)
{
	regName|=NORDIC_R_REGISTER;

	return (spi_trf(regName));
}

uint8_t nrf_write_register(uint8_t regName, uint8_t data)
{
	/*Configure the register for a write*/
	regName|=NORDIC_W_REGISTER;
	spi_trf(regName);
	/*Write to the register and read the status*/
	return(spi_trf(data));
}

void nrf_set_TXaddress(uint8_t* addr_ptr)
{
	uint8_t index;
	nrf_write_register(NORDIC_TX_ADDRESS, *addr_ptr);
	for(index=1; index<5; index++)
		spi_trf(*(addr_ptr+index));
}


