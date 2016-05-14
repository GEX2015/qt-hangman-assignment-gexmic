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
    controller/mainController.cpp \
    model/Hangman.cpp

HEADERS  += controller/mainController.h \
    model/Hangman.h

FORMS    += view/mainwindow.ui

DISTFILES += \
    view/images/.DS_Store \
    view/images/gallows0.png \
    view/images/gallows2.png \
    view/images/gallows3.png \
    view/images/gallows4.png \
    view/images/gallows5.png \
    view/images/gallows6.png \
    view/images/Untitled-1.psd

RESOURCES += \
    resources.qrc

