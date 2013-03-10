#include "SequenceStep.h"

// ================= Private methods =================

void SequenceStep::createItemText()
{
	tableItem->setText(title+" ("+timeToNextStep.toString("mm:ss.z")+")");
}

// ================= Constructor / Destructor =================

SequenceStep::SequenceStep(QString getTitle)
{
	timeToNextStep = QTime(0, 0, 1);
	fadeLight	   = false;
	title		   = getTitle;

	tableItem	   = new QTableWidgetItem();
	ledSides	   = new vector<LedSide>;
	ledSides->push_back(LedSide());
	ledSides->push_back(LedSide());

	createItemText();
}

SequenceStep::~SequenceStep()
{
	delete(tableItem); tableItem = NULL;
	if(ledSides!=NULL) { delete(ledSides); ledSides = NULL; }
}

// ================= Public methods =================

unsigned char SequenceStep::red(unsigned int side, int branch)
{
	if(branch>=3 || side>=2) { return 0; }
	return ledSides->at(side).red(branch);
}

unsigned char SequenceStep::green(unsigned int side, int branch)
{
	if(branch>=3 || side>=2) { return 0; }
	return ledSides->at(side).green(branch);
}

unsigned char SequenceStep::blue(unsigned int side, int branch)
{
	if(branch>=3 || side>=2) { return 0; }
	return ledSides->at(side).blue(branch);
}

unsigned char SequenceStep::white(unsigned int side)
{
	if(side>=2) { return 0; }
	return ledSides->at(side).white();
}

QTime	SequenceStep::getTimeToNextStep() { return timeToNextStep; }
bool	SequenceStep::getFageLight	   () { return fadeLight	 ; }
QString SequenceStep::getTitle		   () { return title		 ; }

QTableWidgetItem* SequenceStep::getItem() { return tableItem	 ; }

RandomGenerator* SequenceStep::getRanGen(unsigned int side)
{
	if(side>=2) { return NULL; }
	return ledSides->at(side).getRanGen();
}

LedSide* SequenceStep::getLedSide(unsigned int side)
{
	if(side>=2) { return NULL; }
	return &(ledSides->at(side));
}

void SequenceStep::setTimeToNextStep(QTime t)
{
	float msec_f = (float)t.msec()/100;
	int   msec_i = (int  )msec_f  *100;

	timeToNextStep = QTime(0, t.minute(), t.second(), msec_i);

	createItemText();
}

void SequenceStep::setFadeLight		(bool	 f) { fadeLight = f; }
void SequenceStep::setTitle			(QString t) { title		= t; createItemText(); }

void SequenceStep::addRandomGenerator(int side, int colors, int dimFactor, bool red, bool green, bool blue, bool white, bool sameColor)
{
	if(side>=2) { return; }
	ledSides->at(side).setRandomGenerator(colors, dimFactor, red, green, blue, white, sameColor);
}

void SequenceStep::generateNewLight()
{
	for(unsigned int i=0;i<ledSides->size();i++)
		ledSides->at(i).createNewRandomColor();
}