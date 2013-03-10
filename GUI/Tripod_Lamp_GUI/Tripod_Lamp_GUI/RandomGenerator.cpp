#include "RandomGenerator.h"

// ================= Private methods =================

void RandomGenerator::saveValuesToLast()
{
	for(unsigned int i=0;i<3;i++) {
		lastRed [i] = redV [i]; lastGreen[i] = greenV[i];
		lastBlue[i] = blueV[i]; lastWhite	 = whiteV;
	}
}

bool RandomGenerator::equalWithLast()
{
	if(colorsUsed()==0 || colorsUsed()==1) return false;
	for(unsigned int i=0;i<3;i++) {
		if(lastRed  [i]!=redV  [i]) return false;
		if(lastGreen[i]!=greenV[i]) return false;
		if(lastBlue [i]!=blueV [i]) return false;
	}
	if(lastWhite!=whiteV) return false;
	return true;
}

bool RandomGenerator::lightIsZero()
{
	if(colorsUsed()==0) return false;
	for(unsigned int i=0;i<3;i++) {
		if(0x00!=redV  [i]) return false;
		if(0x00!=greenV[i]) return false;
		if(0x00!=blueV [i]) return false;
	}
	if(0x00!=whiteV) return false;
	return true;
}

int RandomGenerator::colorsUsed()
{
	int num = 0;
	if(red  ) num++;
	if(green) num++;
	if(blue ) num++;
	if(white) num++;
	return num;
}

void RandomGenerator::createRandom()
{
	unsigned int randNumber[10];
	unsigned int j = 0;

	// Generate random light values
//	srand(time(NULL));
	QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

	for(unsigned int i=0;i<10;i++)
	{
		randNumber[i] = rand();
		if(colors==USE_ALL_COLORS)
			randNumber[i] = randNumber[i] % MAX_LED_VALUE;
		else
			randNumber[i] = (randNumber[i] % 2) * MAX_LED_VALUE;

		randNumber[i] = (unsigned char)((((float)randNumber[i])*dimFactor)/100);
	}
	
	// Reset old light values
	for(unsigned int i=0;i<3;i++)
	{
		redV [i] = 0; greenV[i] = 0;
		blueV[i] = 0; whiteV    = 0;
	}

	// Assign new read values
	if(red)
	{
		redV[0] = randNumber[j++];
		if(sameColor) redV[1] = redV[0]; else redV[1] = randNumber[j++];
		if(sameColor) redV[2] = redV[0]; else redV[2] = randNumber[j++];
	}

	if(green)
	{
		greenV[0] = randNumber[j++];
		if(sameColor) greenV[1] = greenV[0]; else greenV[1] = randNumber[j++];
		if(sameColor) greenV[2] = greenV[0]; else greenV[2] = randNumber[j++];
	}

	if(blue)
	{
		blueV[0] = randNumber[j++];
		if(sameColor) blueV[1] = blueV[0]; else blueV[1] = randNumber[j++];
		if(sameColor) blueV[2] = blueV[0]; else blueV[2] = randNumber[j++];
	}

	if(white) { whiteV = randNumber[j]; }
}

// ================= Constructor / Destructor =================

RandomGenerator::RandomGenerator(int getColors, int getDimFactor, bool getRed, bool getGreen, bool getBlue, bool getWhite, bool getSameColor)
{
	colors	  = getColors;
	dimFactor = getDimFactor;
	red		  = getRed;
	green	  = getGreen;
	blue	  = getBlue;
	white	  = getWhite;
	sameColor = getSameColor;

	for(unsigned int i=0;i<3;i++) {
		redV [i] = 0; greenV[i] = 0;
		blueV[i] = 0; whiteV    = 0;
	}
	saveValuesToLast();
}

RandomGenerator::~RandomGenerator() {  }


// ================= Public methods =================

int	 RandomGenerator::whatColors	  () { return colors   ; }
int  RandomGenerator::getDimmingFactor() { return dimFactor; }
bool RandomGenerator::useRed		  () { return red	   ; }
bool RandomGenerator::useGreen		  () { return green	   ; }
bool RandomGenerator::useBlue		  () { return blue	   ; }
bool RandomGenerator::useWhite		  () { return white	   ; }
bool RandomGenerator::useSameColor	  () { return sameColor; }

void RandomGenerator::setWhatColors(int  c ) { colors	 = c ; }
void RandomGenerator::setDimFactor (int  df) { dimFactor = df; }
void RandomGenerator::setRed	   (bool r ) { red		 = r ; }
void RandomGenerator::setGreen	   (bool g ) { green	 = g ; }
void RandomGenerator::setBlue	   (bool b ) { blue		 = b ; }
void RandomGenerator::setWhite	   (bool w ) { white	 = w ; }
void RandomGenerator::setSameColor (bool sc) { sameColor = sc; }
unsigned char RandomGenerator::redValue  (int i) { if(i>=3) return 0; return redV  [i]; }
unsigned char RandomGenerator::greenValue(int i) { if(i>=3) return 0; return greenV[i]; }
unsigned char RandomGenerator::blueValue (int i) { if(i>=3) return 0; return blueV [i]; }
unsigned char RandomGenerator::whiteValue(     ) {					  return whiteV   ; }

void RandomGenerator::createNewColor()
{
	while(equalWithLast() || lightIsZero())
		createRandom();

	saveValuesToLast();
}