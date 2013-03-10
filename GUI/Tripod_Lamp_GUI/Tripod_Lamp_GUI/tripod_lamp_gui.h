#ifndef TRIPOD_LAMP_GUI_H
#define TRIPOD_LAMP_GUI_H

#include <QFile>
#include <QList>
#include <QSlider>
#include <QPainter>
#include <QPointer>
#include <QScrollBar>
#include <QTextStream>
#include <QFileDialog>
#include <QMouseEvent>
#include <QListWidget>
#include <QMessageBox>
#include <QSystemTrayIcon>
#include <QtGui/QMainWindow>
#include <cmath>
#include <iostream>

// Network Libraries
//#include <qmobilityglobal.h> 
#include <QtNetwork> 
#include <QTcpServer>
#include <QNetworkSession> 

// Own object headers
#include "LEDState.h"
#include "TcpServer.h"
#include "HelpAbout.h"
#include "ClickLabel.h"
#include "DebugPrint.h"
#include "CommandGen.h"
#include "RunSequence.h"
#include "CommandCall.h"
#include "CommandLine.h"
#include "SequenceStep.h"
#include "SequenceTable.h"
#include "BufferLoadout.h"
#include "PresetComboBox.h"
#include "SerialPortSettings.h"
#include "ui_tripod_lamp_gui.h"

#define PI 3.14159265
#define ANGLE_RED		 90
#define ANGLE_GREEN		210
#define ANGLE_BLUE		330

#define DEFAULT_FILE	"default.tlr"

using namespace std;

class Tripod_Lamp_GUI : public QMainWindow
{
	Q_OBJECT

public:
	Tripod_Lamp_GUI(QWidget *parent = 0, Qt::WFlags flags = 0);
	~Tripod_Lamp_GUI();

private:
	Ui::Tripod_Lamp_GUIClass ui;
	SerialPortSettings		*sps;
	RunSequence				*rsf;
	DebugPrint				*dbp;
	BufferLoadout			*buf;
	HelpAbout				*hab;

	LedState				*lst;
	CommandGen				*cmg;
	CommandLine				*cmd;
	CommandCall				*cal;
	SequenceTable			*seqTable;
	PresetComboBox			*presetBox;

	TcpServer				*tcp;
	ClickLabel				*cl ;
	QPixmap					*colorWheelPixmap;
	QPainter				*colorWheelPainter;
	QSpinBox				*redTop[3], *greenTop[3], *blueTop[3];
	QSpinBox				*redBot[3], *greenBot[3], *blueBot[3];

	// Systray variables and methods
	QSystemTrayIcon *trayIcon;
    QMenu			*trayIconMenu;
    QAction			*showHideTray, *closeTray;

	int  port, baud;
	bool setAllColorsMode;
	
	void createTrayActions			 ();	// (tripod_lamp_gui.cpp)
    void createTrayIcon				 ();	// (tripod_lamp_gui.cpp)
    void setTrayIcon				 ();	// (tripod_lamp_gui.cpp)
	void closeEvent	   (QCloseEvent *e);	// (tripod_lamp_gui.cpp)
	void setSilderMaxValues			 ();	// (GUISlotsGeneral.cpp)
	void updateSerialPortSettings	 ();	// (GUISlotsGeneral.cpp)
	void updateColorSliderLabels	 ();	// (LEDSlotsColor.cpp)
	void updateLEDSilderLabel		 ();	// (LEDSlotsSpecificLED.cpp)
	void updateColorLabels			 ();	// (LEDSlotsSpecificLED.cpp)
	unsigned char getSpecificLEDValue();	// (LEDSlotsSpecificLED.cpp)
	void initSequenceTab			 ();	// (GUISlotsGeneral.cpp)
	void setDefaultView				 ();	// (GUISlotsSequence.cpp)

	// Private methods in LEDSlotsTCP.cpp
	void changeBranch    (char color, int changeValue, char side, int branch);
	char getColorValue   (char color, char side, int branch);
	char getNewColorValue(char colorValue, int changeValue );

private slots:
	void trayIconClicked(QSystemTrayIcon::ActivationReason reason);
    void showHideWindow	 ();
	void menuExit		 ();
	void changeConnection();

	void setAllColors (int red, int green, int blue);
	void setRedColor  (int colorValue);
	void setGreenColor(int colorValue);
	void setBlueColor (int colorValue);
	void setWhiteColor(int colorValue);
	void resetColorSettings();
	void setColorSlider();

	void setDefault	  ();
	void getDefault	  ();
	void setFade	  ();
	void setAllLEDsOff();

	void setSpecificLED(int colorValue);
	void setSpecificLEDSlider();
	void increaseSpecificLED();
	void decreaseSpecificLED();

	void showSerialPortSettings();
	void saveSerialPortSettings();

	void ClickLabelClickEvent(int x, int y);

	void setColor(char color, char colorValue);							// All LEDs
	void setColor(char color, char colorValue, char side);				// All LEDs on one side
	void setColor(char color, char colorValue, char side, int branch);	// A LED on one side on one branch

	// Sequence slots
	void showOptionsTop(int i);
	void showOptionsBot(int i);
	void addStep();
	void saveStep();
	void loadStep(unsigned int step);
	void removeStep();
	void loadSequence();

	// Running sequence form slots
	void runSequenceBegin();
	void runSequenceStep ();
	void doSequenceStep(unsigned int step);

	// Sequence Table Slots
	void setUpSequenceTable();

	// Preset Combo Box Slots
	void setUpPresetComboBox();
	void savePreset();
	void discardPreset();

	void setPresetColor(char color, char colorValue, char side, char branch);
	void setPresetWhite(char colorValue, char side);
	void setPresetName (QString name);

	// LED Slots for TCP Commands
	void changeLEDs(char color, int changeValue, char side, int branch);

	// Slots for Debug Print
	void showDebugPrint();

	// Slots for BufferLoadout
	void showBufferLoadout();

public slots:
	void actionWhenConnected	  ();
	void actionWhenDisconnected	  ();
	void actionWhenConnectionFails();

signals:
	void doConnect(int, int);
	void doDisconnect();

};

#endif // TRIPOD_LAMP_GUI_H