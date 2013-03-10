#include "Preset.h"

Preset::Preset() 
{
	presetName = "";

	for(unsigned int i=0;i<NUM_SIDES;i++)
	{
		whiteValues[i] = 0x00;
		for(unsigned int j=0;j<NUM_BRANCHES;j++)
			for(unsigned int k=0;k<NUM_COLORS;k++)
				colorValues[i][j][k] = 0x00;
	}
}

Preset::~Preset() { }

QString Preset::getName()
{
	return presetName;
}

unsigned char Preset::colorValue(unsigned int side, unsigned int branch, unsigned int color)
{
	if(side<NUM_SIDES && branch<NUM_BRANCHES && color<NUM_COLORS)
		return colorValues[side][branch][color];

	return 0;
}

unsigned char Preset::whiteValue(unsigned int side)
{
	if(side<NUM_SIDES)
		return whiteValues[side];

	return 0;
}


void Preset::setName(QString name)
{
	presetName = name;
}

void Preset::setColor(unsigned int side, unsigned int branch, unsigned int color, unsigned char value)
{
	if(side<NUM_SIDES && branch<NUM_BRANCHES && color<NUM_COLORS)
		colorValues[side][branch][color] = value;
}

void Preset::setWhite(unsigned int side, unsigned char value)
{  
	if(side<NUM_SIDES)
		whiteValues[side] = value;
}