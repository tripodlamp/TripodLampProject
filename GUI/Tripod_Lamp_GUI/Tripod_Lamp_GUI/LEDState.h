#ifndef LEDSTATE_H
#define LEDSTATE_H

#include <vector>
#include "Led.h"
#include "CommandDefs.h"

using namespace std;

class LedState
{
private:
	vector<vector<Led*>* > *branches;

public:
	LedState();
	~LedState();

	unsigned char getRed  (char side, int branch);
	unsigned char getGreen(char side, int branch);
	unsigned char getBlue (char side, int branch);
	unsigned char getWhite(char side			);
	
	void setRed(char colorValue);
	void setRed(char colorValue, char side);
	void setRed(char colorValue, char side, int branch);

	void setGreen(char colorValue);
	void setGreen(char colorValue, char side);
	void setGreen(char colorValue, char side, int branch);

	void setBlue(char colorValue);
	void setBlue(char colorValue, char side);
	void setBlue(char colorValue, char side, int branch);

	void setWhite(char colorValue);
	void setWhite(char colorValue, char side);
};

#define NUM_BRANCHES	3

#endif // LEDSTATE_H