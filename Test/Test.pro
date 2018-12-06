TEMPLATE = app
TARGET = test

include(../common.pri)

# This is a test case, and it should run when we do a "make check".
CONFIG += testcase
QT += testlib

LIBS += ../Build/libmath.a
PRE_TARGETDEPS += ../Build/libmath.a

# Input
SOURCES += Harness.cpp Primes_T.cpp Sqrt_T.cpp
HEADERS += Harness.h Primes_T.h Sqrt_T.h
