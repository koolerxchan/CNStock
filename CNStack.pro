#-------------------------------------------------
#
# Project created by QtCreator 2015-08-10T22:25:49
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = CNStack
TEMPLATE = app

SOURCES += main.cpp\
    xlengine.cpp \
    DataType.cpp \
    qcustomplot.cpp \
    mainwindow.cpp \
    onedaystockmangemant.cpp \
    databasemanagement.cpp



HEADERS  += \
    DataType.h \
    networkkernel.h \
    xlengine.h \
    qcustomplot.h \
    mainwindow.h \
    onedaystockmangemant.h \
    databasemanagement.h

win32 {
SOURCES  += networkkernel_win.cpp
HEADERS  += networkkernel_win.h
}

unix {
SOURCES  +=  networkkernerl_linux.cpp
HEADERS  +=  networkkernerl_linux.h
}

FORMS    += \
    mainwindow.ui \
    onedaystockmangemant.ui
