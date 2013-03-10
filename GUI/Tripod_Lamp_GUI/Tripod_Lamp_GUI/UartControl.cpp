#include "UartControl.h"

UartControl::UartControl()
{
	uart = new CSio();
}

UartControl::~UartControl()
{
	delete(uart); uart = NULL;
}

bool UartControl::Connect(int port, int baud)
{
	uart->SetComPort (port);
	uart->SetBaudRate(baud);

	return uart->Open();
}

void UartControl::Disconnect()
{
	uart->Close();
}

void UartControl::sendCommand(char command, char value)
{
	uart->Write(reinterpret_cast<const byte*>(&command), 1);
	uart->Write(reinterpret_cast<const byte*>(&value  ), 1);
}