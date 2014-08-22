#-------------------------------------------------
#
# Project created by QtCreator 2014-08-12T10:26:39
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = burya
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    database.cpp \
    dialogcolor.cpp \
    qcustomplot.cpp \
    creategraphics.cpp

HEADERS  += mainwindow.h \
    database.h \
    dialogcolor.h \
    qcustomplot.h \
    creategraphics.h

FORMS    += mainwindow.ui \
    dialogcolor.ui \
    creategraphics.ui

CONFIG += qwt
