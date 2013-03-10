#ifndef PRESET_H
#define PRESET_H

#include <QString>

#define NUM_SIDES		2
#define NUM_BRANCHES	3
#define NUM_COLORS		3

#define SIDE_TOP		0
#define SIDE_BOT		1
#define BRANCH_1		0
#define BRANCH_2		1
#define BRANCH_3		2
#define COLOR_RED		0
#define COLOR_GREEN		1
#define COLOR_BLUE		2

class Preset
{
private:
	QString presetName;
	unsigned char colorValues[NUM_SIDES][NUM_BRANCHES][NUM_COLORS];
	unsigned char whiteValues[NUM_SIDES];

public:
	Preset();
	~Preset();

	QString getName();
	unsigned char colorValue(unsigned int side, unsigned int branch, unsigned int color);
	unsigned char whiteValue(unsigned int side);

	void setName (QString name);
	void setColor(unsigned int side, unsigned int branch, unsigned int color, unsigned char value);
	void setWhite(unsigned int side, unsigned char value);
};

#endif // PRESETCOMBOBOX_H