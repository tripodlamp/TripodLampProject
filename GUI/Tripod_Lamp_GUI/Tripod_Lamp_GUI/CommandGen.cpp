#include "CommandGen.h"

void CommandGen::sendCommand(char cmd, char value)
{
	uartCmds->at(cmdWritePointer)->first  = cmd;
	uartCmds->at(cmdWritePointer)->second = value;
	cmdWritePointer = (cmdWritePointer+1)%UART_CMD_BUFFER_SIZE;
//	printDebug("Added uartCommand to transmit buffer: 0x"+QString::number((unsigned int)cmd, 16).rightJustified(2, '0').right(2)+QString::number((unsigned int)value, 16).rightJustified(2, '0').right(2)+"; wrPointer: "+QString::number(cmdWritePointer));
}

CommandGen::CommandGen()
{
	uartCmds = new vector<pair<char,char> *>();
	// Preload transmit buffer
	for(unsigned int i=0;i<UART_CMD_BUFFER_SIZE;i++)
		uartCmds->push_back(new pair<char,char>(0x00, 0x00));

	cmdWritePointer = 0;
}

CommandGen::~CommandGen()
{
	delete(uartCmds); uartCmds = NULL;
}

void CommandGen::setAllColors(char red, char green, char blue, bool sideCondition, char side)
{
	// red
	char command = CMD_SET_COLOR;
	command |= COLOR_RED_SW;
	command |= side ;
	if(sideCondition) { command |= SIDE_CONDITION; }
	this->sendCommand(command, red);

	// green
	command  = CMD_SET_COLOR;
	command |= COLOR_GREEN_SW;
	command |= side ;
	if(sideCondition) { command |= SIDE_CONDITION; }
	this->sendCommand(command, green);

	// blue
	command  = CMD_SET_COLOR;
	command |= COLOR_BLUE_SW;
	command |= side ;
	if(sideCondition) { command |= SIDE_CONDITION; }
	this->sendCommand(command, blue);

	if(sideCondition) {
		setColorStatus(COLOR_RED_SW  , red  , side);
		setColorStatus(COLOR_GREEN_SW, green, side);
		setColorStatus(COLOR_BLUE_SW , blue , side);
	} else {
		setColorStatus(COLOR_RED_SW  , red  );
		setColorStatus(COLOR_GREEN_SW, green);
		setColorStatus(COLOR_BLUE_SW , blue );
	}
}

void CommandGen::setColor(char color, char colorValue, bool sideCondition, char side)
{
	char command = CMD_SET_COLOR;
	command |= color;
	command |= side ;
	if(sideCondition) { command |= SIDE_CONDITION; }
	this->sendCommand(command, colorValue);

	if(sideCondition) setColorStatus(color, colorValue, side); else setColorStatus(color, colorValue);
}

void CommandGen::setWhite(char colorValue, bool sideCondition, char side)
{
	char command;
	if(!sideCondition || side==SIDE_UP)
	{
		command = CMD_SET_ONE_LED;
		command|= WHITE_U_SW;
		this->sendCommand(command, colorValue);
	}
	if(!sideCondition || side==SIDE_BOTTOM)
	{
		command = CMD_SET_ONE_LED;
		command|= WHITE_B_SW;
		this->sendCommand(command, colorValue);
	}

	if(sideCondition) setColorStatus(COLOR_WHITE_SW, colorValue, side); else setColorStatus(COLOR_WHITE_SW, colorValue);
}

void CommandGen::setDefault()
{
	char command = CMD_SET_DEFAULT;
	char value   = 0x00;
	this->sendCommand(command, value);
}

void CommandGen::setFade(bool on)
{
	char command = CMD_SET_FADE;
	char value   = (char)on;
	this->sendCommand(command, value);
}

void CommandGen::setLED(char color, char colorValue, char side, char branch)
{
	char command = CMD_SET_ONE_LED;
	switch(color)
	{
	case COLOR_RED_SW:
		switch(branch)
		{
		case 0: if(side==SIDE_UP) command |= RED_1U_SW; else command |= RED_1B_SW; break;
		case 1: if(side==SIDE_UP) command |= RED_2U_SW; else command |= RED_2B_SW; break;
		case 2: if(side==SIDE_UP) command |= RED_3U_SW; else command |= RED_3B_SW; break;
		default: return; break;
		}
//		printDebug("Setting Red(Branch: "+QString::number(branch)+", Side: "+QString::number(side)+") to 0x"+QString::number(colorValue, 16));
		setColorStatus(color, colorValue, side, (int)branch);
		break;
	case COLOR_GREEN_SW:
		switch(branch)
		{
		case 0: if(side==SIDE_UP) command |= GREEN_1U_SW; else command |= GREEN_1B_SW; break;
		case 1: if(side==SIDE_UP) command |= GREEN_2U_SW; else command |= GREEN_2B_SW; break;
		case 2: if(side==SIDE_UP) command |= GREEN_3U_SW; else command |= GREEN_3B_SW; break;
		default: return; break;
		}
//		printDebug("Setting Green(Branch: "+QString::number(branch)+", Side: "+QString::number(side)+") to 0x"+QString::number(colorValue, 16));
		setColorStatus(color, colorValue, side, (int)branch);
		break;
	case COLOR_BLUE_SW:
		switch(branch)
		{
		case 0: if(side==SIDE_UP) command |= BLUE_1U_SW; else command |= BLUE_1B_SW; break;
		case 1: if(side==SIDE_UP) command |= BLUE_2U_SW; else command |= BLUE_2B_SW; break;
		case 2: if(side==SIDE_UP) command |= BLUE_3U_SW; else command |= BLUE_3B_SW; break;
		default: return; break;
		}
//		printDebug("Setting Blue(Branch: "+QString::number(branch)+", Side: "+QString::number(side)+") to 0x"+QString::number(colorValue, 16));
		setColorStatus(color, colorValue, side, (int)branch);
		break;
	case COLOR_WHITE_SW:
		if(side==SIDE_UP) command |= WHITE_U_SW; else command |= WHITE_B_SW;
//		printDebug("Setting White(Side: "+QString::number(side)+") to 0x"+QString::number(colorValue, 16));
		setColorStatus(color, colorValue, side);
		break;
	default: return; break;
	}
	this->sendCommand(command, colorValue);
}

void CommandGen::doSequenceStep(SequenceStep *step)
{
	LedSide	*top	  = step->getLedSide(SIDE_TOP);
	LedSide	*bot	  = step->getLedSide(SIDE_BOT);
	bool	 sideCond = true;

	setFade(step->getFageLight());

	switch(top->getLightType())
	{
	case LIGHT_TYPE_NOCHANGE: break;
	case LIGHT_TYPE_RANDOM:
	case LIGHT_TYPE_MANUAL:
		top->createNewRandomColor();
		if(bot->getLightType()==LIGHT_TYPE_SAME) sideCond = false;
		for(int i=0;i<3;i++)
		{
			setLED(COLOR_RED_SW  , top->red  (i), SIDE_UP, i); if(bot->getLightType()==LIGHT_TYPE_SAME) setLED(COLOR_RED_SW  , top->red  (i), SIDE_BOTTOM, i);
			setLED(COLOR_GREEN_SW, top->green(i), SIDE_UP, i); if(bot->getLightType()==LIGHT_TYPE_SAME) setLED(COLOR_GREEN_SW, top->green(i), SIDE_BOTTOM, i); 
			setLED(COLOR_BLUE_SW , top->blue (i), SIDE_UP, i); if(bot->getLightType()==LIGHT_TYPE_SAME) setLED(COLOR_BLUE_SW , top->blue (i), SIDE_BOTTOM, i);
		}
		setWhite(top->white(), sideCond, SIDE_UP);
		break;
	case LIGHT_TYPE_SAME: break;
	}

	sideCond = true;

	switch(bot->getLightType())
	{
	case LIGHT_TYPE_NOCHANGE: break;
	case LIGHT_TYPE_RANDOM:
	case LIGHT_TYPE_MANUAL:
		bot->createNewRandomColor();
		if(top->getLightType()==LIGHT_TYPE_SAME) sideCond = false;
		for(int i=0;i<3;i++)
		{
			setLED(COLOR_RED_SW  , bot->red  (i), SIDE_BOTTOM, i); if(top->getLightType()==LIGHT_TYPE_SAME) setLED(COLOR_RED_SW  , bot->red  (i), SIDE_UP, i);
			setLED(COLOR_GREEN_SW, bot->green(i), SIDE_BOTTOM, i); if(top->getLightType()==LIGHT_TYPE_SAME) setLED(COLOR_GREEN_SW, bot->green(i), SIDE_UP, i); 
			setLED(COLOR_BLUE_SW , bot->blue (i), SIDE_BOTTOM, i); if(top->getLightType()==LIGHT_TYPE_SAME) setLED(COLOR_BLUE_SW , bot->blue (i), SIDE_UP, i);
		}
		setWhite(bot->white(), sideCond, SIDE_BOTTOM);
		break;
	case LIGHT_TYPE_SAME: break;
	}
}

vector<pair<char, char> *> *CommandGen::getTransmitBuffer	 () { return uartCmds; }
unsigned int			   *CommandGen::getBufferWritePointer() { return &cmdWritePointer; }