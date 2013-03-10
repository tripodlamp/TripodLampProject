#include "LEDState.h"

LedState::LedState()
{
	branches = new vector<vector<Led*>* >;
	for(unsigned int i=0;i<NUM_BRANCHES;i++)
	{
		branches->push_back(new vector<Led*>);
		branches->at(i)->push_back(new Led());
		branches->at(i)->push_back(new Led());
	}
}

LedState::~LedState()
{
	for(unsigned int i=0;i<NUM_BRANCHES;i++)
	{
		delete(branches->at(i)->at(0)); branches->at(i)->at(0) = NULL;
		delete(branches->at(i)->at(1)); branches->at(i)->at(1) = NULL;
		delete(branches->at(i)); branches->at(i) = NULL;
	}
}

unsigned char LedState::getRed(char side, int branch)
{
	if(branch>=NUM_BRANCHES) return 0x00;
	if(side>0) side = 1;
	return branches->at(branch)->at(side)->red();
}

unsigned char LedState::getGreen(char side, int branch)
{
	if(branch>=NUM_BRANCHES) return 0x00;
	if(side>0) side = 1;
	return branches->at(branch)->at(side)->green();
}

unsigned char LedState::getBlue(char side, int branch)
{
	if(branch>=NUM_BRANCHES) return 0x00;
	if(side>0) side = 1;
	return branches->at(branch)->at(side)->blue();
}

unsigned char LedState::getWhite(char side)
{
	if(side>0) side = 1;
	return branches->at(0)->at(side)->white();
}

// ======================================================

void LedState::setRed(char colorValue)
{
	for(unsigned int i=0;i<NUM_BRANCHES;i++)
	{
		branches->at(i)->at(0)->setRed(colorValue);
		branches->at(i)->at(1)->setRed(colorValue);
	}
}

void LedState::setRed(char colorValue, char side)
{
	if(side>0) side = 1;
	for(unsigned int i=0;i<NUM_BRANCHES;i++)
		branches->at(i)->at(side)->setRed(colorValue);
}

void LedState::setRed(char colorValue, char side, int branch)
{
	if(branch>=NUM_BRANCHES) return;
	if(side>0) side = 1;
	branches->at(branch)->at(side)->setRed(colorValue);
}

// ======================================================

void LedState::setGreen(char colorValue)
{
	for(unsigned int i=0;i<NUM_BRANCHES;i++)
	{
		branches->at(i)->at(0)->setGreen(colorValue);
		branches->at(i)->at(1)->setGreen(colorValue);
	}
}

void LedState::setGreen(char colorValue, char side)
{
	if(side>0) side = 1;
	for(unsigned int i=0;i<NUM_BRANCHES;i++)
		branches->at(i)->at(side)->setGreen(colorValue);
}

void LedState::setGreen(char colorValue, char side, int branch)
{
	if(branch>=NUM_BRANCHES) return;
	if(side>0) side = 1;
	branches->at(branch)->at(side)->setGreen(colorValue);
}

// ======================================================

void LedState::setBlue(char colorValue)
{
	for(unsigned int i=0;i<NUM_BRANCHES;i++)
	{
		branches->at(i)->at(0)->setBlue(colorValue);
		branches->at(i)->at(1)->setBlue(colorValue);
	}
}

void LedState::setBlue(char colorValue, char side)
{
	if(side>0) side = 1;
	for(unsigned int i=0;i<NUM_BRANCHES;i++)
		branches->at(i)->at(side)->setBlue(colorValue);
}

void LedState::setBlue(char colorValue, char side, int branch)
{
	if(branch>=NUM_BRANCHES) return;
	if(side>0) side = 1;
	branches->at(branch)->at(side)->setBlue(colorValue);
}

// ======================================================

void LedState::setWhite(char colorValue)
{
	for(unsigned int i=0;i<NUM_BRANCHES;i++)
	{
		branches->at(i)->at(0)->setWhite(colorValue);
		branches->at(i)->at(1)->setWhite(colorValue);
	}
}

void LedState::setWhite(char colorValue, char side)
{
	if(side>0) side = 1;
	for(unsigned int i=0;i<NUM_BRANCHES;i++)
		branches->at(i)->at(side)->setWhite(colorValue);
}

// ======================================================