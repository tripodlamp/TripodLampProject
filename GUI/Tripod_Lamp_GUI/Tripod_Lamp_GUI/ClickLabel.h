#ifndef CLICKLABEL_H
#define CLICKLABEL_H

#include <QWidget>
#include <QMouseEvent>

class ClickLabel : public QWidget
{
	Q_OBJECT

public:
	ClickLabel(QWidget *p);
	~ClickLabel();

private:
	bool mouseButtonPushed;

protected:
	void mouseReleaseEvent(QMouseEvent *e);    
	void mousePressEvent  (QMouseEvent *e);
	void mouseMoveEvent   (QMouseEvent *e);

signals:
	void mouseClickEvent();
	void mouseMoveEvent();

	void mouseMove(int, int);
};

#endif // CLICKLABEL_H