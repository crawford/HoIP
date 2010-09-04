TEMPLATE = app
TARGET = HelperServer
QT += core \
	network
CONFIG += release
OBJECTS_DIR += build
MOC_DIR += build
UI_DIR += build
DESTDIR += release

HEADERS += src/frmServer.h \
	src/SerialPort.h
SOURCES += src/frmServer.cpp \
	src/SerialPort.cpp \
    src/main.cpp
FORMS += ui/server.ui
