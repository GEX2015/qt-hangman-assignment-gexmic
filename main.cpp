// /////////////////////////////////////////////////////////////////////
// File:  Hangman Games
//
// Author: Michael Landry
// This assignment represents my own work and is in accordance with the College Academic Policy
//
// Copyright (c) 2016 All Right Reserved by Michael Landry
// Contributors:
// Description:  QT version of hangman. You have to find the secret word and you have 5 wong guesse.
//
// Date: mai 13 2016
// Revisions:
//
// ///////////////////////////////////////////////////////////////////

#include "controller/mainController.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
