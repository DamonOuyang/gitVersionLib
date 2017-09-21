#-------------------------------------------------
#
# Project created by QtCreator 2017-09-18T10:42:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CreditMgr_non-ui
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    lineedit.cpp \
    pushbutton.cpp \
    label.cpp

HEADERS  += widget.h \
    lineedit.h \
    pushbutton.h \
    label.h \
    SDT_VC.h

LIBS += "E:/gitVersionLib/test_code/CreditMgr_non-ui/SDT.dll"

