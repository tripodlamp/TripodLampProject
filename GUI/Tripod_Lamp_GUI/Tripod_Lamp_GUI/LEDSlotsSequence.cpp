#include "tripod_lamp_gui.h"

void Tripod_Lamp_GUI::showOptionsTop(int i)
{
	ui.pushButtonSaveStep->setDisabled(false);
	ui.stackedWidgetTop->setCurrentIndex(i);
	if(i==LIGHT_TYPE_SAME && ui.comboBoxBotSel->currentIndex()==LIGHT_TYPE_SAME)
		ui.pushButtonSaveStep->setDisabled(true);
}

void Tripod_Lamp_GUI::showOptionsBot(int i)
{
	ui.pushButtonSaveStep->setDisabled(false);
	ui.stackedWidgetBot->setCurrentIndex(i);
	if(i==LIGHT_TYPE_SAME && ui.comboBoxTopSel->currentIndex()==LIGHT_TYPE_SAME)
		ui.pushButtonSaveStep->setDisabled(true);
}

void Tripod_Lamp_GUI::addStep()
{
	seqTable->addStep();
	if(ui.pushButtonConnect->text()=="Disconnect")
	{
		ui.pushButtonRunSeqBeg->setDisabled(false);
		ui.pushButtonRunSeqSel->setDisabled(false);
	}
}

void Tripod_Lamp_GUI::saveStep()
{
	SequenceStep *s = seqTable->sequenceStep();
	if(s==NULL) return;
	s->setTimeToNextStep(ui.timeEditToNextStep->time	());
	s->setFadeLight		(ui.checkBoxFadeLight->isChecked());
	s->setTitle			(ui.lineEditStepName ->text		());

	// Set TOP side settings
	s->getLedSide(SIDE_TOP)->setLightType(ui.comboBoxTopSel->currentIndex());
	switch(s->getLedSide(SIDE_TOP)->getLightType())
	{
	case LIGHT_TYPE_NOCHANGE: break;
	case LIGHT_TYPE_RANDOM  :
		s->addRandomGenerator(SIDE_TOP,
							  ui.comboBoxRandom1Colors->currentIndex(), 
							  ui.spinBoxRandom1Dim->value			(),
							  ui.checkBoxRandom1Red	  ->isChecked   (),
							  ui.checkBoxRandom1Green ->isChecked   (),
							  ui.checkBoxRandom1Blue  ->isChecked   (),
							  ui.checkBoxRandom1White ->isChecked   (),
							  ui.checkBoxRandom1Same  ->isChecked   ());
		break;
	case LIGHT_TYPE_MANUAL:
		for(int i=0;i<3;i++)
		{
			s->getLedSide(SIDE_TOP)->setRed  (i, (unsigned char)redTop  [i]->value());
			s->getLedSide(SIDE_TOP)->setGreen(i, (unsigned char)greenTop[i]->value());
			s->getLedSide(SIDE_TOP)->setBlue (i, (unsigned char)blueTop [i]->value());
		}
		s->getLedSide(SIDE_TOP)->setWhite((unsigned char)ui.spinBoxTopWhite->value());
		break;
	case LIGHT_TYPE_SAME: break;
	}
	
	// Set BOTTOM side settings
	s->getLedSide(SIDE_BOT)->setLightType(ui.comboBoxBotSel->currentIndex());
	switch(s->getLedSide(SIDE_BOT)->getLightType())
	{
	case LIGHT_TYPE_NOCHANGE: break;
	case LIGHT_TYPE_RANDOM  :
		s->addRandomGenerator(SIDE_BOT,
							  ui.comboBoxRandom2Colors->currentIndex(), 
							  ui.spinBoxRandom2Dim->value			(),
							  ui.checkBoxRandom2Red	  ->isChecked   (),
							  ui.checkBoxRandom2Green ->isChecked   (),
							  ui.checkBoxRandom2Blue  ->isChecked   (),
							  ui.checkBoxRandom2White ->isChecked   (),
							  ui.checkBoxRandom2Same  ->isChecked   ());
		break;
	case LIGHT_TYPE_MANUAL:
		for(int i=0;i<3;i++)
		{
			s->getLedSide(SIDE_BOT)->setRed  (i, (unsigned char)redBot  [i]->value());
			s->getLedSide(SIDE_BOT)->setGreen(i, (unsigned char)greenBot[i]->value());
			s->getLedSide(SIDE_BOT)->setBlue (i, (unsigned char)blueBot [i]->value());
		}
		s->getLedSide(SIDE_BOT)->setWhite((unsigned char)ui.spinBoxBotWhite->value());
		break;
	case LIGHT_TYPE_SAME: break;
	}
}

void Tripod_Lamp_GUI::loadStep(unsigned int step)
{
	SequenceStep *s = seqTable->sequenceStep(step);
	ui.groupBoxStep->setDisabled(false);
	setDefaultView();

	ui.groupBoxStep->setTitle("Step "+QString::number(seqTable->currentRow()+1)+": "+s->getTitle());

	ui.timeEditToNextStep->setTime		(s->getTimeToNextStep());
	ui.checkBoxFadeLight->setChecked	(s->getFageLight	 ());

	ui.comboBoxTopSel->setCurrentIndex(s->getLedSide(SIDE_TOP)->getLightType());
	ui.comboBoxBotSel->setCurrentIndex(s->getLedSide(SIDE_BOT)->getLightType());
	
	RandomGenerator *g = NULL;
	switch(s->getLedSide(SIDE_TOP)->getLightType())
	{
		case LIGHT_TYPE_NOCHANGE: break;
		case LIGHT_TYPE_RANDOM  :
			g = s->getRanGen(SIDE_TOP);
			if(g!=NULL)
			{
				ui.comboBoxRandom1Colors->setCurrentIndex(g->whatColors());
				ui.spinBoxRandom1Dim	->setValue(g->getDimmingFactor ());
				ui.checkBoxRandom1Red   ->setChecked(g->useRed		());
				ui.checkBoxRandom1Green ->setChecked(g->useGreen	());
				ui.checkBoxRandom1Blue  ->setChecked(g->useBlue		());
				ui.checkBoxRandom1White ->setChecked(g->useWhite	());
				ui.checkBoxRandom1Same  ->setChecked(g->useSameColor());
			}
			break;
		case LIGHT_TYPE_MANUAL:
			for(int i=0;i<3;i++)
			{
				redTop  [i]->setValue((int)s->getLedSide(SIDE_TOP)->redPercent  (i));
				greenTop[i]->setValue((int)s->getLedSide(SIDE_TOP)->greenPercent(i));
				blueTop [i]->setValue((int)s->getLedSide(SIDE_TOP)->bluePercent (i));
			}
			ui.spinBoxTopWhite->setValue((int)s->getLedSide(SIDE_TOP)->whitePercent());
			break;
		case LIGHT_TYPE_SAME: break;
	}

	switch(s->getLedSide(SIDE_BOT)->getLightType())
	{
		case LIGHT_TYPE_NOCHANGE: break;
		case LIGHT_TYPE_RANDOM  :
			g = s->getRanGen(SIDE_BOT);
			if(g!=NULL)
			{
				ui.comboBoxRandom2Colors->setCurrentIndex(g->whatColors());
				ui.spinBoxRandom2Dim	->setValue(g->getDimmingFactor ());
				ui.checkBoxRandom2Red   ->setChecked(g->useRed		());
				ui.checkBoxRandom2Green ->setChecked(g->useGreen	());
				ui.checkBoxRandom2Blue  ->setChecked(g->useBlue		());
				ui.checkBoxRandom2White ->setChecked(g->useWhite	());
				ui.checkBoxRandom2Same  ->setChecked(g->useSameColor());
			}
			break;
		case LIGHT_TYPE_MANUAL:
			for(int i=0;i<3;i++)
			{
				redBot  [i]->setValue((int)s->getLedSide(SIDE_BOT)->redPercent  (i));
				greenBot[i]->setValue((int)s->getLedSide(SIDE_BOT)->greenPercent(i));
				blueBot [i]->setValue((int)s->getLedSide(SIDE_BOT)->bluePercent (i));
			}
			ui.spinBoxBotWhite->setValue((int)s->getLedSide(SIDE_BOT)->whitePercent());
			break;
		case LIGHT_TYPE_SAME: break;
	}
	
	ui.lineEditStepName->setText(s->getTitle());

	if(step<seqTable->rowCount()-1 && seqTable->rowCount()>1) ui.pushButtonStepDown->setDisabled(false);
	if(step>0					   && seqTable->rowCount()>1) ui.pushButtonStepUp  ->setDisabled(false);	
	ui.pushButtonStepRemove->setDisabled(false);
}

void Tripod_Lamp_GUI::removeStep()
{
	seqTable->removeStep();
	if(seqTable->rowCount()==0)
	{
		ui.pushButtonRunSeqBeg->setDisabled(true);
		ui.pushButtonRunSeqSel->setDisabled(true);
		setDefaultView();
		ui.groupBoxStep->setDisabled(true);
	}
}

void Tripod_Lamp_GUI::loadSequence()
{
	seqTable->loadFromFile();
	ui.tabWidget->setCurrentPage(2);
}

void Tripod_Lamp_GUI::setDefaultView()
{
	ui.groupBoxStep->setTitle(tr("Step options"));
	
	// General setting elements
	ui.comboBoxTopSel->setCurrentIndex(0);
	ui.comboBoxBotSel->setCurrentIndex(0);
	ui.timeEditToNextStep->setTime(QTime(0, 0, 1));
	ui.checkBoxFadeLight->setChecked(false);

	ui.lineEditStepName	   ->setText("");
	ui.pushButtonStepUp	   ->setDisabled(true);
	ui.pushButtonStepDown  ->setDisabled(true);
	ui.pushButtonStepRemove->setDisabled(true);

	// Random setting elements
	ui.comboBoxRandom1Colors->setCurrentIndex(0); 
	ui.checkBoxRandom1Red	->setChecked(true );
	ui.checkBoxRandom1Green ->setChecked(true );
	ui.checkBoxRandom1Blue  ->setChecked(true );
	ui.checkBoxRandom1White ->setChecked(false);
	ui.checkBoxRandom1Same  ->setChecked(false);

	ui.comboBoxRandom2Colors->setCurrentIndex(0); 
	ui.checkBoxRandom2Red	->setChecked(true );
	ui.checkBoxRandom2Green ->setChecked(true );
	ui.checkBoxRandom2Blue  ->setChecked(true );
	ui.checkBoxRandom2White ->setChecked(false);
	ui.checkBoxRandom2Same  ->setChecked(false);

	// Manual setting elements
	for(int i=0;i<3;i++)
	{
		redTop[i]->setValue(0); greenTop[i]->setValue(0); blueTop[i]->setValue(0);
		redBot[i]->setValue(0); greenBot[i]->setValue(0); blueBot[i]->setValue(0);
	}
	ui.spinBoxTopWhite->setValue(0);
	ui.spinBoxBotWhite->setValue(0);
}

//==================================================================================

void Tripod_Lamp_GUI::runSequenceBegin()
{
	rsf->setStartStep(0);
	rsf->show();
	rsf->activateTimer();
}

void Tripod_Lamp_GUI::runSequenceStep()
{
	rsf->setStartStep(seqTable->currentRow());
	rsf->show();
	rsf->activateTimer();
}

void Tripod_Lamp_GUI::doSequenceStep(unsigned int step)
{	
	if(step<seqTable->stepCount())
	{
		QTime t = QTime::currentTime();
		dbp->print(t.toString("HH:mm:ss")+": Doing seqeunce step: "+QString::number(step));
		cmg->doSequenceStep(seqTable->sequenceStep(step));
	}
}