#include "tripod_lamp_gui.h"

void Tripod_Lamp_GUI::showDebugPrint()
{
	dbp->move(this->geometry().x()+this->geometry().width()+7, 200);
	dbp->show();
}