#include "SocketChat.h"

SocketChat::SocketChat(QWidget *parent, Qt::WFlags flags) : QDialog(parent, flags)
{
	ui.setupUi(this);
	this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

	QObject::connect(ui.pushButtonSend   , SIGNAL(pressed()), this, SLOT  (prepareSendMessage()));
	QObject::connect(ui.pushButtonEndChat, SIGNAL(pressed()), this, SIGNAL(endChat			 ()));
}

SocketChat::~SocketChat() { }

void SocketChat::showText(QString t)
{
	ui.lineEditMessage->setText(t);
}

void SocketChat::prepareSendMessage()
{
	QString message = ui.lineEditMessage->text().trimmed();
	
	if(!message.isEmpty())
		sendMessage(message);

	ui.lineEditMessage->setText("");
}