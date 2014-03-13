QT = core network gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
TARGET = ipproof-ng-server
DEPENDPATH += . include src
INCLUDEPATH += . include

# Input
HEADERS += \
    include/mainwindow.h \
    include/server.h \
    include/server-listener.h \
    include/measurement-config-dialog.h \
    include/throughput-widget.h
SOURCES += \
    src/mainwindow.cpp \
    src/server.cpp \
    src/server-listener.cpp \
    src/measurement-config-dialog.cpp \
    src/throughput-widget.cpp
