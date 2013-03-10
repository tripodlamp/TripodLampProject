#ifndef DEBUGPRINT_H
#define DEBUGPRINT_H

#include <QFont>
#include <QDialog>
#include <QScrollBar>
#include <QTextCharFormat>
#include <QtGui/QMainWindow>
#include "ui_FormDebugPrint.h"

class DebugPrint : public QDialog
{
	Q_OBJECT

public:
	DebugPrint(QWidget *parent = 0, Qt::WFlags flags = 0);
	~DebugPrint();

private:
	Ui::FormDebugPrint ui;

	unsigned int lineCounter;
	QTextCharFormat f;

public slots:
	void clearText();
	void print(QString t);
};

#endif // DEBUGPRINT_H