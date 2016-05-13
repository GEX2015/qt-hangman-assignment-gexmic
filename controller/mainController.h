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


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <map>
#include <memory>
#include <QPushButton>
#include <QLabel>
#include <string>

namespace Ui {
class MainWindow;
}

//foward declaration
class Hangman;
enum class Gallow;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void draw();

public slots:
    void onLetterClicked();
    void onNewPhraseClicked();

private:

    Ui::MainWindow *ui;
    std::vector<std::string> _gallowImage;
    std::vector<QPushButton*> _letterButtons;
    std::vector<QLabel*> _gallowLabel;

    std::unique_ptr<Hangman> _hangmanGame;

    QLabel* _lblGallow;
    QLabel*  _lblSecretWord;
};

#endif // MAINWINDOW_H
