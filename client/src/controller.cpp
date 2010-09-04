#include "controller.h"
#include <QMessageBox>
#include <QFile>

RobotController::RobotController(QWidget *parent) : QDialog(parent) {
	ui.setupUi(this);
	up = false;
	down = false;
	left = false;
	right = false;
	
	on_btnUpdateValues_clicked();
	leftSpeed = stopSpeed;
	rightSpeed = stopSpeed;

	socket = new QTcpSocket(this);
	QFile file("server.txt");
	if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		socket->connectToHost(file.readLine(), 12345);
		if(!socket->waitForConnected(5000)) {
			QMessageBox::critical(this, "Connection Error", "Could not establish a connection to host.");
			exit(1);
		}
	} else {
		QMessageBox::critical(this, "Settings Error", "Could not find the server settings file.");
		exit(1);
	}
	file.close();

	timer = new QTimer(this);
	timer->setInterval(50);
	connect(timer, SIGNAL(timeout()), this, SLOT(accelerate()));
}

RobotController::~RobotController() {
	socket->disconnectFromHost();
}

void RobotController::on_btnBeep_clicked(bool checked) {
	if(checked)
		socket->write(QString("pwm 2:150\n").toAscii());
	else
		socket->write(QString("pwm 2:0\n").toAscii());
	socket->flush();
}

void RobotController::on_txtCommand_returnPressed() {
	ui.btnSend->animateClick();
}

void RobotController::on_btnSend_clicked() {
	socket->write(QString(ui.txtCommand->text() + "\n").toAscii());
	socket->flush();
}

void RobotController::on_btnUpdateValues_clicked() {
	maxLeft = ui.spnMSL->value();
	maxRight = ui.spnMSR->value();
	stopSpeed = ui.spnStop->value();
}

void RobotController::sendSpeedUpdate() {
	socket->write(QString("servo 1:%1 2:%2\n").arg(rightSpeed).arg(leftSpeed).toAscii());
	socket->flush();
}

bool RobotController::incrementToward(int &initialL, int targetL, int &initialR, int targetR) {
	if(initialL == targetL && initialR == targetR)
		return false;
	
	if(initialL < targetL) {
		initialL += 10;
		if(initialL > targetL)
			initialL = targetL;
	} else if(initialL != targetL) {
		initialL -= 10;
		if(initialL < targetL)
			initialL = targetL;
	}
	if(initialR < targetR) {
		initialR += 10;
		if(initialR > targetR)
			initialR = targetR;
	} else if(initialR != targetR) {
		initialR -= 10;
		if(initialR < targetR)
			initialR = targetR;
	}
	
	return true;
}

void RobotController::accelerate() {
	bool changed = false;

	if(!timer->isActive())
		timer->start();
	
	if(up) {
		if(left)
			changed |= incrementToward(leftSpeed, stopSpeed, rightSpeed, maxRight);
		else if(right)
			changed |= incrementToward(leftSpeed, maxLeft, rightSpeed, stopSpeed);
		else
			changed |= incrementToward(leftSpeed, maxLeft, rightSpeed, maxRight);
	} else if(down) {
		
		if(left)
			changed |= incrementToward(leftSpeed, stopSpeed, rightSpeed, -maxRight);
		else if(right)
			changed |= incrementToward(leftSpeed, -maxLeft, rightSpeed, stopSpeed);
		else
			changed |= incrementToward(leftSpeed, -maxLeft, rightSpeed, -maxRight);
	} else if(left)
		changed |= incrementToward(leftSpeed, -maxLeft, rightSpeed, maxRight);
	else if(right)
		changed |= incrementToward(leftSpeed, maxLeft, rightSpeed, -maxRight);
	else
		changed |= incrementToward(leftSpeed, stopSpeed, rightSpeed, stopSpeed);

	if(!changed)
		timer->stop();
	
	sendSpeedUpdate();
}

void RobotController::keyPressEvent(QKeyEvent *event) {
	if(event->isAutoRepeat())
		return;
	
	if(event->key() == Qt::Key_Escape)
		reject();
	
	bool changed = false;
	
	if(event->key() == Qt::Key_Up && !up) {
		up = true;
		changed = true;
	}
	if(event->key() == Qt::Key_Down && !down) {
		down = true;
		changed = true;
	}
	if(event->key() == Qt::Key_Left && !left) {
		left = true;
		changed = true;
	}
	if(event->key() == Qt::Key_Right && !right) {
		right = true;
		changed = true;
	}
	event->accept();
	
	if(changed)
		accelerate();
}

void RobotController::keyReleaseEvent(QKeyEvent *event) {
	if(event->isAutoRepeat())
		return;
	
	bool changed = false;
		
	if(event->key() == Qt::Key_Up && up) {
		up = false;
		changed = true;
	}
	if(event->key() == Qt::Key_Down && down) {
		down = false;
		changed = true;
	}
	if(event->key() == Qt::Key_Left && left) {
		left = false;
		changed = true;
	}
	if(event->key() == Qt::Key_Right && right) {
		right = false;
		changed = true;
	}
	event->accept();
	
	if(changed)
		accelerate();
}
