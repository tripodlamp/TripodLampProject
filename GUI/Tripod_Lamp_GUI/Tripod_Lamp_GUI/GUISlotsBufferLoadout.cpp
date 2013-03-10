#include "tripod_lamp_gui.h"

void Tripod_Lamp_GUI::showBufferLoadout()
{
	buf->move(this->geometry().x()-buf->geometry().width()-23, this->geometry().y()-30);
	buf->show();
}