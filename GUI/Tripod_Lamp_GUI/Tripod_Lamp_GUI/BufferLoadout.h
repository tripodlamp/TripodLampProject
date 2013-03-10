#ifndef BUFFERLOADOUT_H
#define BUFFERLOADOUT_H

#include <QDialog>
#include <QtGui/QMainWindow>
#include "ui_FormBufferLoadout.h"
#include "CommandDefs.h"

class BufferLoadout : public QDialog
{
	Q_OBJECT

private:
	Ui::FormBufferLoadout ui;

	unsigned int *writePointer;

	void setValue(int value);

public:
	BufferLoadout(unsigned int *getWritePointer, QWidget *parent = 0, Qt::WFlags flags = 0);
	~BufferLoadout();

public slots:
	void setLoadout(unsigned int readPointer);
};

#endif // BUFFERLOADOUT_H