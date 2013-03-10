#include "DebugPrint.h"

DebugPrint::DebugPrint(QWidget *parent, Qt::WFlags flags) : QDialog(parent)
{
	ui.setupUi(this);
	this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

	QObject::connect(ui.pushButtonClear, SIGNAL(clicked()), this, SLOT(clearText()));

	lineCounter = 0;
	f.setFont(QFont("Courier New", 10));
}

DebugPrint::~DebugPrint() { }

void DebugPrint::clearText() { ui.plainTextEditDebug->clear(); lineCounter = 0; }

void DebugPrint::print(QString t)
{
	if(this->isVisible())
	{
		ui.plainTextEditDebug->textCursor().insertText(QString::number(++lineCounter)+": "+t+"\n", f);
		ui.plainTextEditDebug->verticalScrollBar()->setValue(ui.plainTextEditDebug->verticalScrollBar()->maximum());
	}
}