#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QLabel>
#include <QtNetwork>
#include <QTcpServer>
#include <QNetworkSession> 
#include "SocketChat.h"
#include "DebugPrint.h"
#include "CommandDefs.h"


using namespace std;

class TcpServer : public QTcpServer
{
	Q_OBJECT

private:
	SocketChat	 *chat;
	DebugPrint   *dbp;
	QTcpSocket   *tcpSocket;
	QHostAddress  serverIP;
	QLabel		 *labelTCPServerStatus;

	void startTCPServer();
	void stopTCPServer ();
	void killSocket	   ();
	void parseCommand  (QString cmd);

public:
	TcpServer(QWidget *getParent, DebugPrint *getDbp, QLabel *getLabelTCPServerStatus, QObject *parent = 0);
	virtual ~TcpServer();

protected:
	void incomingConnection(int socketDescriptor);

public slots:
	void toggleTCPServer();

	void readDataFromSocket();
	void sendDataFromSocket(QString text);

signals:
	void changeLEDs(char, int, char, int);
};

#endif // TCPSERVER_H