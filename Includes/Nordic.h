/*
 * nordic.h
 *
 *  Created on: 09-Nov-2016
 *      Author: Ashwath
 */

#ifndef INCLUDES_NORDIC_H_
#define INCLUDES_NORDIC_H_
#include<stdint.h>

/*Defining some commonly used commands*/
#define NORDIC_R_REGISTER 						   0b00000000
#define NORDIC_W_REGISTER 						   0b00100000
#define NORDIC_R_RX_PAYLOAD						   0b01100001			//Read RX-payload. 1-32 Bytes first
#define NORDIC_T_TX_PAYLOAD						   0b10100000			//Read TX-payload. 1-32 Bytes first
#define NORDIC_FLUSH_TX							   0b11100001			//Flush TX FIFO, used in TX mode
#define NORDIC_FLUSH_RX							   0b11100010			//Flush RX FIFO, used in RX mode
#define NORDIC_NOP								   0b11111111			//NOP-does nothing. Can be used to read the status register

/*Defining the address corresponding to some commonly used registers in the Nordic chip*/
#define NORDIC_CONFIG 				   			   (0x00) 						//Configuration Register
#define NORDIC_TX_ADDRESS 			   			   (0x10)						//Sets TX Address
#define NORDIC_RF_SETUP 			   		       (0x06)						//RF Setup Register
#define NORDIC_STATUS 				   			   (0x07) 						//Status Register
#define NORDIC_FIFO_STATUS             			   (0x17)						//FIFO Status Register

/*Defining some Bit masks associated with the CONFIG register*/
#define NORDIC_CONFIG_POWER_UP_MASK    			   (0x02)						//1:Power up; 0: Power Down
#define NORDIC_CONFIG_RX_DR_MASK       			   (0x40)						//Mask interrupt caused by RX_DR. 1: Interrupt not reflected
#define NORDIC_CONFIG_TX_DS_MASK	   			   (0x20)						//Mask interrupt caused by TX_DS. 1: Interrupt not reflected
#define NORDIC_CONFIG_EN_CRC_MASK	   			   (0x08)						//Enable CRC
#define NORDIC_CONFIG_CRCO_MASK		   		       (0x04)						//CRC coding scheme. '0'-1 Bytes, '1'-2 Bytes

/*Defining some Bit masks associated with the STATUS register*/
#define NORDIC_STATUS_RX_DR_MASK				   (0x40)						//Data ready RX FIFO Interrupt
#define NORDIC_STATUS_TX_DS_MASK				   (0x20)						//Data sent TX FIFO Interrupt
#define NORDIC_STATUS_MAX_RT_MASK				   (0x10)						//Max number of TX retransmits Interrupt
#define NORDIC_STATUS_TX_FULL_MASK				   (0x01)						//TX FIFO Full flag

/*Defining some Bit masks associated with the FIFO Status register*/
#define NORDIC_FIFO_TX_REUSE_MASK				   (0x40)						//Used for a PTX device
#define NORDIC_FIFO_TX_FULL_MASK				   (0x20)						//TX FIFO Full Flag
#define NORDIC_FIFO_TX_EMPTY_MASK                  (0x10)						//TX FIFO Empty Flag
#define NORDIC_FIFO_RX_FULL_MASK				   (0x02)						//RX FIFO Full Flag
#define NORDIC_FIFO_RX_EMPTY_MASK				   (0x01)						//RX FIFO Empty Flag

/*Defining some Bit masks associated with RF Setup register*/
#define NORDIC_RF_CONT_WAVE_MASK				   (0x80)						//Enables continuous carrier transmit when high
#define NORDIC_RF_RF_DR_LOW_MASK                   (0x20)						//Set RF Data Rate to 256kbps
#define NORDIC_RF_PLL_LOCK_MASK				   	   (0x10)						//Force PLL Lock signal. Used only in test
#define NORDIC_RF_DR_HIGH_MASK					   (0x08)						//Helps select between high speed data rates
#define NORDIC_RF_PWR_MASK						   ((uint8_t)((uint8_t)x<<1))	//Set RF output power in TX mode

uint8_t nrf_config();

/*Returns value stored in the Nordic chip's register*/
uint8_t nrf_read_register(uint8_t regName);

/*Writes data to the register specified*/
uint8_t nrf_write_register(uint8_t reg_name,  uint8_t data);

void nrf_set_TXaddress(uint8_t* addr_ptr);


#endif /* INCLUDES_NORDIC_H_ */
