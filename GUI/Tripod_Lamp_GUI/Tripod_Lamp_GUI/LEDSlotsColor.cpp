#include "tripod_lamp_gui.h"

void Tripod_Lamp_GUI::setAllColors(int red, int green, int blue)
{
	bool sideCondition = !(ui.comboBoxSide->currentText()=="Both");
	char side = SIDE_UP;
	if(ui.comboBoxSide->currentText()=="Bottom") { side = SIDE_BOTTOM; }
	cmg->setAllColors((char)red, (char)green, (char)blue, sideCondition, side);		// setup own function in this thread
	updateColorSliderLabels();
}

void Tripod_Lamp_GUI::setRedColor(int colorValue)
{
	if(setAllColorsMode) return;
	if(ui.checkBoxLinkSliders->isChecked())
	{
		ui.verticalSliderGreen->setValue(colorValue);
		ui.verticalSliderBlue ->setValue(colorValue);
	}
	setAllColors(ui.verticalSliderRed->value(), ui.verticalSliderGreen->value(), ui.verticalSliderBlue->value());
	updateColorSliderLabels();
}

void Tripod_Lamp_GUI::setGreenColor(int colorValue)
{
	if(setAllColorsMode) return;
	if(ui.checkBoxLinkSliders->isChecked())
	{
		ui.verticalSliderRed ->setValue(colorValue);
		ui.verticalSliderBlue->setValue(colorValue);
	}
	setAllColors(ui.verticalSliderRed->value(), ui.verticalSliderGreen->value(), ui.verticalSliderBlue->value());
	updateColorSliderLabels();
}

void Tripod_Lamp_GUI::setBlueColor(int colorValue)
{
	if(setAllColorsMode) return;
	if(ui.checkBoxLinkSliders->isChecked())
	{
		ui.verticalSliderRed  ->setValue(colorValue);
		ui.verticalSliderGreen->setValue(colorValue);
	}
	setAllColors(ui.verticalSliderRed->value(), ui.verticalSliderGreen->value(), ui.verticalSliderBlue->value());
	updateColorSliderLabels();
}

void Tripod_Lamp_GUI::setWhiteColor(int colorValue)
{
	if(setAllColorsMode) return;
	bool sideCondition = !(ui.comboBoxSide->currentText()=="Both");
	char side = SIDE_UP;
	if(ui.comboBoxSide->currentText()=="Bottom") { side = SIDE_BOTTOM; }
	cmg->setWhite((char)colorValue, sideCondition, side);				// setup own function in this thread
	updateColorSliderLabels();
}

void Tripod_Lamp_GUI::resetColorSettings()
{
	setAllColorsMode = true;
	ui.verticalSliderRed  ->setValue(0);
	ui.verticalSliderGreen->setValue(0);
	ui.verticalSliderBlue ->setValue(0);
	ui.verticalSliderWhite->setValue(0);
	ui.comboBoxSide->setCurrentIndex(0);
	updateColorSliderLabels();

	if(colorWheelPainter!=NULL) { delete(colorWheelPainter); colorWheelPainter = NULL; }
	if(colorWheelPixmap !=NULL) { delete(colorWheelPixmap ); colorWheelPixmap  = NULL; }
	setAllColorsMode = false;
}

void Tripod_Lamp_GUI::setColorSlider()
{
	unsigned int value_red, value_green, value_blue, value_white;
	char side = SIDE_UP;
	if(ui.comboBoxSide->currentText()=="Bottom") { side = SIDE_BOTTOM; }
	value_red	= lst->getRed  (side, 0);
	value_green = lst->getGreen(side, 0);
	value_blue	= lst->getBlue (side, 0);
	value_white = lst->getWhite(side   );
	ui.verticalSliderRed  ->setValue(value_red  );
	ui.verticalSliderGreen->setValue(value_green);
	ui.verticalSliderBlue ->setValue(value_blue );
	ui.verticalSliderWhite->setValue(value_white);
}

void Tripod_Lamp_GUI::updateColorSliderLabels()
{
	ui.labelRedValue  ->setText(QString::number(ui.verticalSliderRed  ->value()*100/ui.verticalSliderRed  ->maximum())+"%");
	ui.labelGreenValue->setText(QString::number(ui.verticalSliderGreen->value()*100/ui.verticalSliderGreen->maximum())+"%");
	ui.labelBlueValue ->setText(QString::number(ui.verticalSliderBlue ->value()*100/ui.verticalSliderBlue ->maximum())+"%");
	ui.labelWhiteValue->setText(QString::number(ui.verticalSliderWhite->value()*100/ui.verticalSliderWhite->maximum())+"%");
}

void Tripod_Lamp_GUI::ClickLabelClickEvent(int x, int y)
{
	float r, phi;
	int red, green, blue, dist_red, dist_green, dist_blue;
	int r_max = 85;

	x-=100; y=100-y;								// Set x and y relative to center of the circle
	r = sqrt(pow((float)x, 2) + pow((float)y, 2));	// Calculate radius

	// Calculate angle
	if(r== 0) { phi = PI/2 ; } else if(y>=0) { phi = acos((float)(x/r)); } else { phi = 2*PI-acos((float)(x/r)); }
	if(phi<0) { phi+=(2*PI); }

	phi*=(360/(2*PI));	// Transform angle-value to degree

	if(phi<ANGLE_RED || phi>=ANGLE_BLUE)
	{
		if(phi<=ANGLE_RED)
		{
			dist_red  = ANGLE_RED - phi;
			dist_blue = phi + 360 - ANGLE_BLUE;
		}
		else
		{
			dist_red  = ANGLE_RED + (360 - phi);
			dist_blue = phi - ANGLE_BLUE;
		}
		dist_green = 120;
	}
	else if(phi>=ANGLE_RED && phi<ANGLE_GREEN)
	{
		dist_red   = phi - ANGLE_RED;
		dist_green = ANGLE_GREEN - phi;
		dist_blue  = 120;
	}
	else
	{
		dist_red   = 120;
		dist_green = phi - ANGLE_GREEN;
		dist_blue  = ANGLE_BLUE - phi;
	}
	if(r>r_max) { r = r_max; }

	if(dist_red  <60) { dist_red   = 0; } else { dist_red  -=60; }
	if(dist_green<60) { dist_green = 0; } else { dist_green-=60; }
	if(dist_blue <60) { dist_blue  = 0; } else { dist_blue -=60; }
	red   = (int)(r/r_max * MAX_LED_VALUE * (60-dist_red  )/60);
	green = (int)(r/r_max * MAX_LED_VALUE * (60-dist_green)/60);
	blue  = (int)(r/r_max * MAX_LED_VALUE * (60-dist_blue )/60);
	setAllColorsMode = true;
	ui.verticalSliderRed  ->setValue(red  );
	ui.verticalSliderGreen->setValue(green);
	ui.verticalSliderBlue ->setValue(blue );
	setAllColors(red, green, blue);
	setAllColorsMode = false;

	// Set point on Color Wheel Label
	if(colorWheelPainter!=NULL) { delete(colorWheelPainter); colorWheelPainter = NULL; }
	if(colorWheelPixmap !=NULL) { delete(colorWheelPixmap ); colorWheelPixmap  = NULL; }
	colorWheelPixmap = new QPixmap(200, 200);
	colorWheelPixmap->fill(QColor("transparent")); 
	colorWheelPainter = new QPainter(colorWheelPixmap);
	colorWheelPainter->setBrush(QBrush(Qt::black));
	colorWheelPainter->drawArc(r*cos(phi*PI/180)+100-2, 100-r*sin(phi*PI/180)-2, 5, 5, 0, 17*360);
	ui.labelColorWheelPaint->setPixmap(*colorWheelPixmap);
}