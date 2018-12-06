# Build file for main application.

TEMPLATE = app
TARGET = main

include(../common.pri)

CONFIG += console
QT += network

LIBS += ../Build/libmath.a

# Input
SOURCES += main.cpp Application.cpp LogCollector.cpp logEvent.cpp

HEADERS += Application.h LogCollector.h logEvent.h

# Output (main application in top level directory)
DESTDIR = ..
