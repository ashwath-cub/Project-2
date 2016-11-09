/*
 * command.h
 *
 *  Created on: 03-Nov-2016
 *      Author: Ashwath
 */
#ifndef command_h
#define command_h

#include<stdint.h>

#define MAX_DATA_SIZE 5

typedef enum Cmd_e
{
	LED_Config
} Cmds;

typedef enum payload_e{
LED_RED , // Provides a temperature Reading
LED_BLUE , // Sets speed for a motor Controller
LED_GREEN, // Configures the LEDs to some color
LED_DANCE // Sets Low Power Mode // More command IDs here
} payload;

typedef struct CI_Msg_t{
Cmds command; // Command operation
uint8_t length; // Size of message
uint8_t data[MAX_DATA_SIZE]; // Generic data payload
uint16_t checksum; // Error detection checksum
}CI_Msg;

void uart_init();
void structure_init(CI_Msg *msg);
void Decode_CI_Msg(CI_Msg *msg);
void Set_red_LED();
void Set_blue_LED();
void Set_green_LED();

#endif
