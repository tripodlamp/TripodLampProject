#ifndef COMMANDGEN_H
#define COMMANDGEN_H

#include <vector>
#include <QObject>
#include <QString>
#include "CommandDefs.h"
#include "SequenceStep.h"

/*
In here create Uart commands and write them into a send-out buffer.
Maybe something like vector<uart_command>.
This object is only allowed to insert data to the vector, but not to delete or clear it!!!! That is important!!!!
*/

using namespace std;

class CommandGen : public QObject
{
	Q_OBJECT

private:
	vector<pair<char,char> *> *uartCmds;
	unsigned int cmdWritePointer;

	void sendCommand(char cmd, char value);

public:
	CommandGen();
	virtual ~CommandGen();

	void setAllColors(char red, char green, char blue, bool sideCondition, char side);
	void setColor(char color, char colorValue, bool sideCondition, char side);
	void setWhite(			  char colorValue, bool sideCondition, char side);
	void setDefault();
	void setFade (bool on);
	void setLED	 (char color, char colorValue, char side, char branch);

	void doSequenceStep(SequenceStep *step);

	vector<pair<char, char> *> *getTransmitBuffer();
	unsigned int			   *getBufferWritePointer();


signals:
	void setColorStatus(char, char);			// All LEDs
	void setColorStatus(char, char, char);		// All LEDs on one side
	void setColorStatus(char, char, char, int);	// An LED on one side on one branch

	void printDebug(QString);
};


#endif // COMMANDGEN_H