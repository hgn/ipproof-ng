TEMPLATE = app
TARGET = ipproof-server-ng


CONFIG += qt debug warn_on

QT += network widgets


HEADERS += include/server.h

SOURCES += src/server.cpp
