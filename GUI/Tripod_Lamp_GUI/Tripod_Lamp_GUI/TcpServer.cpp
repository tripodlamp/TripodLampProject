#include "TcpServer.h"

// ====================================== Private methods ======================================

void TcpServer::startTCPServer()
{
	QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
	// use the first non-localhost IPv4 address
	for(int i=0;i<ipAddressesList.size();++i) 
		if(ipAddressesList.at(i)!=QHostAddress::LocalHost && ipAddressesList.at(i).toIPv4Address()) {
			serverIP = ipAddressesList.at(i); break;
		}
	
	if(!this->listen(serverIP, SERVER_PORT))
	{
		dbp->print(tr("Unable to start the server: %1.").arg(this->errorString()));
		close();
		return;
	}

	labelTCPServerStatus->setText("<font color='#00BB00'>Online</font>");

	dbp->print(tr("The server is running on\nIP: "+serverIP.toString()+"\nport: "+QString::number(this->serverPort())+"\n\nRun the Fortune Client example now."));
}

void TcpServer::stopTCPServer()
{
	if(tcpSocket!=NULL) { killSocket(); }
	this->close();
	labelTCPServerStatus->setText("<font color='#FF0000'>Offline</font>");
	dbp->print(tr("TCPServer: closed()"));
}

void TcpServer::killSocket()
{
	if(tcpSocket!=NULL)
	{
		tcpSocket->disconnectFromHost ();
		tcpSocket->waitForDisconnected();
		QObject::disconnect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readDataFromSocket()));
		delete(tcpSocket); 
	}
	tcpSocket = NULL;
}

void TcpServer::parseCommand(QString cmd)
{
	QString s_color, s_branch, s_side, s_value;
	char color , side;
	int	 branch, value;
	bool sideCondition = false;
	
	s_color  = cmd.mid(0, 1);
	s_branch = cmd.mid(1, 1);
	s_side   = cmd.mid(2, 1);
	s_value  = cmd.mid(3);
	
	switch(s_color.toUInt())
	{
	case TCP_COLOR_RED  : color = COLOR_RED_SW  ; break;
	case TCP_COLOR_GREEN: color = COLOR_GREEN_SW; break;
	case TCP_COLOR_BLUE : color = COLOR_BLUE_SW ; break;
	case TCP_COLOR_WHITE: color = COLOR_WHITE_SW; break;
	default: dbp->print("parseCommand: Invalid color value"); return;
	}

	switch(s_branch.toUInt())
	{
	case TCP_BRANCH_ALL: branch = 3; break;
	case TCP_BRANCH_1  : branch = 0; break;
	case TCP_BRANCH_2  : branch = 1; break;
	case TCP_BRANCH_3  : branch = 2; break;
	default: dbp->print("parseCommand: Invalid branch value"); return;
	}

	switch(s_side.toUInt())
	{
	case TCP_SIDE_BOTH  : side = SIDE_BOTH	; break;
	case TCP_SIDE_TOP   : side = SIDE_UP	; break;
	case TCP_SIDE_BOTTOM: side = SIDE_BOTTOM; break;
	default: dbp->print("parseCommand: Invalid side value"); return;
	}

	value = s_value.toUInt();
	
	/*switch(s_value.toUInt())
	{
	case TCP_VALUE_MAX: value = MAX_LED_VALUE; break;
	case TCP_VALUE_P10: value =  10;		   break;
	case TCP_VALUE_P1 : value =   1;		   break;
	case TCP_VALUE_M1 : value = - 1;		   break;
	case TCP_VALUE_M10: value = -10;		   break;
	case TCP_VALUE_OFF: value =   0;		   break;
	default: dbp->print("parseCommand: Invalid change value"); return;
	}*/

	// Emit signal to change the light
	changeLEDs(color, value, side, branch);
}

// ====================================== Con-/Destructor ======================================

TcpServer::TcpServer(QWidget *getParent, DebugPrint *getDbp, QLabel *getLabelTCPServerStatus, QObject *parent) : QTcpServer(parent)
{
    dbp					 = getDbp;
	labelTCPServerStatus = getLabelTCPServerStatus;
	tcpSocket			 = NULL;
	
	labelTCPServerStatus->setText("<font color='#FF0000'>Offline</font>");
}

TcpServer::~TcpServer() {  }

// ====================================== Protected methods ======================================

void TcpServer::incomingConnection(int socketDescriptor)
{
	dbp->print("TcpServer: Incoming connection -> opening new socket");

	tcpSocket = new QTcpSocket(this);
	if(!tcpSocket->setSocketDescriptor(socketDescriptor))
	{
		dbp->print("TcpServer: Error while setting socket descriptor");
		return;
	}
	dbp->print("TcpServer: Socket created");

	QObject::connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readDataFromSocket()));
}

// ====================================== Public slots ======================================

void TcpServer::toggleTCPServer()
{
	if(this->isListening())
		stopTCPServer();
	else
		startTCPServer();
}

void TcpServer::readDataFromSocket()
{
	dbp->print("TcpServer: Data available on socket");

	if(!(tcpSocket->bytesAvailable()))
	{
		if(!(tcpSocket->waitForReadyRead()))
		{
			killSocket();
			dbp->print("TcpServer: Connection timed out -> Socket killed");
			return;
		}
	}

    QString     msg;
	QStringList msgs;
	QByteArray  buffer;

	dbp->print("avaliable on start: "+QString::number(tcpSocket->bytesAvailable()));
	buffer = tcpSocket->readAll();
	dbp->print("read to buffer: "+QString::number(buffer.size()));
	dbp->print("availiable now: "+QString::number(tcpSocket->bytesAvailable()));

	msg = msg.append(buffer);
	msgs = msg.split(TCP_COMMAND_END);

	for(unsigned int i=0;i<msgs.size();i++)
		parseCommand(msgs.at(i));
}

void TcpServer::sendDataFromSocket(QString text)
{
	if(tcpSocket!=NULL)
	{
		qint64 bytessend = tcpSocket->write(text.utf8());
		
		while(tcpSocket->bytesToWrite()>0)
		   tcpSocket->waitForBytesWritten();

		dbp->print("TcpServer: "+QString::number(bytessend)+" Bytes send");
	}
}