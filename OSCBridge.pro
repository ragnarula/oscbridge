#-------------------------------------------------
#
# Project created by QtCreator 2014-08-22T15:05:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OSCBridge
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ioservicehandler.cpp \
    udposcendpoint.cpp \
    core.cpp \
    devicemapper.cpp \
    bufferreader.cpp \
    tcpdevice.cpp \
    device.cpp \
    oscaddressreader.cpp \
    adddevicedialog.cpp

HEADERS  += mainwindow.h \
    ioservicehandler.h \
    udposcendpoint.h \
    core.h \
    globals.h \
#    messaging.hpp \
    devicemapper.h \
    bufferreader.h \
    messagtypes.h \
    oscpkt.hh \
    tcpdevice.h \
    device.h \
    oscaddressreader.h \
    adddevicedialog.h

FORMS    += mainwindow.ui \
    adddevicedialog.ui

QMAKE_CXXFLAGS = -std=c++11 -stdlib=libc++
QMAKE_LFLAGS = -std=c++11 -stdlib=libc++

CONFIG += c++11
QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.9


INCLUDEPATH += /usr/local/include

INCLUDEPATH += $$PWD/../logger
INCLUDEPATH += $$PWD/../messaging

unix|win32: LIBS += -lboost_system -L/usr/local/lib
#unix|win32: LIBS += /usr/local/lib/libboost_system.a

unix|win32: LIBS += -lboost_filesystem
#unix|win32: LIBS += /use/local/lib/libboost_filesystem.a
