# Build file for all Sources
# This builds all files to be tested as a static library. Both the application and the test
# framework link to it.

TEMPLATE = lib
CONFIG += staticlib

TARGET = math

include(../common.pri)

SOURCES += primes.cpp sqrt.cpp
HEADERS += primes.h sqrt.h

DESTDIR = ../Build
