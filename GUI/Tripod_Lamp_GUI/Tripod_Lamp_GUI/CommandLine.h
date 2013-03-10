#ifndef COMMANDLINE_H
#define COMMANDLINE_H

#include <vector>
#include <QObject>
#include <iostream>
#include "UartControl.h"
#include "CommandDefs.h"

using namespace std;

class CommandLine : public QObject
{
	Q_OBJECT

private:
	UartControl	*uct;
	vector<pair<char, char> *> *uartCmds;
	unsigned int *bufferWritePointer;
	unsigned int  bufferReadPointer;

public:
	CommandLine(vector<pair<char, char> *> *getUartCmds, unsigned int *getBufferWritePointer);
	~CommandLine();

	void listenAndSendCommands();
		
public slots:
	void Connect(int port, int baud);
	void Disconnect();

signals:
	void connectionSuccess();
	void connectionFailed();
	void disconnected();

	void printDebug(QString);
	void giveReadPointer(unsigned int);
};

#endif // COMMANDLINE_H