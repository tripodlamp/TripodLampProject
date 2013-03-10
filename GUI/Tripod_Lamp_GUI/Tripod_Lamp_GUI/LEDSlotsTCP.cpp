#include "tripod_lamp_gui.h"

void Tripod_Lamp_GUI::changeLEDs(char color, int changeValue, char side, int branch)
{
	bool sideCondition = true;
	if(side==SIDE_BOTH) { sideCondition = false; }

	if(branch<NUM_BRANCHES || color==COLOR_WHITE_SW)	// Just check one branch
		changeBranch(color, changeValue, side, branch);
	else												// Check all branches
		for(unsigned int i=0;i<NUM_BRANCHES;i++)
			changeBranch(color, changeValue, side, i);
}

void Tripod_Lamp_GUI::changeBranch(char color, int changeValue, char side, int branch)
{
	char colorValue;
	
	if(side==SIDE_UP || side==SIDE_BOTH)
	{
//		while(cal->isRunning()) {  } // Wait loop until thread 'command line' has finished
//		colorValue = getColorValue(color, SIDE_UP, branch);
//		colorValue = getNewColorValue(colorValue, changeValue);
		colorValue = (char)(changeValue*MAX_LED_VALUE/100);
		cmg->setLED(color, (char)colorValue, SIDE_UP, branch);			// call same method as in LEDSlotsSpecificLED.cpp
	}

	if(side==SIDE_BOTTOM || side==SIDE_BOTH)
	{
//		while(cal->isRunning()) {  } // Wait loop until thread 'command line' has finished
//		colorValue = getColorValue(color, SIDE_BOTTOM, branch);
//		colorValue = getNewColorValue(colorValue, changeValue);
		colorValue = (char)(changeValue*MAX_LED_VALUE/100);
		cmg->setLED(color, (char)colorValue, SIDE_BOTTOM, branch);		// call same method as in LEDSlotsSpecificLED.cpp
	}
}

char Tripod_Lamp_GUI::getColorValue(char color, char side, int branch)
{
	char returnValue = 0x00;

	switch(color)
	{
	case COLOR_RED_SW  : returnValue = lst->getRed  (side, branch); break;
	case COLOR_GREEN_SW: returnValue = lst->getGreen(side, branch); break;
	case COLOR_BLUE_SW : returnValue = lst->getBlue (side, branch); break;
	case COLOR_WHITE_SW: returnValue = lst->getWhite(side		 ); break;
	default: break;
	}

	return returnValue;
}

char Tripod_Lamp_GUI::getNewColorValue(char colorValue, int changeValue)
{
	int value = colorValue;

	value&= 0xFF;
	value+= changeValue;

		 if(changeValue==0) 	 value = 0;
	else if(value>MAX_LED_VALUE) value = MAX_LED_VALUE;
	else if(value<0)			 value = 0;

	return (char)(value & 0xFF);
}