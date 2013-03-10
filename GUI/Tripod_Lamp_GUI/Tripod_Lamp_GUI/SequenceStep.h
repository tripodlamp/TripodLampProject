#ifndef SEQUENCESTEP_H
#define SEQUENCESTEP_H

#include <QTime>
#include <QString>
#include <QTableWidgetItem>
#include <vector>
#include "LedSide.h"

using namespace std;

class SequenceStep
{
private:
	QTime			  timeToNextStep;
	bool			  fadeLight;
	QString			  title;
	QTableWidgetItem *tableItem;
	vector<LedSide>  *ledSides;

	void createItemText();

public:
	SequenceStep (QString getTitle = "");
	~SequenceStep();

	unsigned char red  (unsigned int side, int branch);
	unsigned char green(unsigned int side, int branch);
	unsigned char blue (unsigned int side, int branch);
	unsigned char white(unsigned int side);

	int		getNewLightType  ();
	QTime	getTimeToNextStep();
	bool	getFageLight	 ();
	QString getTitle		 ();
	QTableWidgetItem* getItem();
	RandomGenerator*  getRanGen (unsigned int g);
	LedSide*		  getLedSide(unsigned int side);

	void setTimeToNextStep(QTime t);
	void setFadeLight(bool f);
	void setTitle(QString t);
	void addRandomGenerator(int side, int colors, int dimFactor, bool red, bool green, bool blue, bool white, bool sameColor);
	void generateNewLight();
};

#define SIDE_TOP			0
#define SIDE_BOT			1

#define NEW_LIGHT_RANDOM	0
#define NEW_LIGHT_MANUAL	1

#endif // SEQUENCESTEP_H