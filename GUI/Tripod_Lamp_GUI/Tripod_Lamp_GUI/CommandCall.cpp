#include "CommandCall.h"

CommandCall::CommandCall(CommandLine *getCmd)
{
	cmd = getCmd;
}

CommandCall::~CommandCall() { }

bool CommandCall::isFree() { return !this->isRunning(); }

void CommandCall::listenAndSendCommands()
{
	start();
}

void CommandCall::run()
{
	cmd->listenAndSendCommands();
}