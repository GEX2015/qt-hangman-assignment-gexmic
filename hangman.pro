#-------------------------------------------------
#
# Project created by QtCreator 2016-05-06T09:19:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = hangman
TEMPLATE = app


SOURCES += main.cpp \
    controller/mainController.cpp

HEADERS  += controller/mainController.h

FORMS    += view/mainwindow.ui

