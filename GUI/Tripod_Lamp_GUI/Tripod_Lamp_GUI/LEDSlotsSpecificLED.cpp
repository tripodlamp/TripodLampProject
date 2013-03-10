#include "tripod_lamp_gui.h"

void Tripod_Lamp_GUI::setSpecificLED(int colorValue)
{
	char color = COLOR_RED_SW;
	char side  = SIDE_UP;
	if(ui.comboBoxColor->currentText  ()=="Green" ) { color = COLOR_GREEN_SW; } else
	if(ui.comboBoxColor->currentText  ()=="Blue"  ) { color = COLOR_BLUE_SW ; } else
	if(ui.comboBoxColor->currentText  ()=="White" ) { color = COLOR_WHITE_SW; }
	if(ui.comboBoxLEDSide->currentText()=="Bottom") { side  = SIDE_BOTTOM   ; }
	cmg->setLED(color, colorValue, side, ui.comboBoxBranch->currentIndex());

	updateLEDSilderLabel();
}

void Tripod_Lamp_GUI::updateLEDSilderLabel() { ui.labelColorValue->setText(QString::number(ui.verticalSliderColor->value()*100/ui.verticalSliderColor->maximum())+"%"); }
void Tripod_Lamp_GUI::setSpecificLEDSlider() { ui.verticalSliderColor->setValue(getSpecificLEDValue()); }

void Tripod_Lamp_GUI::increaseSpecificLED()
{
	unsigned char value = getSpecificLEDValue();
	if(value<0xFF) setSpecificLED(value+1);
	setSpecificLEDSlider();
}

void Tripod_Lamp_GUI::decreaseSpecificLED()
{
	unsigned char value = getSpecificLEDValue();
	if(value>0x00) setSpecificLED(value-1);
	setSpecificLEDSlider();
}

void Tripod_Lamp_GUI::updateColorLabels()
{
	// Red
	ui.labelB1RedTop   ->setText(QString::number(lst->getRed(SIDE_UP	, 0)*100/MAX_LED_VALUE)+"%");
	ui.labelB2RedTop   ->setText(QString::number(lst->getRed(SIDE_UP	, 1)*100/MAX_LED_VALUE)+"%");
	ui.labelB3RedTop   ->setText(QString::number(lst->getRed(SIDE_UP	, 2)*100/MAX_LED_VALUE)+"%");
	ui.labelB1RedBottom->setText(QString::number(lst->getRed(SIDE_BOTTOM, 0)*100/MAX_LED_VALUE)+"%");
	ui.labelB2RedBottom->setText(QString::number(lst->getRed(SIDE_BOTTOM, 1)*100/MAX_LED_VALUE)+"%");
	ui.labelB3RedBottom->setText(QString::number(lst->getRed(SIDE_BOTTOM, 2)*100/MAX_LED_VALUE)+"%");

	// Green
	ui.labelB1GreenTop	 ->setText(QString::number(lst->getGreen(SIDE_UP	, 0)*100/MAX_LED_VALUE)+"%");
	ui.labelB2GreenTop	 ->setText(QString::number(lst->getGreen(SIDE_UP	, 1)*100/MAX_LED_VALUE)+"%");
	ui.labelB3GreenTop	 ->setText(QString::number(lst->getGreen(SIDE_UP	, 2)*100/MAX_LED_VALUE)+"%");
	ui.labelB1GreenBottom->setText(QString::number(lst->getGreen(SIDE_BOTTOM, 0)*100/MAX_LED_VALUE)+"%");
	ui.labelB2GreenBottom->setText(QString::number(lst->getGreen(SIDE_BOTTOM, 1)*100/MAX_LED_VALUE)+"%");
	ui.labelB3GreenBottom->setText(QString::number(lst->getGreen(SIDE_BOTTOM, 2)*100/MAX_LED_VALUE)+"%");

	// Blue
	ui.labelB1BlueTop	->setText(QString::number(lst->getBlue(SIDE_UP	  , 0)*100/MAX_LED_VALUE)+"%");
	ui.labelB2BlueTop	->setText(QString::number(lst->getBlue(SIDE_UP	  , 1)*100/MAX_LED_VALUE)+"%");
	ui.labelB3BlueTop	->setText(QString::number(lst->getBlue(SIDE_UP	  , 2)*100/MAX_LED_VALUE)+"%");
	ui.labelB1BlueBottom->setText(QString::number(lst->getBlue(SIDE_BOTTOM, 0)*100/MAX_LED_VALUE)+"%");
	ui.labelB2BlueBottom->setText(QString::number(lst->getBlue(SIDE_BOTTOM, 1)*100/MAX_LED_VALUE)+"%");
	ui.labelB3BlueBottom->setText(QString::number(lst->getBlue(SIDE_BOTTOM, 2)*100/MAX_LED_VALUE)+"%");

	// White
	ui.labelWhiteTop   ->setText(QString::number(lst->getWhite(SIDE_UP	  )*100/MAX_LED_VALUE)+"%");
	ui.labelWhiteBottom->setText(QString::number(lst->getWhite(SIDE_BOTTOM)*100/MAX_LED_VALUE)+"%");
}

unsigned char Tripod_Lamp_GUI::getSpecificLEDValue()
{
	unsigned char value = 0;
	char side  = SIDE_UP;
	char color = COLOR_RED_SW;
	if(ui.comboBoxLEDSide->currentText()=="Bottom") { side  = SIDE_BOTTOM   ; }
	if(ui.comboBoxColor	 ->currentText()=="Green" ) { color = COLOR_GREEN_SW; } else
	if(ui.comboBoxColor	 ->currentText()=="Blue"  ) { color = COLOR_BLUE_SW ; } else
	if(ui.comboBoxColor	 ->currentText()=="White" ) { color = COLOR_WHITE_SW; }
	switch(color)
	{
	case COLOR_RED_SW  : value = lst->getRed  (side, ui.comboBoxBranch->currentIndex()); break;
	case COLOR_GREEN_SW: value = lst->getGreen(side, ui.comboBoxBranch->currentIndex()); break;
	case COLOR_BLUE_SW : value = lst->getBlue (side, ui.comboBoxBranch->currentIndex()); break;
	case COLOR_WHITE_SW: value = lst->getWhite(side									  ); break;
	default: break;
	}
	return value;
}