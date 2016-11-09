/*
 * nordic.h
 *
 *  Created on: 09-Nov-2016
 *      Author: Ashwath
 */

#ifndef INCLUDES_NORDIC_H_
#define INCLUDES_NORDIC_H_
#include<stdint.h>

#define NORDIC_POWER_UP_MASK 		(0x02)
#define NORDIC_STATUS_RX_DR_MASK    (0x40)
#define NORDIC_STATUS_TX_DS_MASK	(0x20)

#define R_REGISTER 0b0000 0000
#define W_REGISTER 0b0010 0000
/*Defining the address corresponding to some commonly used registers in the Nordic chip*/

#define CONFIG 				   0x00 				//Configuration Register
#define RF_CH 				   0x05					//RF Channel
#define RF_SETUP 			   0x06					//RF Setup Register
#define STATUS 				   0x07 				//Status Register



uint8_t nrf_config();

/*Returns value stored in the Nordic chip's register*/
uint8_t nrf_read_register(uint8_t regName);

/*Writes data to the register specified*/
uint8_t nrf_write_register(uint8_t reg_name,  uint8_t data);

uint8_t nrf_transmit_data(//);

uint8_t nrf_flush_tx_fifo();

uint8_t nrf_set_tx_address();

#endif /* INCLUDES_NORDIC_H_ */
