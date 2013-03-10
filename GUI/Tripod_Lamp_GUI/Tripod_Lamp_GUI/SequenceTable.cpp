#include "SequenceTable.h"

// ================= Private methods =================

void SequenceTable::redrawTable()
{
	this->clearTable();

	unsigned int row;
	for(unsigned int i=0;i<steps->size();i++)
	{
		row = this->rowCount();
		this->setRowCount(row+1);
		this->setItem(row, 0, steps->at(i)->getItem());
	}
}

void SequenceTable::clearTable()
{
	for(unsigned int i=0;i<this->rowCount();i++) { this->takeItem(i, 0); }
	this->clearSelection();
	this->setRowCount(0);
}

// ================= Constructor / Destructor =================

SequenceTable::SequenceTable(QWidget *parent) : QTableWidget(parent)
{
	this->setColumnCount(1);
	this->setRowCount(0);

	this->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	this->setEditTriggers (QAbstractItemView::NoEditTriggers );
    this->setSelectionMode(QAbstractItemView::SingleSelection);
	this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->setShowGrid(false);
    this->setWordWrap(false);
	this->setGridStyle(Qt::DashLine);
    this->setCornerButtonEnabled(false);

	this->horizontalHeader()->setStretchLastSection(true);
	this->horizontalHeader()->setVisible(false);
	this->verticalHeader  ()->setDefaultSectionSize(20);
    this->verticalHeader  ()->setMinimumSectionSize(20);
	this->verticalHeader  ()->setHighlightSections (false);
    this->verticalHeader  ()->setStretchLastSection(false);
	this->verticalHeader  ()->setResizeMode(QHeaderView::Fixed);

	QPalette* palette = new QPalette();
	palette->setColor(QPalette::Highlight, QColor(51, 153, 255));
	this->setPalette(*palette);  

	lastClickedRow = -1;
	stepCounter	   =  1;

	steps = new vector<SequenceStep*>;

	QObject::connect(this, SIGNAL(cellClicked(int,  int)), this, SLOT(tableClicked(int, int)));
}

SequenceTable::~SequenceTable()
{
	for(unsigned int i=0;i<steps->size();i++) { delete(steps->at(i)); }
	delete(steps); steps = NULL;
}

// ================= Public methods =================

void SequenceTable::removeStep()
{
	if(lastClickedRow!=-1)
	{
		if((unsigned)lastClickedRow<steps->size())
		{
			this->takeItem(lastClickedRow, 0);
			delete(steps->at(lastClickedRow));
			steps->erase(steps->begin()+lastClickedRow);

			redrawTable();
			if(steps->size()==0) { stepCounter = 1; }
			if(lastClickedRow==steps->size()) { lastClickedRow--; }
			tableClicked(lastClickedRow, 0);
		}
	}
}

void SequenceTable::removeAllSteps()
{
	this->clearTable();
	lastClickedRow = -1;
	for(unsigned int i=0;i<steps->size();i++) { delete(steps->at(i)); }
	steps->clear();
}

unsigned int SequenceTable::stepCount() { return steps->size(); }

SequenceStep* SequenceTable::sequenceStep()
{
	if(lastClickedRow!=-1)
		return sequenceStep((unsigned)lastClickedRow);

	return NULL;
}

SequenceStep* SequenceTable::sequenceStep(unsigned int step)
{
	if(step<steps->size())
		return steps->at(step);

	return NULL;
}

// ================= Public slots =================

void SequenceTable::addStep()
{
	steps->push_back(new SequenceStep("Step "+QString::number(stepCounter++)));
	redrawTable();
	tableClicked(steps->size()-1, 0);
}

void SequenceTable::moveStepUp()
{
	if(lastClickedRow==-1 || lastClickedRow==0) return;
	SequenceStep *s = steps->at(lastClickedRow);
	steps->erase(steps->begin()+lastClickedRow);
	lastClickedRow--;
	steps->insert(steps->begin()+lastClickedRow, s);
	redrawTable();
	tableClicked(lastClickedRow, 0);
}

void SequenceTable::moveStepDown()
{
	if(lastClickedRow==-1 || lastClickedRow==steps->size()-1) return;
	SequenceStep *s = steps->at(lastClickedRow);
	steps->erase(steps->begin()+lastClickedRow);
	lastClickedRow++;
	steps->insert(steps->begin()+lastClickedRow, s);
	redrawTable();
	tableClicked(lastClickedRow, 0);
}

void SequenceTable::loadFromFile()
{
	QMessageBox  msgBox;
	QString		 fileString, header, body, title;
	QTime		 timeUntilNext;
	bool		 doFade;
	unsigned int lightType[2], stepsSkipped;
	QStringList  stepList, stepPartList, headerList, ledSideList, ledSide[2];

	if(stepCount()>0)
	{
		int ret = QMessageBox::warning(this, tr("Load sequence form file"), tr("Discard the actual sequence?"), QMessageBox::Yes | QMessageBox::Cancel);
		if(ret==QMessageBox::Yes)
			removeAllSteps();
		else
			return;
	}

	QString fileName = QFileDialog::getOpenFileName(this, tr("Load sequence"), "", tr("Tripod Lamp Sequence (*.tls)"));
	SequenceStep *s;

	QFile file(fileName);
    if(file.open(QIODevice::ReadOnly))
    {
       QTextStream in(&file);
	   // Read in the whole data series file into one string
       while(!in.atEnd()) fileString.append(in.readLine());
    }
	else
	{
		msgBox.setIcon(QMessageBox::Critical);
		msgBox.setText("Couldn't open file '"+fileName+"'");
		msgBox.exec();
		return;
	}
	file.close();

	stepsSkipped = 0;

	stepList = fileString.split(SEP_STEP);
	for(unsigned int i=0;i<stepList.size();i++)
	{
		stepPartList = stepList.at(i).split(SEP_HEADER_BLOCK);

		if(stepPartList.size()!=2) { stepsSkipped++; continue; }
		header = stepPartList.at(0);
		body   = stepPartList.at(1);

		headerList = header.split(SEP_HEADER_INFO);
		if(headerList.size()!=3) { stepsSkipped++; continue; } 
		title		  = headerList.at(0);
		timeUntilNext = QTime::fromString(headerList.at(1), TIME_FORMAT);
		doFade		  = (bool)headerList.at(2).toUInt();

		ledSideList = body.split(SEP_LED_SIDE);
		if(ledSideList.size()!=2) { stepsSkipped++; continue; }

		ledSide[SIDE_TOP] = ledSideList.at(SIDE_TOP).split(SEP_LED_SIDE_INFO);
		ledSide[SIDE_BOT] = ledSideList.at(SIDE_BOT).split(SEP_LED_SIDE_INFO);

		lightType[SIDE_TOP] = ledSide[SIDE_TOP].at(0).toUInt();
		lightType[SIDE_BOT] = ledSide[SIDE_BOT].at(0).toUInt();
		for(unsigned int j=0;j<2;j++) {
			switch(lightType[j]) {
				case LIGHT_TYPE_NOCHANGE: break;
				case LIGHT_TYPE_RANDOM	: if(ledSide[j].size()!= 8) { stepsSkipped++; continue; } break;
				case LIGHT_TYPE_MANUAL	: if(ledSide[j].size()!=11)	{ stepsSkipped++; continue; } break;
				case LIGHT_TYPE_SAME	: break;
			}
		}

		addStep(); // finally add the step to the sequence

		// Set values to just added step
		s = sequenceStep();
		s->setTitle			(title		  );
		s->setTimeToNextStep(timeUntilNext);
		s->setFadeLight		(doFade		  );
		s->getLedSide(SIDE_TOP)->setLightType(lightType[SIDE_TOP]);
		s->getLedSide(SIDE_BOT)->setLightType(lightType[SIDE_BOT]);
		for(unsigned int j=0;j<2;j++)
		{
			switch(s->getLedSide(j)->getLightType())
			{
			case LIGHT_TYPE_NOCHANGE: break;
			case LIGHT_TYPE_RANDOM  :
				s->addRandomGenerator(j, ledSide[j].at(1).toUInt(), ledSide[j].at(2).toUInt(), ledSide[j].at(3).toUInt(), ledSide[j].at(4).toUInt(), ledSide[j].at(5).toUInt(), ledSide[j].at(6).toUInt(), ledSide[j].at(7).toUInt());
				break;
			case LIGHT_TYPE_MANUAL:
				for(int k=0;k<3;k++) {
					s->getLedSide(j)->setRed  (i, (unsigned char)ledSide[j].at((k*3)+1).toUInt());
					s->getLedSide(j)->setGreen(i, (unsigned char)ledSide[j].at((k*3)+2).toUInt());
					s->getLedSide(j)->setBlue (i, (unsigned char)ledSide[j].at((k*3)+3).toUInt());
				}
				s->getLedSide(j)->setWhite((unsigned char)ledSide[j].at(10).toUInt());
				break;
			case LIGHT_TYPE_SAME: break;
			}
		}
	}
	if(stepsSkipped==0)
	{
		msgBox.setIcon(QMessageBox::Information);
		msgBox.setText("Sequence successfully loaded");
	}
	else
	{
		msgBox.setIcon(QMessageBox::Warning);
		msgBox.setText("Sequence successfully loaded...");
		msgBox.setInformativeText("...but "+QString::number(stepsSkipped)+" step(s) were skipped");
	}
	msgBox.exec();

	// Load first step
	tableClicked(0, 0);
}

void SequenceTable::saveToFile()
{
	QMessageBox msgBox;
	if(stepCount()==0)
	{
		msgBox.setIcon(QMessageBox::Information);
		msgBox.setText("No sequence to save available");
		msgBox.exec();
		return;
	}

	QString fileName = QFileDialog::getSaveFileName(this, tr("Save sequence"), "", tr("Tripod Lamp Sequence (*.tls)"));
	SequenceStep	*s;
	LedSide			*l;
	RandomGenerator *r;

	QFile file(fileName);
    if(file.open(QIODevice::ReadWrite))
	{
        QTextStream out(&file);
		for(unsigned int i=0;i<stepCount();i++)
		{
			s = steps->at(i);

			// Write general information to file
			out << s->getTitle() << SEP_HEADER_INFO << s->getTimeToNextStep().toString(TIME_FORMAT) << SEP_HEADER_INFO << (int)s->getFageLight() << SEP_HEADER_BLOCK << flush;
			// Now, do the both led sides (both are equal)
			for(unsigned int j=0;j<2;j++)
			{
				l = s->getLedSide(j);
				out << l->getLightType() << flush;	// Write the light-type-ID to the file
				switch(l->getLightType())
				{
				case LIGHT_TYPE_NOCHANGE: break; // No more information necessary...
				case LIGHT_TYPE_RANDOM:
					out << SEP_LED_SIDE_INFO << flush;
					r = l->getRanGen();
					out << r->whatColors	  () << SEP_LED_SIDE_INFO << flush;
					out << r->getDimmingFactor() << SEP_LED_SIDE_INFO << flush;
					out << r->useRed		  () << SEP_LED_SIDE_INFO << flush;
					out << r->useGreen		  () << SEP_LED_SIDE_INFO << flush;
					out << r->useBlue		  () << SEP_LED_SIDE_INFO << flush;
					out << r->useWhite		  () << SEP_LED_SIDE_INFO << flush;
					out << r->useSameColor	  () << flush; break;
				case LIGHT_TYPE_MANUAL:
					out << SEP_LED_SIDE_INFO << flush; // Write info seperator
					// Write the RGB-percent values of the three branches to the file
					for(int k=0;k<3;k++) {
						out << l->redPercent  (k) << SEP_LED_SIDE_INFO << flush;
						out << l->greenPercent(k) << SEP_LED_SIDE_INFO << flush;
						out << l->bluePercent (k) << SEP_LED_SIDE_INFO << flush;
					}
					// At the end, write the percent value of the white PWM to the file
					out << l->whitePercent() << flush; break;
				case LIGHT_TYPE_SAME: break; // No more informatio necessary...
				}

				if(j==0) { out << SEP_LED_SIDE << flush; }
			}
			if(i<stepCount()-1) { out << SEP_STEP << endl; }
		}
		msgBox.setIcon(QMessageBox::Information);
		msgBox.setText("Sequence successfully saved");
		msgBox.exec();
    }
	file.close();
}

// ================= Private slots =================

void SequenceTable::tableClicked(int row, int column)
{
	lastClickedRow = row;
	this->setCurrentIndex(this->model()->index(row, column));
	this->selectRow(row);
	if(row!=-1) loadStep(row);
}