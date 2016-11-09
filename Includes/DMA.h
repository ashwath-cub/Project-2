/*
 * dma.h
 *
 *  Created on: 07-Nov-2016
 *      Author: Ashwath
 */
#ifndef INCLUDES_DMA_H_
#define INCLUDES_DMA_H_

void uart_init();

void print_character(int c);

void start_timer();

uint32_t stop_timer();

void DMA_setup(char* source, char* destination);

void start_dma();

void while_dma_over_wait();
#endif /* INCLUDES_DMA_H_ */
