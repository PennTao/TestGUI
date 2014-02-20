#-------------------------------------------------
#
# Project created by QtCreator 2014-02-12T17:36:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestGUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mygraphicsview.cpp \
    mygraphicsscene.cpp

HEADERS  += mainwindow.h \
    mygraphicsview.h \
    mygraphicsscene.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    panda_AP.jpg
