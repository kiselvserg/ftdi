#-------------------------------------------------
#
# Project created by QtCreator 2013-11-22T01:14:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ftdi
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

FORMS    += widget.ui

LIBS += D:\qt\qtproject\include\ftdi\ftd2xx.lib
