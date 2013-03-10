#include "tripod_lamp_gui.h"

void Tripod_Lamp_GUI::setUpSequenceTable()
{
	seqTable = new SequenceTable(ui.verticalLayoutWidget);
	ui.vLayoutSeqTable->addWidget(seqTable);
	seqTable->setVisible(true);

	QObject::connect(seqTable			  , SIGNAL(loadStep (unsigned int)), this	 , SLOT(loadStep	(unsigned int)));
	QObject::connect(ui.menuLoadSequence  , SIGNAL(triggered(			 )), this	 , SLOT(loadSequence(			 )));
	QObject::connect(ui.menuSaveSequence  , SIGNAL(triggered(			 )), seqTable, SLOT(saveToFile	(			 )));
	QObject::connect(ui.pushButtonAddStep , SIGNAL(clicked  (			 )), this	 , SLOT(addStep	    (			 )));
	QObject::connect(ui.pushButtonStepUp  , SIGNAL(clicked  (			 )), seqTable, SLOT(moveStepUp  (			 )));
	QObject::connect(ui.pushButtonStepDown, SIGNAL(clicked  (			 )), seqTable, SLOT(moveStepDown(			 )));
}