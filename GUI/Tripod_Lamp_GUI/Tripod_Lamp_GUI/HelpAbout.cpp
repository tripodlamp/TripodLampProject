#include "HelpAbout.h"

HelpAbout::HelpAbout(QWidget *parent, Qt::WFlags flags) : QDialog(parent)
{
	ui.setupUi(this);

	this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
	this->setModal(true);
}

HelpAbout::~HelpAbout() {  }

void HelpAbout::showHelpAbout() { this->show (); }
void HelpAbout::hideHelpAbout() { this->close(); }