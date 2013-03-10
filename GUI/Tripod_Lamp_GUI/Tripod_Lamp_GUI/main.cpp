#include "tripod_lamp_gui.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Tripod_Lamp_GUI w;
	w.show();
	return a.exec();
}
