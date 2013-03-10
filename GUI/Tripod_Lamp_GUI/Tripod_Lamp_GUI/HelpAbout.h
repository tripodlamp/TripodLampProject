#ifndef HELPABOUT_H
#define HELPABOUT_H

#include <QDialog>
#include <QtGui/QMainWindow>
#include "ui_FormAbout.h"

class HelpAbout : public QDialog
{
	Q_OBJECT

private:
	Ui::FormAbout ui;

public:
	HelpAbout(QWidget *parent = 0, Qt::WFlags flags = 0);
	~HelpAbout();

public slots:
	void showHelpAbout();
	void hideHelpAbout();
};

#endif // HELPABOUT_H