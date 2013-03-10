#include "tripod_lamp_gui.h"

void Tripod_Lamp_GUI::setAllLEDsOff()
{
	cmg->setAllColors((char)0x00, (char)0x00, (char)0x00, false, SIDE_UP);
	resetColorSettings();
	ui.verticalSliderColor->setValue(0);
	cmg->setWhite((char)0x00, false, SIDE_UP);
}

void Tripod_Lamp_GUI::setDefault()
{
	cmg->setDefault();
	QFile file(DEFAULT_FILE);
	if(file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text))
	{
		QTextStream out(&file);
		for(unsigned int i=0;i<NUM_SIDES;i++) {
			for(unsigned int j=0;j<NUM_BRANCHES;j++) {
					out << lst->getRed  (i, j) << SEP_VALUE << flush;
					out << lst->getGreen(i, j) << SEP_VALUE << flush;
					out << lst->getBlue (i, j) << SEP_VALUE << flush;
			}
		}
		out << lst->getWhite(SIDE_TOP) << SEP_VALUE << lst->getWhite(SIDE_BOT) << endl;
	}
	file.close();
}

void Tripod_Lamp_GUI::getDefault()
{
	QString		fileString;
	QStringList values;
	unsigned int count = 0;

	QFile file(DEFAULT_FILE);
	if(file.open(QIODevice::ReadOnly))
	{
		QTextStream in(&file);
		// Read in the whole data series file into one string
		while(!in.atEnd()) fileString.append(in.readLine());
	}
	file.close();

	values = fileString.split(SEP_VALUE);
	if(values.size()!=20) return;

	for(unsigned int i=0;i<NUM_SIDES;i++) {
		for(unsigned int j=0;j<NUM_BRANCHES;j++) {
			cmg->setLED(COLOR_RED_SW  , (unsigned char) values.at(count++).toUInt(), i*SIDE_BOTTOM, j);
			cmg->setLED(COLOR_GREEN_SW, (unsigned char) values.at(count++).toUInt(), i*SIDE_BOTTOM, j);
			cmg->setLED(COLOR_BLUE_SW , (unsigned char) values.at(count++).toUInt(), i*SIDE_BOTTOM, j);
		}
	}
	cmg->setWhite((unsigned char) values.at(count++).toUInt(), true, SIDE_UP	);
	cmg->setWhite((unsigned char) values.at(count++).toUInt(), true, SIDE_BOTTOM);
}

void Tripod_Lamp_GUI::setFade()
{
	bool on = true;
	if(ui.pushButtonSwitchFade->text()=="Switch Fades on")
		ui.pushButtonSwitchFade->setText(tr("Switch Fades off"));
	else
	{
		ui.pushButtonSwitchFade->setText(tr("Switch Fades on"));
		on = false;
	}
	cmg->setFade(on);
}

void Tripod_Lamp_GUI::setColor(char color, char colorValue)
{
	switch(color)
	{
	case COLOR_RED_SW  : lst->setRed  (colorValue); break;
	case COLOR_GREEN_SW: lst->setGreen(colorValue); break;
	case COLOR_BLUE_SW : lst->setBlue (colorValue); break;
	case COLOR_WHITE_SW: lst->setWhite(colorValue); break;
	}
	updateColorLabels();
}

void Tripod_Lamp_GUI::setColor(char color, char colorValue, char side)
{
	switch(color)
	{
	case COLOR_RED_SW  : lst->setRed  (colorValue, side); break;
	case COLOR_GREEN_SW: lst->setGreen(colorValue, side); break;
	case COLOR_BLUE_SW : lst->setBlue (colorValue, side); break;
	case COLOR_WHITE_SW: lst->setWhite(colorValue, side); break;
	}
	updateColorLabels();
}

void Tripod_Lamp_GUI::setColor(char color, char colorValue, char side, int branch)
{
	switch(color)
	{
	case COLOR_RED_SW  : lst->setRed  (colorValue, side, branch); break;
	case COLOR_GREEN_SW: lst->setGreen(colorValue, side, branch); break;
	case COLOR_BLUE_SW : lst->setBlue (colorValue, side, branch); break;
	}
	updateColorLabels();
}