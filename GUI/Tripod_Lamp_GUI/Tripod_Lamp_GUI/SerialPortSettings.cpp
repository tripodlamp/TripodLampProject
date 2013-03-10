#include "SerialPortSettings.h"

SerialPortSettings::SerialPortSettings(QWidget *parent, Qt::WFlags flags)
{
	ui.setupUi(this);
	this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
	this->setModal(true);

	QObject::connect(ui.pushButtonCancel, SIGNAL(clicked()), this, SLOT(closeDialog()));
	QObject::connect(ui.pushButtonOK	, SIGNAL(clicked()), this, SLOT(saveDialog ()));
}

SerialPortSettings::~SerialPortSettings() { }

void SerialPortSettings::setSettingValues(int port, int baud)
{
	ui.comboBoxPort->setCurrentIndex(ui.comboBoxPort->findText(QString::number(port)));
	ui.comboBoxBaud->setCurrentIndex(ui.comboBoxBaud->findText(QString::number(baud)));
}

int SerialPortSettings::getPort() { return ui.comboBoxPort->currentText().toInt(); }
int SerialPortSettings::getBaud() { return ui.comboBoxBaud->currentText().toInt(); }

void SerialPortSettings::closeDialog() { this->close (); }
void SerialPortSettings::saveDialog () { closeAndSave(); }