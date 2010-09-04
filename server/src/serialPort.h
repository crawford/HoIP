#ifndef SERIALPORT_H_
#define SERIALPORT_H_

#include <windows.h>
#include <QString>
#include <QByteArray>

class SerialPort {
public:
	SerialPort(QString name);
	bool config(int baudRate, int byteSize);
	bool open();
	bool write(QByteArray data);
	void close();
	
private:
	HANDLE hCom;
	QString portName;
};
#endif
