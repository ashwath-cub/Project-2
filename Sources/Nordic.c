/*
 * Nordic.c
 *
 *  Created on: 09-Nov-2016
 *      Author: Ashwath
 */
#include "nordic.h"

uint8_t nrf_read_register(uint8_t regName)
{
	regName|=R_REGISTER;

	return (spi_trf(regName));
}

uint8_t nrf_write_register(uint8_t regName, uint8_t data)
{
	/*Configure the register for a write*/
	regName|=W_REGISTER;
	spi_trf(regName);
	/*Write to the register and read the status*/
	return(spi_trf(data));
}





