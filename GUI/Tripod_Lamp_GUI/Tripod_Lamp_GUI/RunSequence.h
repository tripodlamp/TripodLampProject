#ifndef RUNSEQUENCE_H
#define RUNSEQUENCE_H

#include <QIcon>
#include <QTime>
#include <QTimer>
#include <QDialog>
#include <QtGui/QMainWindow>
#include <vector>
#include "SequenceTable.h"
#include "ui_FormRunSequence.h"

#define TIMER_INTERVALL		100

class RunSequence : public QDialog
{
	Q_OBJECT

public:
	RunSequence(QWidget *parent = 0, Qt::WFlags flags = 0);
	~RunSequence();

	void setSequence(SequenceTable *getSeqTable);
	void setStartStep(unsigned int s);
	void activateTimer();

private:
	Ui::FormRunSequence ui;

	SequenceTable *seqTable;
	QTimer		  *timer;
	QTime		   time;
	QIcon		   iconPause, iconContinue;

	unsigned int   stepNow, stepNxt;

	void updateLabels();
	void setPauseButton(bool showPause);
	virtual void closeEvent(QCloseEvent *e);

private slots:
	void timerInterrupt();
	void pauseSequence ();
	void stopSequence  ();

signals:
	void doSequenceStep(unsigned int);

};
#endif // RUNSEQUENCE_H