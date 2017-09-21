#-------------------------------------------------
#
# Project created by QtCreator 2017-09-20T09:18:48
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BaseAPI
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    baseapi.cpp \
    gameapi.cpp

HEADERS  += widget.h \
    baseapi.h \
    gameapi.h

