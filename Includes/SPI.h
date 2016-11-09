/*
 * SPI.h
 *
 *  Created on: 09-Nov-2016
 *      Author: Ashwath
 */

#ifndef INCLUDES_SPI_H_
#define INCLUDES_SPI_H_
#include<stdint.h>

void spi_init(void);

uint8_t spi_trf(char spiMsg);


#endif /* INCLUDES_SPI_H_ */
