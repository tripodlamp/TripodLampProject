#ifndef SOCKETCHAT_H
#define SOCKETCHAT_H

#include <QDialog>
#include <QtGui/QMainWindow>
#include "ui_FormSocketChat.h"

class SocketChat : public QDialog
{
	Q_OBJECT

private:
	Ui::FormSocketChat ui;

public:
	SocketChat(QWidget *parent = 0, Qt::WFlags flags = 0);
	virtual ~SocketChat();

	void showText(QString t);

public slots:
	void prepareSendMessage();

signals:
	void sendMessage(QString);
	void endChat();

};


#endif // SOCKETCHAT_H