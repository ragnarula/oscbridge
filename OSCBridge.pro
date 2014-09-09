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
    bufferreader.cpp

HEADERS  += mainwindow.h \
    ioservicehandler.h \
    udposcendpoint.h \
    core.h \
    globals.h \
    messaging.hpp \
    devicemapper.h \
    bufferreader.h \
    messagtypes.h \
    oscpkt.hh

FORMS    += mainwindow.ui

#QMAKE_CXXFLAGS = -std=c++11 -stdlib=libc++
#QMAKE_LFLAGS = -std=c++11 -stdlib=libc++

CONFIG += c++11
QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.9


INCLUDEPATH += /usr/local/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-Logger-Desktop_Qt_5_3_clang_64bit-Debug/release/ -lLogger
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-Logger-Desktop_Qt_5_3_clang_64bit-Debug/debug/ -lLogger
else:unix: LIBS += -L$$PWD/../build-Logger-Desktop_Qt_5_3_clang_64bit-Debug/ -lLogger

INCLUDEPATH += $$PWD/../Logger
DEPENDPATH += $$PWD/../Logger

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-Logger-Desktop_Qt_5_3_clang_64bit-Debug/release/libLogger.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-Logger-Desktop_Qt_5_3_clang_64bit-Debug/debug/libLogger.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-Logger-Desktop_Qt_5_3_clang_64bit-Debug/release/Logger.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-Logger-Desktop_Qt_5_3_clang_64bit-Debug/debug/Logger.lib
else:unix: PRE_TARGETDEPS += $$PWD/../build-Logger-Desktop_Qt_5_3_clang_64bit-Debug/libLogger.a



unix|win32: LIBS += -lboost_system -L/usr/local/lib
#unix|win32: LIBS += /usr/local/lib/libboost_system.a

unix|win32: LIBS += -lboost_filesystem
#unix|win32: LIBS += /use/local/lib/libboost_filesystem.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-AppPaths-Desktop_Qt_5_3_clang_64bit-Debug/release/ -lAppPaths
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-AppPaths-Desktop_Qt_5_3_clang_64bit-Debug/debug/ -lAppPaths
else:unix: LIBS += -L$$PWD/../build-AppPaths-Desktop_Qt_5_3_clang_64bit-Debug/ -lAppPaths

INCLUDEPATH += $$PWD/../AppPaths
DEPENDPATH += $$PWD/../AppPaths

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-AppPaths-Desktop_Qt_5_3_clang_64bit-Debug/release/libAppPaths.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-AppPaths-Desktop_Qt_5_3_clang_64bit-Debug/debug/libAppPaths.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-AppPaths-Desktop_Qt_5_3_clang_64bit-Debug/release/AppPaths.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-AppPaths-Desktop_Qt_5_3_clang_64bit-Debug/debug/AppPaths.lib
else:unix: PRE_TARGETDEPS += $$PWD/../build-AppPaths-Desktop_Qt_5_3_clang_64bit-Debug/libAppPaths.a
