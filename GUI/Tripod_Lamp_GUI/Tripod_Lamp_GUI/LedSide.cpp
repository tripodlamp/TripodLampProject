#include "LedSide.h"

LedSide::LedSide(unsigned int getLightType)
{
	ranGen = NULL;
	setLightType(getLightType);

	for(int i=0;i<3;i++)
	{
		redValue  [i] = 0;
		greenValue[i] = 0;
		blueValue [i] = 0;
	}
	whiteValue = 0;
}

LedSide::~LedSide()
{
	if(ranGen!=NULL) { delete(ranGen); ranGen = NULL; }
}


unsigned int LedSide::getLightType () { return lightType; }
RandomGenerator* LedSide::getRanGen() { return ranGen	; }

unsigned char LedSide::red(int branch)
{
	unsigned char red = 0;
	if(branch>=3) return 0;
	switch(lightType)
	{
	case LIGHT_TYPE_NOCHANGE: break;
	case LIGHT_TYPE_RANDOM	: if(ranGen!=NULL) red = ranGen->redValue(branch); break;
	case LIGHT_TYPE_MANUAL	: red = (unsigned char)((((float)redValue[branch])/100)*MAX_LED_VALUE); break;
	case LIGHT_TYPE_SAME	: break;
	}
	return red;
}

unsigned char LedSide::green(int branch)
{
	unsigned char green = 0;
	if(branch>=3) return 0;
	switch(lightType)
	{
	case LIGHT_TYPE_NOCHANGE: break;
	case LIGHT_TYPE_RANDOM	: if(ranGen!=NULL) green = ranGen->greenValue(branch); break;
	case LIGHT_TYPE_MANUAL	: green = (unsigned char)((((float)greenValue[branch])/100)*MAX_LED_VALUE); break;
	case LIGHT_TYPE_SAME	: break;
	}
	return green;
}

unsigned char LedSide::blue(int branch)
{
	unsigned char blue = 0;
	if(branch>=3) return 0;
	switch(lightType)
	{
	case LIGHT_TYPE_NOCHANGE: break;
	case LIGHT_TYPE_RANDOM	: if(ranGen!=NULL) blue = ranGen->blueValue(branch); break;
	case LIGHT_TYPE_MANUAL	: blue = (unsigned char)((((float)blueValue[branch])/100)*MAX_LED_VALUE); break;
	case LIGHT_TYPE_SAME	: break;
	}
	return blue;
}

unsigned char LedSide::white()
{
	unsigned char white = 0;
	switch(lightType)
	{
	case LIGHT_TYPE_NOCHANGE: break;
	case LIGHT_TYPE_RANDOM	: if(ranGen!=NULL) white = ranGen->whiteValue(); break;
	case LIGHT_TYPE_MANUAL  : white = (unsigned char)((((float)whiteValue)/100)*MAX_LED_VALUE); break;
	case LIGHT_TYPE_SAME	: break;
	}
	return white;
}

unsigned char LedSide::redPercent  (int branch) { if(branch>=3) return 0; return redValue  [branch]; }
unsigned char LedSide::greenPercent(int branch) { if(branch>=3) return 0; return greenValue[branch]; }
unsigned char LedSide::bluePercent (int branch) { if(branch>=3) return 0; return blueValue [branch]; }
unsigned char LedSide::whitePercent(		  ) { return whiteValue; }

void LedSide::setLightType(unsigned int i)
{
	lightType = i;

	if(lightType!=LIGHT_TYPE_RANDOM && ranGen!=NULL) {
		delete(ranGen); ranGen = NULL;
	}
}

void LedSide::setRandomGenerator(int colors, int dimFactor, bool red, bool green, bool blue, bool white, bool sameColor)
{
	if(ranGen!=NULL) {
		delete(ranGen); ranGen = NULL;
	}
	ranGen = new RandomGenerator(colors, dimFactor, red, green, blue, white, sameColor);
}

void LedSide::setRed(int branch, unsigned char value)
{
	if(branch>=3) return;
	redValue[branch] = value;
}

void LedSide::setGreen(int branch, unsigned char value)
{
	if(branch>=3) return;
	greenValue[branch] = value;
}
void LedSide::setBlue(int branch, unsigned char value)
{
	if(branch>=3) return;
	blueValue[branch] = value;
}

void LedSide::setWhite(unsigned char value) { whiteValue = value; }


void LedSide::createNewRandomColor()
{
	if(ranGen!=NULL) ranGen->createNewColor();
}