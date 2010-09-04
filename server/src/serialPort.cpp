#include "serialPort.h"

SerialPort::SerialPort(QString name) {
	portName = name;
}
bool SerialPort::config(int baudRate, int byteSize) {
	if(!SetupComm(hCom, 1024, 1024))
		return false;

	DCB dcbConfig;
	
	if(GetCommState(hCom, &dcbConfig)) {
		/* Configuring Serial Port Settings */
		dcbConfig.BaudRate = baudRate;
		dcbConfig.ByteSize = byteSize;
		dcbConfig.Parity = NOPARITY;
		dcbConfig.StopBits = ONESTOPBIT;
		dcbConfig.fBinary = TRUE;
		dcbConfig.fParity = FALSE;
	} else
		return false;

	if(!SetCommState(hCom, &dcbConfig))
		return false;

	COMMTIMEOUTS commTimeout;
				
	if(GetCommTimeouts(hCom, &commTimeout)) {
		/* Configuring Read & Write Time Outs */
		commTimeout.ReadIntervalTimeout = 1000; //One second
		commTimeout.ReadTotalTimeoutConstant = 1000; //One second
		commTimeout.ReadTotalTimeoutMultiplier = 0;
		commTimeout.WriteTotalTimeoutConstant = 1000; //One second
		commTimeout.WriteTotalTimeoutMultiplier = 0;
	} else
		return false;

	if(SetCommTimeouts(hCom, &commTimeout))
		return true;
	else
		return false;
}
bool SerialPort::open() {
	hCom = CreateFile( (LPCTSTR) portName.utf16(),
	    GENERIC_READ | GENERIC_WRITE,
	    0,    // exclusive access 
	    NULL, // default security attributes 
	    OPEN_EXISTING,
	    0,
	    NULL 
	    );
	
	if(hCom == INVALID_HANDLE_VALUE)
		return false;
	else
		return true;

}
bool SerialPort::write(QByteArray data) {
	unsigned long dwNumberOfBytesWritten;
	char c;
	
	for(int i = 0; i < data.size(); i++) {
		c = data.at(i);
		if(WriteFile(hCom, &c, 1, &dwNumberOfBytesWritten, NULL) != 0) {
			if(dwNumberOfBytesWritten == 0)
				return false;
		} else
			return false;
	}
		
	return true;
}
void SerialPort::close() {
	if(hCom != INVALID_HANDLE_VALUE) {
		CloseHandle(hCom);
		hCom = INVALID_HANDLE_VALUE;
	}
}
