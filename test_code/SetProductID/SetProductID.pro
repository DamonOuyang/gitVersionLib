#-------------------------------------------------
#
# Project created by QtCreator 2017-10-17T16:14:33
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SetProductID
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \


HEADERS  += widget.h \


FORMS    += widget.ui

DISTFILES += \
    Service/service.pri
