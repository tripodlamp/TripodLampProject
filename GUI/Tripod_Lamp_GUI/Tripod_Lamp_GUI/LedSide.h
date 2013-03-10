#ifndef LEDSIDE_H
#define LEDSIDE_H

#include <vector>
#include "RandomGenerator.h"

using namespace std;

#define LIGHT_TYPE_NOCHANGE		0
#define LIGHT_TYPE_RANDOM		1
#define LIGHT_TYPE_MANUAL		2
#define LIGHT_TYPE_SAME			3

class LedSide
{
private:
	unsigned int lightType;
	RandomGenerator *ranGen;
	unsigned char redValue  [3];
	unsigned char greenValue[3];
	unsigned char blueValue [3];
	unsigned char whiteValue;

public:
	LedSide(unsigned int getLightType = LIGHT_TYPE_NOCHANGE);
	~LedSide();

	unsigned int getLightType ();
	RandomGenerator *getRanGen();

	unsigned char red  (int branch);
	unsigned char green(int branch);
	unsigned char blue (int branch);
	unsigned char white(		  );

	unsigned char redPercent  (int branch);
	unsigned char greenPercent(int branch);
	unsigned char bluePercent (int branch);
	unsigned char whitePercent(			 );
	
	void setLightType(unsigned int i);
	void setRandomGenerator(int colors, int dimFactor, bool red, bool green, bool blue, bool white, bool sameColor);
	void setRed  (int branch, unsigned char value);
	void setGreen(int branch, unsigned char value);
	void setBlue (int branch, unsigned char value);
	void setWhite(			  unsigned char value);


	void createNewRandomColor();
};

#endif // LEDSIDE_H