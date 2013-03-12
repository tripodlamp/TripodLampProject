#include "UART.h"

uint8_t RxQueue[RX_QUEUE_SIZE];
uint8_t RxQueueWrite, RxQueueRead;


void uartInit(void)
{
	UBRRH = UBRR_VAL >> 8;
    UBRRL = UBRR_VAL & 0xFF;
	
	UCSRC = (1<<URSEL) | (1<<UCSZ1) | (1<<UCSZ0);	// Asynchron 8N1 
    UCSRB|= (1<<RXEN ) | (1<<TXEN);					// Enable UART Rx & Tx
	UCSRB|= (1<<RXCIE);								// Enable UART Rx Interrupt
	
	RxQueueWrite = 0;
	RxQueueRead  = 0;
}

void uartSendByte(uint8_t byte)
{
	while(bit_is_clear(UCSRA, UDRE));	// Warten auf Datenregister empty	
	UDR = byte;
}

uint8_t	uartDataAvail()
{
	if(RxQueueWrite<RxQueueRead)
		return (RX_QUEUE_SIZE+RxQueueWrite-RxQueueRead);
	else
		return RxQueueWrite-RxQueueRead;
}

uint8_t	uartGetByte()
{
	uint8_t ret = RxQueue[RxQueueRead];
	if(++RxQueueRead==RX_QUEUE_SIZE) { RxQueueRead = 0; }
	return ret;		
}

ISR(USART_RXC_vect)
{
	RxQueue[RxQueueWrite] = UDR;
	if(++RxQueueWrite==RX_QUEUE_SIZE) { RxQueueWrite = 0; }
}