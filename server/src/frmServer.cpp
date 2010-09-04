#include "frmServer.h"
#include <QFile>
#include <QMessageBox>

FrmServer::FrmServer(QWidget *parent, Qt::WindowFlags f) : QDialog(parent, f) {
	setupUi(this);
	socket = 0;
	server = new QTcpServer(this);
	connect(server, SIGNAL(newConnection()), this, SLOT(handleNewConnection()));

	QFile file("port.txt");
	if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		port = new SerialPort(file.readLine());
	} else {
		QMessageBox::critical(this, "Settings Error", "Could not find the port settings file.");
		exit(1);
	}
	file.close();

	if(!port->open()) {
		QMessageBox::critical(this, "Serial Port Error", "Could not open serial port.");
		exit(1);
	}
	port->config(9600, 8);

	server->listen(QHostAddress::Any, 12345);
}

FrmServer::~FrmServer() {
	if(socket) {
		socket->disconnectFromHost();
		delete socket;
	}
	server->close();
	delete server;
}

void FrmServer::handleNewConnection() {
	socket = server->nextPendingConnection();
	server->close();
	connect(socket, SIGNAL(disconnected()), this, SLOT(lostClient()));
	connect(socket, SIGNAL(readyRead()), this, SLOT(handleCommand()));
	lblStatus->setText("Connection established to: " + socket->peerAddress().toString());
}

void FrmServer::lostClient() {
	lblStatus->setText("Lost connection to client.\nWaiting for connection...");
	delete socket;
	socket = 0;
	server->listen(QHostAddress::Any, 12345);
}

void FrmServer::handleCommand() {
	QString line;
	while(socket->canReadLine()) {
		line = socket->readLine();
		lblStatus->setText("Command: " + line);
	}
	port->write(QString(line + " \r").toAscii());
}
