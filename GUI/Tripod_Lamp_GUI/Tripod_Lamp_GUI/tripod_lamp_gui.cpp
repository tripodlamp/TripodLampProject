#include "tripod_lamp_gui.h"

Tripod_Lamp_GUI::Tripod_Lamp_GUI(QWidget *parent, Qt::WFlags flags) : QMainWindow(parent, flags)
{
	ui.setupUi(this);

	// General GUI connections
	QObject::connect(ui.menuExit			   , SIGNAL(triggered   (   )), this, SLOT(menuExit				 (   )));
	QObject::connect(ui.menuConnect			   , SIGNAL(triggered   (   )), this, SLOT(changeConnection		 (   )));
	QObject::connect(ui.menuSerialPortSettings , SIGNAL(triggered   (   )), this, SLOT(showSerialPortSettings(	 )));
	QObject::connect(ui.menuShowDebug		   , SIGNAL(triggered   (   )), this, SLOT(showDebugPrint		 (	 )));
	QObject::connect(ui.menuBufferLoadout	   , SIGNAL(triggered   (   )), this, SLOT(showBufferLoadout	 (	 )));
	QObject::connect(ui.menuToSystray		   , SIGNAL(triggered	(	)), this, SLOT(showHideWindow		 (	 )));
	QObject::connect(ui.pushButtonConnect	   , SIGNAL(clicked		(   )), this, SLOT(changeConnection		 (   )));
	QObject::connect(ui.pushButtonSetDefault   , SIGNAL(clicked		(   )), this, SLOT(setDefault			 (	 )));
	QObject::connect(ui.pushButtonAllLedsOff   , SIGNAL(clicked		(   )), this, SLOT(setAllLEDsOff		 (	 )));
	QObject::connect(ui.pushButtonSwitchFade   , SIGNAL(clicked		(   )), this, SLOT(setFade				 (	 )));
	QObject::connect(ui.pushButtonRunSeqBeg    , SIGNAL(clicked		(	)), this, SLOT(runSequenceBegin		 (	 )));
	QObject::connect(ui.pushButtonRunSeqSel    , SIGNAL(clicked		(	)), this, SLOT(runSequenceStep		 (	 )));
	// Color Tab connections
	QObject::connect(ui.verticalSliderRed	   , SIGNAL(valueChanged	   (int)), this, SLOT(setRedColor		(int)));
	QObject::connect(ui.verticalSliderGreen	   , SIGNAL(valueChanged	   (int)), this, SLOT(setGreenColor		(int)));
	QObject::connect(ui.verticalSliderBlue	   , SIGNAL(valueChanged	   (int)), this, SLOT(setBlueColor		(int)));
	QObject::connect(ui.verticalSliderWhite	   , SIGNAL(valueChanged	   (int)), this, SLOT(setWhiteColor		(int)));
	QObject::connect(ui.pushButtonResetSettings, SIGNAL(clicked			   (   )), this, SLOT(resetColorSettings(	)));
	QObject::connect(ui.comboBoxSide		   , SIGNAL(currentIndexChanged(int)), this, SLOT(setColorSlider	(	)));
	// Specfifc LED connections
	QObject::connect(ui.verticalSliderColor	   , SIGNAL(valueChanged	   (int)), this, SLOT(setSpecificLED	  (int)));
	QObject::connect(ui.comboBoxBranch		   , SIGNAL(currentIndexChanged(int)), this, SLOT(setSpecificLEDSlider(	  )));
	QObject::connect(ui.comboBoxLEDSide		   , SIGNAL(currentIndexChanged(int)), this, SLOT(setSpecificLEDSlider(	  )));
	QObject::connect(ui.comboBoxColor		   , SIGNAL(currentIndexChanged(int)), this, SLOT(setSpecificLEDSlider(	  )));
	QObject::connect(ui.pushButtonIncreaseLED  , SIGNAL(clicked			   (   )), this, SLOT(increaseSpecificLED (	  )));
	QObject::connect(ui.pushButtonDecreaseLED  , SIGNAL(clicked			   (   )), this, SLOT(decreaseSpecificLED (	  )));
	// Sequence connections
	QObject::connect(ui.comboBoxTopSel		   , SIGNAL(currentIndexChanged(int)), this, SLOT(showOptionsTop	  (int)));
	QObject::connect(ui.comboBoxBotSel		   , SIGNAL(currentIndexChanged(int)), this, SLOT(showOptionsBot	  (int)));
	QObject::connect(ui.pushButtonSaveStep	   , SIGNAL(clicked			   (   )), this, SLOT(saveStep			  (   )));
	QObject::connect(ui.lineEditStepName	   , SIGNAL(returnPressed	   (   )), this, SLOT(saveStep			  (	  )));
	QObject::connect(ui.pushButtonStepRemove   , SIGNAL(clicked			   (   )), this, SLOT(removeStep		  (	  )));

	
	// Create QThread and CommandLine Object
	// CommandLine contains the connection to the serial port
	lst  = new LedState	  ();
	cmg  = new CommandGen ();
	cmd  = new CommandLine(cmg->getTransmitBuffer(), cmg->getBufferWritePointer());
	cal  = new CommandCall(cmd);

	// Setup to connections to CommandLine Object
	QObject::connect(this, SIGNAL(doConnect	  (int, int)), cmd, SLOT(Connect   (int, int)));
	QObject::connect(this, SIGNAL(doDisconnect(		   )), cmd, SLOT(Disconnect(		)));

	QObject::connect(cmd, SIGNAL(connectionSuccess()), this, SLOT(actionWhenConnected	   ()));
	QObject::connect(cmd, SIGNAL(connectionFailed ()), this, SLOT(actionWhenConnectionFails()));
	QObject::connect(cmd, SIGNAL(disconnected	  ()), this, SLOT(actionWhenDisconnected   ()));

	// Setup to connections to CommandGen Object
	QObject::connect(cmg, SIGNAL(setColorStatus(char, char			 )), this, SLOT(setColor(char, char			  )));
	QObject::connect(cmg, SIGNAL(setColorStatus(char, char, char	 )), this, SLOT(setColor(char, char, char	  )));
	QObject::connect(cmg, SIGNAL(setColorStatus(char, char, char, int)), this, SLOT(setColor(char, char, char, int)));

	// Setup the form for the serial port settings
	sps = new SerialPortSettings(this);
	QObject::connect(sps, SIGNAL(closeAndSave()), this, SLOT(saveSerialPortSettings()));

	// Setup form for print out debug messages
	dbp = new DebugPrint(this);
	QObject::connect(cmd, SIGNAL(printDebug(QString)), dbp, SLOT(print(QString)));
	QObject::connect(cmg, SIGNAL(printDebug(QString)), dbp, SLOT(print(QString)));

	// Setup form for buffer loadout
	buf = new BufferLoadout(cmg->getBufferWritePointer(), this);
	QObject::connect(cmd, SIGNAL(giveReadPointer(unsigned int)), buf, SLOT(setLoadout(unsigned int)));

	// Setup form for  help about
	hab = new HelpAbout(this);
	QObject::connect(ui.menuAbout, SIGNAL(triggered()), hab, SLOT(showHelpAbout()));
	
	// Setup form for running a sequence
	rsf = new RunSequence(this);
	rsf->setModal(true);
	QObject::connect(rsf, SIGNAL(doSequenceStep(unsigned int)), this, SLOT(doSequenceStep(unsigned int)));

	// Setup for the tcp server
	tcp = new TcpServer(this, dbp, ui.labelTCPServerStatus, this);
	QObject::connect(ui.menuStartTCPServer, SIGNAL(triggered (					  )), tcp , SLOT(toggleTCPServer(					 )));
	QObject::connect(tcp				  , SIGNAL(changeLEDs(char, int, char, int)), this, SLOT(changeLEDs		(char, int, char, int)));

	// Setup for the sequence table
	setUpSequenceTable();

	// Setup for the preset combo box
	setUpPresetComboBox();

	// Init Status Bar settings
	updateSerialPortSettings();

	// Add clicklabel above the color wheel picture to track the mouse actions
	cl = new ClickLabel(ui.tabWidget->widget(0));
	cl->setGeometry(QRect(ui.labelColorWheel->geometry().left(), ui.labelColorWheel->geometry().top(), ui.labelColorWheel->geometry().width(), ui.labelColorWheel->geometry().height()));
	QObject::connect(cl, SIGNAL(mouseMove(int, int)), this, SLOT(ClickLabelClickEvent(int, int)));

	// Setup inital values for pointers for the QPixmap and QOainter to draw the small circle on the color wheel
	colorWheelPixmap  = NULL;
	colorWheelPainter = NULL;
	setAllColorsMode  = false;

	// Call functions to setup inital state for GUI
	actionWhenDisconnected ();
	updateColorSliderLabels();
	setSilderMaxValues	   ();
	initSequenceTab		   ();
	createTrayActions	   ();
    createTrayIcon		   ();
    setTrayIcon			   ();
    trayIcon->show		   ();

	// finally, start second thread to send uart commands
	cal->listenAndSendCommands();
}

Tripod_Lamp_GUI::~Tripod_Lamp_GUI()
{
	delete(trayIcon	   ); trayIcon	   = NULL;
	delete(trayIconMenu); trayIconMenu = NULL;
}

void Tripod_Lamp_GUI::createTrayActions()
{
	showHideTray = new QAction(tr("&Hide Main Window"), this);
    QObject::connect(showHideTray, SIGNAL(triggered()), this, SLOT(showHideWindow()));
    showHideTray->setIcon(QIcon(":/Tripod_Lamp_GUI/Icons/arrow_down.png"));

    closeTray = new QAction(tr("&Exit"), this);
    QObject::connect(closeTray, SIGNAL(triggered()), this, SLOT(menuExit()));
    closeTray->setIcon(QIcon(":/Tripod_Lamp_GUI/Icons/cross.png"));
}

void Tripod_Lamp_GUI::createTrayIcon()
{
	trayIconMenu = new QMenu(this);
	trayIconMenu->addAction(showHideTray);
	trayIconMenu->addSeparator();
	trayIconMenu->addAction(closeTray);
 
	trayIcon = new QSystemTrayIcon(this);
	trayIcon->setContextMenu(trayIconMenu);
 
	QObject::connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(trayIconClicked(QSystemTrayIcon::ActivationReason)));
}

void Tripod_Lamp_GUI::setTrayIcon()
{
	trayIcon->setIcon(QIcon(":/Tripod_Lamp_GUI/Icons/colorwheel_Icon.png"));
}

void Tripod_Lamp_GUI::closeEvent(QCloseEvent *e)
{
	trayIcon->hide();
	e->accept();
}