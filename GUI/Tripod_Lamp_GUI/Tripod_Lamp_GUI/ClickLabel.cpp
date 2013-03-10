#include "ClickLabel.h"

ClickLabel::ClickLabel(QWidget *p) : QWidget(p)
{
	this->setMouseTracking(true);
	mouseButtonPushed = false;
}

ClickLabel::~ClickLabel() {  }

void ClickLabel::mouseReleaseEvent(QMouseEvent *e) { mouseButtonPushed = false; mouseMove(e->pos().x(), e->pos().y()); }
void ClickLabel::mousePressEvent  (QMouseEvent *e) { mouseButtonPushed = true ; }

void ClickLabel::mouseMoveEvent(QMouseEvent *e)
{
	if(mouseButtonPushed)
			mouseMove(e->pos().x(), e->pos().y());
}