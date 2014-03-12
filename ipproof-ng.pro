QT = core network gui

TEMPLATE = app
TARGET = 
DEPENDPATH += . include src
INCLUDEPATH += . include

# Input
HEADERS += include/mainwindow.h include/server.h include/server-listener.h
SOURCES += src/mainwindow.cpp src/server.cpp src/server-listener.cpp
