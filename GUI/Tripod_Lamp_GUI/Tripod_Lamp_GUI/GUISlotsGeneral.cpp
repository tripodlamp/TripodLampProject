#include "tripod_lamp_gui.h"

void Tripod_Lamp_GUI::trayIconClicked(QSystemTrayIcon::ActivationReason reason)
{
	if(reason==QSystemTrayIcon::DoubleClick)
        showHideWindow();
}

void Tripod_Lamp_GUI::showHideWindow()
{
	if(this->isVisible())
    {
		this->hide();
		showHideTray->setIcon(QIcon(":/Tripod_Lamp_GUI/Icons/arrow_up.png"));
		showHideTray->setText("Show Main Window");
    }
    else
    {
		this->show();
		showHideTray->setIcon(QIcon(":/Tripod_Lamp_GUI/Icons/arrow_down.png"));
		showHideTray->setText("Hide Main Window");
    }
}

void Tripod_Lamp_GUI::menuExit()
{
	exit(0);
}

void Tripod_Lamp_GUI::changeConnection()
{
	if(ui.pushButtonConnect->text()=="Connect")
		doConnect(port, baud);
	else
		doDisconnect();
}

void Tripod_Lamp_GUI::showSerialPortSettings()
{
	sps->setSettingValues(port, baud);
	sps->show();
}

void Tripod_Lamp_GUI::saveSerialPortSettings()
{
	port = sps->getPort();
	baud = sps->getBaud();
	sps->close();
	updateSerialPortSettings();
}

// =============================================================================
// Private methode after this line

void Tripod_Lamp_GUI::setSilderMaxValues()
{
	ui.verticalSliderRed  ->setMaxValue(MAX_LED_VALUE);
	ui.verticalSliderGreen->setMaxValue(MAX_LED_VALUE);
	ui.verticalSliderBlue ->setMaxValue(MAX_LED_VALUE);
	ui.verticalSliderWhite->setMaxValue(MAX_LED_VALUE);
	ui.verticalSliderColor->setMaxValue(MAX_LED_VALUE);
}

void Tripod_Lamp_GUI::updateSerialPortSettings()
{
	port = sps->getPort();
	baud = sps->getBaud();
	ui.labelPort->setText("COM-Port: "+QString::number(port));
	ui.labelBaud->setText("Baudrate: "+QString::number(baud));
}

// =============================================================================
// Public slots after this line

void Tripod_Lamp_GUI::actionWhenConnected()
{
	// Menu elements
	ui.menuConnect->setText("Disconnect");
	ui.menuConnect->setIcon(QIcon(":/Tripod_Lamp_GUI/Icons/disconnect.png"));
	ui.labelConnectionStatusText->setText("<font color='#00BB00'>Connected</font>");
	ui.labelConnectionStatusIcon->setText("<img src=\":/Tripod_Lamp_GUI/Icons/connect.png\">");

	// General GUI elements
	ui.pushButtonConnect	  ->setText("Disconnect");
	ui.pushButtonSetDefault	  ->setDisabled(false);
	ui.pushButtonAllLedsOff	  ->setDisabled(false);
	ui.pushButtonSwitchFade	  ->setDisabled(false);
	if(seqTable->stepCount()>0) ui.pushButtonRunSeqBeg->setDisabled(false);
	if(seqTable->stepCount()>0) ui.pushButtonRunSeqSel->setDisabled(false);
		
	// Set Color Tab elements
	ui.verticalSliderRed	  ->setDisabled(false);
	ui.verticalSliderGreen	  ->setDisabled(false);
	ui.verticalSliderBlue	  ->setDisabled(false);
	ui.verticalSliderWhite	  ->setDisabled(false);
	ui.comboBoxSide			  ->setDisabled(false);
	cl						  ->setDisabled(false);
	ui.pushButtonResetSettings->setDisabled(false);
	ui.labelColorWheel		  ->setDisabled(false);
	ui.checkBoxLinkSliders	  ->setDisabled(false);
	ui.pushButtonIncreaseLED  ->setDisabled(false);
	ui.pushButtonDecreaseLED  ->setDisabled(false);

	// Set LED elements
	ui.comboBoxBranch		  ->setDisabled(false);
	ui.comboBoxLEDSide		  ->setDisabled(false);
	ui.comboBoxColor		  ->setDisabled(false);
	ui.verticalSliderColor	  ->setDisabled(false);
}

void Tripod_Lamp_GUI::actionWhenDisconnected()
{
	// Menu elements
	ui.menuConnect->setText("Connect");
	ui.menuConnect->setIcon(QIcon(":/Tripod_Lamp_GUI/Icons/connect.png"));
	ui.labelConnectionStatusText->setText("<font color='#FF0000'>Disconnected</font>");
	ui.labelConnectionStatusIcon->setText("<img src=\":/Tripod_Lamp_GUI/Icons/disconnect.png\">");

	// General GUI elements
	ui.pushButtonConnect	  ->setText("Connect");
	ui.pushButtonSetDefault	  ->setDisabled(true);
	ui.pushButtonAllLedsOff	  ->setDisabled(true);
	ui.pushButtonSwitchFade	  ->setDisabled(true);
	ui.pushButtonRunSeqBeg	  ->setDisabled(true);
	ui.pushButtonRunSeqSel    ->setDisabled(true);
	
	// Set Color Tab elements
	ui.verticalSliderRed	  ->setDisabled(true);
	ui.verticalSliderGreen	  ->setDisabled(true);
	ui.verticalSliderBlue	  ->setDisabled(true);
	ui.verticalSliderWhite	  ->setDisabled(true);
	ui.comboBoxSide			  ->setDisabled(true);
	cl						  ->setDisabled(true);
	ui.pushButtonResetSettings->setDisabled(true);
	ui.labelColorWheel		  ->setDisabled(true);
	ui.checkBoxLinkSliders	  ->setDisabled(true);

	// Set LED elements
	ui.comboBoxBranch		  ->setDisabled(true);
	ui.comboBoxLEDSide		  ->setDisabled(true);
	ui.comboBoxColor		  ->setDisabled(true);
	ui.verticalSliderColor	  ->setDisabled(true);
	ui.pushButtonIncreaseLED  ->setDisabled(true);
	ui.pushButtonDecreaseLED  ->setDisabled(true);

	if(colorWheelPainter!=NULL) { delete(colorWheelPainter); colorWheelPainter = NULL; }
	if(colorWheelPixmap !=NULL) { delete(colorWheelPixmap ); colorWheelPixmap  = NULL; }
}

void Tripod_Lamp_GUI::actionWhenConnectionFails()
{
	ui.labelConnectionStatusText->setText("<font color='#FF0000'>Connection failed</font>");
	ui.labelConnectionStatusIcon->setText("<img src=\":/Tripod_Lamp_GUI/Icons/disconnect.png\">");
}

void Tripod_Lamp_GUI::initSequenceTab()
{
	ui.groupBoxStep->setDisabled(true);

	redTop[0] = ui.spinBoxTopRed1; greenTop[0] = ui.spinBoxTopGreen1; blueTop[0] = ui.spinBoxTopBlue1;
	redTop[1] = ui.spinBoxTopRed2; greenTop[1] = ui.spinBoxTopGreen2; blueTop[1] = ui.spinBoxTopBlue2;
	redTop[2] = ui.spinBoxTopRed3; greenTop[2] = ui.spinBoxTopGreen3; blueTop[2] = ui.spinBoxTopBlue3;

	redBot[0] = ui.spinBoxBotRed1; greenBot[0] = ui.spinBoxBotGreen1; blueBot[0] = ui.spinBoxBotBlue1;
	redBot[1] = ui.spinBoxBotRed2; greenBot[1] = ui.spinBoxBotGreen2; blueBot[1] = ui.spinBoxBotBlue2;
	redBot[2] = ui.spinBoxBotRed3; greenBot[2] = ui.spinBoxBotGreen3; blueBot[2] = ui.spinBoxBotBlue3;

	rsf->setSequence(seqTable);
}