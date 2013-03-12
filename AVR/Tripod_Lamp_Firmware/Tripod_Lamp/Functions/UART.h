#ifndef UART_H_
#define UART_H_

#include "../Defs.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdbool.h>
#include <util/delay.h>

#define UBRR_VAL	((F_CPU+BAUD*8)/(BAUD*16)-1)	// calculate value for UART rate register


void	uartInit();
void	uartSendByte(uint8_t byte);
uint8_t	uartDataAvail();
uint8_t	uartGetByte();

#endif /* UART_H_ */