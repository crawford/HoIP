#include "controller.h"

#include <QtGui>
#include <QApplication>

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	RobotController w;
	w.show();
	a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));
	return a.exec();
}
