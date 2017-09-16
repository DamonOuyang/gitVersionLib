#-------------------------------------------------
#
# Project created by QtCreator 2017-09-15T11:58:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CreditMgr
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h \
    SDT_VC.h

FORMS    += widget.ui
LIBS     += "E:/gitVersionLib/test_code/CreditMgr/SDT.dll"
