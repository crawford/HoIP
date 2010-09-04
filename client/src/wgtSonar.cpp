#include "wgtSonar.h"
#include <QPainter>

WgtSonar::WgtSonar(QWidget *parent) : QWidget(parent) {
	setMinimumSize(200, 200);
}

void WgtSonar::paintEvent(QPaintEvent *event) {
	QPainter *p = new QPainter(this);
	p->setRenderHint(QPainter::Antialiasing, true);
	
	p->setPen(QColor(255, 0, 0));
	p->setBrush(QColor(255, 0, 0));
	for(int i = 0; i < 7; i++)
		drawArc(rand()%120 + 50, i, p);
	
	p->setPen(QColor(200, 200, 200));
	for(int i = 1; i < 4; i++)
		drawCircle(i*40 + 50, p);
}

void WgtSonar::drawArc(int size, int segment, QPainter *painter) {
	painter->drawPie((width()-size)/2, (height()-size)/2, size, size, 3909 + 823*segment, 823);
}

void WgtSonar::drawCircle(int size, QPainter *painter) {
	painter->drawArc((width()-size)/2, (height()-size)/2, size, size, 0, 5760);
}
