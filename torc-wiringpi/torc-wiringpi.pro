include(../settings.pro)

THIS_LIB = $$PROJECTNAME-wiringpi

TEMPLATE = lib
TARGET = $$THIS_LIB-$$LIBVERSION
INSTALLS = target

QMAKE_CLEAN += $(TARGET) $(TARGETA) $(TARGETD) $(TARGET0) $(TARGET1) $(TARGET2)

CONFIG += thread dll
QT += core
QT -= gui

DEPENDPATH  += ../ ./
INCLUDEPATH += $$DEPENDPATH

LIBS += -lwiringPi

HEADERS += torcwiringpi.h
HEADERS += torcwiringpiexport.h
SOURCES += torcwiringpi.cpp

DEFINES += PREFIX=\\\"$${PREFIX}\\\"
DEFINES += RUNPREFIX=\\\"$${RUNPREFIX}\\\"
DEFINES += LIBDIRNAME=\\\"$${LIBDIRNAME}\\\"
DEFINES += TORC_WIRINGPI_API

use_hidesyms {
    QMAKE_CXXFLAGS += -fvisibility=hidden
}

install.path   = $${PREFIX}/share/torc/html/
install.files += wiringpi.html

INSTALLS += install
