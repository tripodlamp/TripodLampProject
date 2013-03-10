#include "RunSequence.h"

RunSequence::RunSequence(QWidget *parent, Qt::WFlags flags)
{
	ui.setupUi(this);
	this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

	seqTable = NULL;
	timer = new QTimer(this);
	timer->setInterval(TIMER_INTERVALL);
	time.setHMS(0, 0, 0);
	stepNow = 0; stepNxt = 0;
	iconPause   .addFile(QString::fromUtf8(":/Tripod_Lamp_GUI/Icons/control_pause_blue.png"), QSize(), QIcon::Normal, QIcon::Off);
	iconContinue.addFile(QString::fromUtf8(":/Tripod_Lamp_GUI/Icons/control_play_blue.png" ), QSize(), QIcon::Normal, QIcon::Off);


	QObject::connect(timer			   , SIGNAL(timeout()), this, SLOT(timerInterrupt()));
	QObject::connect(ui.pushButtonPause, SIGNAL(clicked()), this, SLOT(pauseSequence ()));
	QObject::connect(ui.pushButtonStop , SIGNAL(clicked()), this, SLOT(stopSequence  ()));

	ui.labelTime->setText(time.toString());
}

RunSequence::~RunSequence()
{
	delete(timer); timer = NULL;
}

void RunSequence::setSequence (SequenceTable *getSeqTable) { seqTable = getSeqTable; }

void RunSequence::setStartStep(unsigned int s)
{
	if(s<seqTable->stepCount());
	{
		stepNow = s;
		time = seqTable->sequenceStep(s)->getTimeToNextStep();
	}
}

void RunSequence::activateTimer()
{
	updateLabels();
	doSequenceStep(stepNow);
	timer->start();
}

void RunSequence::updateLabels()
{
	stepNxt = stepNow + 1;
	if(stepNxt==seqTable->stepCount()) stepNxt = 0;
	if(stepNow<seqTable->stepCount()) ui.labelStepNow ->setText(seqTable->sequenceStep(stepNow)->getTitle());
	if(stepNxt<seqTable->stepCount()) ui.labelStepNext->setText(seqTable->sequenceStep(stepNxt)->getTitle());
	ui.labelTime->setText(time.toString("mm:ss.z"));
}

void RunSequence::setPauseButton(bool showPause)
{
	if(showPause)
	{
		ui.pushButtonPause->setText("Pause");
		ui.pushButtonPause->setIcon(iconPause);
	}
	else
	{
		ui.pushButtonPause->setText("Continue");
		ui.pushButtonPause->setIcon(iconContinue);
	}
}

void RunSequence::closeEvent(QCloseEvent *e)
{
	timer->stop();
}

void RunSequence::timerInterrupt()
{
	if(time==QTime(0, 0, 0))
	{
		stepNow++;
		if(stepNow==seqTable->stepCount()) stepNow = 0;
		time = seqTable->sequenceStep(stepNow)->getTimeToNextStep();
		doSequenceStep(stepNow);
		time = time.addMSecs(-TIMER_INTERVALL);
	}
	else
		time = time.addMSecs(-TIMER_INTERVALL);
	updateLabels();
}

void RunSequence::pauseSequence()
{
	if(timer->isActive())
	{
		// Pause here...
		timer->stop();
		setPauseButton(false);
	}
	else
	{
		// Continue here...
		timer->start();
		setPauseButton(true);
	}
}

void RunSequence::stopSequence()
{
	timer->stop();
	this->hide ();
}