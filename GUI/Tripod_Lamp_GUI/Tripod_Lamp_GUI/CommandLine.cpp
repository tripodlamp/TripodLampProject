#include "CommandLine.h"

CommandLine::CommandLine(vector<pair<char, char> *> *getUartCmds, unsigned int *getBufferWritePointer)
{
	uct				   = new UartControl();
	uartCmds		   = getUartCmds;
	bufferWritePointer = getBufferWritePointer;
	bufferReadPointer  = 0;
}

CommandLine::~CommandLine()
{
	delete(uct); uct = NULL;
}

void CommandLine::listenAndSendCommands()
{
	printDebug("CMD: Start listing...");
	while(1)
	{
		if((*bufferWritePointer)!=bufferReadPointer)
		{
//			printDebug("CMD: Sending data: 0x"+QString::number(uartCmds->at(bufferReadPointer)->first , 16).rightJustified(2, '0').right(2)+
//											   QString::number(uartCmds->at(bufferReadPointer)->second, 16).rightJustified(2, '0').right(2)+
//											   "; read pointer: "+QString::number(bufferReadPointer));
			uct->sendCommand(uartCmds->at(bufferReadPointer)->first, uartCmds->at(bufferReadPointer)->second);
			bufferReadPointer = (bufferReadPointer+1)%UART_CMD_BUFFER_SIZE;
			giveReadPointer(bufferReadPointer);
//			printDebug("CMD: Data sent, new read pointer: "+QString::number(bufferReadPointer));
		}
	}
	// this method should never reach this point
	printDebug("CMD: Stop listing... (should not be possible)");
}

void CommandLine::Connect(int port, int baud)
{
	if(uct->Connect(port, baud))
		connectionSuccess();
	else
		connectionFailed();
}

void CommandLine::Disconnect()
{
	uct->Disconnect();
	disconnected();
}

