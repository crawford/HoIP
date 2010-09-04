#ifndef FRMSERVER_H
#define FRMSERVER_H

#include "ui_server.h"
#include "serialPort.h"
#include <QDialog>
#include <QTcpServer>
#include <QTcpSocket>

class FrmServer : public QDialog, Ui::Server {
Q_OBJECT
public:
	FrmServer(QWidget *parent = 0, Qt::WindowFlags f = 0);
	~FrmServer();

private:
	QTcpServer *server;
	QTcpSocket *socket;
	SerialPort *port;

private slots:
	void handleNewConnection();
	void lostClient();
	void handleCommand();
};

#endif
