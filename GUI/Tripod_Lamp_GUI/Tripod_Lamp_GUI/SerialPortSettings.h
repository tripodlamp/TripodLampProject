#ifndef SERIALPORTSETTINGS_H
#define SERIALPORTSETTINGS_H

#include <QDialog>
#include <QtGui/QMainWindow>
#include "ui_FormSerialPortSettings.h"

class SerialPortSettings : public QDialog
{
	Q_OBJECT

public:
	SerialPortSettings(QWidget *parent = 0, Qt::WFlags flags = 0);
	~SerialPortSettings();

	void setSettingValues(int port, int baud);

	int  getPort();
	int  getBaud();

private:
	Ui::FormSerialPortSettings ui;

public slots:
	void closeDialog();
	void saveDialog ();

signals:
	void closeAndSave();


};

#endif // SERIALPORTSETTINGS_H