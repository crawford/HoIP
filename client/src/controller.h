#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QtGui/QDialog>
#include <QKeyEvent>
#include <QTimer>
#include <QTcpSocket>
#include "ui_controller.h"

class RobotController : public QDialog {
	Q_OBJECT

public:
	RobotController(QWidget *parent = 0);
	~RobotController();
	
protected:
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);

private:
	void sendSpeedUpdate();
	bool incrementToward(int &initialL, int targetL, int &initialR, int targetR);
	
	Ui::RobotControllerClass ui;
	QTcpSocket *socket;
	QTimer *timer;
	bool up;
	bool down;
	bool left;
	bool right;
	int maxLeft;
	int maxRight;
	int stopSpeed;
	int leftSpeed;
	int rightSpeed;
	
private slots:
	void on_btnBeep_clicked(bool checked);
	void on_btnSend_clicked();
	void on_txtCommand_returnPressed();
	void on_btnUpdateValues_clicked();
	void accelerate();
};

#endif // CONTROLLER_H
