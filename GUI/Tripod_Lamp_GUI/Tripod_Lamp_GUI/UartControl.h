#ifndef UARTCONTROL_H
#define UARTCONTROL_H

#include "sio.h"

class UartControl
{
public:
	UartControl();
	~UartControl();

	bool Connect(int port, int baud);
	void Disconnect();

	void sendCommand(char command, char value);

private:
	CSio *uart;
};

#endif // UARTCONTROL_H