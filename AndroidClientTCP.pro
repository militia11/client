#-------------------------------------------------
#
# Project created by QtCreator 2015-08-27T17:42:23
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AndroidClientTCP
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    Client.cpp

HEADERS  += MainWindow.h \
    Client.h

FORMS    += MainWindow.ui
