#include "BufferLoadout.h"

void BufferLoadout::setValue(int value)
{
	ui.progressBar->setValue(value);
	ui.labelValue->setText(tr(QString::number(value)+" ("+QString::number((value/UART_CMD_BUFFER_SIZE*100))+"%)"));
}

BufferLoadout::BufferLoadout(unsigned int *getWritePointer, QWidget *parent, Qt::WFlags flags) : QDialog(parent)
{
	ui.setupUi(this);
	this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

	ui.progressBar->setMaximum(UART_CMD_BUFFER_SIZE);
	setValue(0);

	writePointer = getWritePointer;
}

BufferLoadout::~BufferLoadout() { }

void BufferLoadout::setLoadout(unsigned int readPointer)
{
	int value = 0;
	if(readPointer<=(*writePointer))
		value = (*writePointer) - readPointer;
	else
		value = ((*writePointer)+UART_CMD_BUFFER_SIZE) - readPointer;

	setValue(value);
}