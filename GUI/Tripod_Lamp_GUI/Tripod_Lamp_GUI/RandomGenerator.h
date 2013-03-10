#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <QTime>

#include "CommandDefs.h"

class RandomGenerator
{
private:
	int colors;
	int dimFactor;
	bool red, green, blue, white;
	bool sameColor;

	unsigned char redV  [3], lastRed  [3];
	unsigned char greenV[3], lastGreen[3];
	unsigned char blueV [3], lastBlue [3];
	unsigned char whiteV   , lastWhite;

	void saveValuesToLast();
	bool equalWithLast	 ();
	bool lightIsZero	 ();
	int  colorsUsed		 ();
	void createRandom	 ();

public: 
	RandomGenerator(int getColors, int getDimFactor, bool getRed, bool getGreen, bool getBlue, bool getWhite, bool getSameColor);
	~RandomGenerator();

	int	 whatColors		 ();
	int  getDimmingFactor();
	bool useRed			 ();
	bool useGreen		 ();
	bool useBlue		 ();
	bool useWhite		 ();
	bool useSameColor	 ();

	void setWhatColors(int  c );
	void setDimFactor (int  df);
	void setRed		  (bool r );
	void setGreen	  (bool g );
	void setBlue	  (bool b );
	void setWhite	  (bool w );
	void setSameColor (bool sc);

	unsigned char redValue  (int i);
	unsigned char greenValue(int i);
	unsigned char blueValue (int i);
	unsigned char whiteValue();

	void createNewColor();
};

#define ONLY_FULL_COLORS	0
#define USE_ALL_COLORS		1


#endif // SEQUENCESTEP_H