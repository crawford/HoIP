#ifndef WGTSONAR_H
#define WGTSONAR_H

#include <QWidget>

class WgtSonar : public QWidget {
	Q_OBJECT
	
public:
	WgtSonar(QWidget *parent);
	
protected:
	void paintEvent(QPaintEvent *event);
	void drawArc(int size, int segment, QPainter *painter);
	void drawCircle(int size, QPainter *painter);
};

#endif /*WGTSONAR_H_*/
