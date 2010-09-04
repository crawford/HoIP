TEMPLATE = app
TARGET = HelperClient
QT += core \
	network
CONFIG += release
OBJECTS_DIR += build
MOC_DIR += build
UI_DIR += build
DESTDIR += release
INCLUDEPATH += src
HEADERS += src/wgtSonar.h \
    src/controller.h
SOURCES += src/wgtSonar.cpp \
    src/controller.cpp \
    src/main.cpp
FORMS += ui/controller.ui
RESOURCES += ui/icons.qrc
