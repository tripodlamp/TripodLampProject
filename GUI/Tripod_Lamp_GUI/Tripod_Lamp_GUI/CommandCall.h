#ifndef COMMANDCALL_H
#define COMMANDCALL_H

#include <QTime>
#include <QThread>
#include "CommandLine.h"
#include "SequenceStep.h"

class CommandCall : public QThread
{
	Q_OBJECT

public:
	CommandCall(CommandLine *getCmd);
	~CommandCall();

	bool isFree();
	void listenAndSendCommands();
	
private:
	CommandLine *cmd;

protected:
	void run();
};

using namespace std;

#endif // COMMANDCALL_H
