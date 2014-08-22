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
    log_policy.cpp \
    debugwindow.cpp

HEADERS  += mainwindow.h \
    logger.hpp \
    log.hpp \
    log_policy.h \
    debugwindow.h

FORMS    += mainwindow.ui \
    debugwindow.ui

#QMAKE_CXXFLAGS = -std=c++11 -stdlib=libc++
#QMAKE_LFLAGS = -std=c++11 -stdlib=libc++

CONFIG += c++11
QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.9
