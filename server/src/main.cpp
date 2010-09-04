#include "frmServer.h"

#include <QtGui>
#include <QApplication>

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	FrmServer w(0, Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint | Qt::WindowTitleHint);
	w.show();
	a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));
	return a.exec();
}
