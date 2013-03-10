#ifndef SEQUENCETABLE_H
#define SEQUENCETABLE_H

#include <QFile>
#include <QScrollBar>
#include <QFileDialog>
#include <QHeaderView>
#include <QTextStream>
#include <QMessageBox>
#include <QTableWidget>

#include <vector>

#include "SequenceStep.h"

using namespace std;

class SequenceTable : public QTableWidget
{
	Q_OBJECT

private:
	int			 lastClickedRow;
	unsigned int stepCounter;

	vector<SequenceStep*> *steps;

	void redrawTable();
	void clearTable ();

public:
	SequenceTable(QWidget *parent);
	virtual ~SequenceTable();

	void removeStep	   ();
	void removeAllSteps();

	unsigned int  stepCount   ();
	SequenceStep* sequenceStep();
	SequenceStep* sequenceStep(unsigned int step);

public slots:
	void addStep	 ();
	void moveStepUp	 ();
	void moveStepDown();
	void loadFromFile();
	void saveToFile  ();

private slots:
	void tableClicked(int row, int column);

signals:
	void loadStep(unsigned int);
};

#define TIME_FORMAT			"mm:ss.zzz"

#define SEP_STEP			"|A|"
#define SEP_HEADER_BLOCK	"|B|"
#define SEP_HEADER_INFO		"|C|"
#define SEP_LED_SIDE		"|D|"
#define SEP_LED_SIDE_INFO	"|E|"

#endif // SEQUENCETABLE_H