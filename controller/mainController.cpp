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


#include "mainController.h"
#include "ui_mainwindow.h"
#include "../model/Hangman.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QPushButton>
#include <QLabel>
#include <QFont>
#include <fstream>
#include <iostream>
#include <QString>
#include <QDebug>
#include <QPalette>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // puch the image of the gallow in a vector
    _gallowImage.push_back("border-image:url(:/media/media/gallows0.png)");
    _gallowImage.push_back("border-image:url(:/media/media/gallows2.png)");
    _gallowImage.push_back("border-image:url(:/media/media/gallows3.png)");
    _gallowImage.push_back("border-image:url(:/media/media/gallows4.png)");
    _gallowImage.push_back("border-image:url(:/media/media/gallows5.png)");
    _gallowImage.push_back("border-image:url(:/media/media/gallows6.png)");

    // create a new hangman object.
    _hangmanGame = std::unique_ptr<Hangman>(new Hangman);

    //create the layout
    auto hlMain = new QHBoxLayout(ui->centralWidget);

    auto vlGallow = new QVBoxLayout();
    _lblGallow = new QLabel(this);
    _lblGallow->setMinimumSize(600,600);
    _lblGallow->setMaximumSize(600,600);
    QString qstr = QString::fromStdString(_gallowImage.at(_hangmanGame->wrongGuessCount()));
    _lblGallow->setStyleSheet(qstr);

    vlGallow->addWidget(_lblGallow);

    // secret word label
    _lblSecretWord = new QLabel(this);
    _lblSecretWord->setObjectName("lblSecretWord");
    _lblSecretWord->setMinimumSize(400,75);
    _lblSecretWord->setMaximumSize(400,75);

    QFont f( "Arial", 15, QFont::Bold);
    _lblSecretWord->setFont(f);

    QString phrase = QString::fromStdString(_hangmanGame->phraseWithDashes());
    _lblSecretWord->setText(phrase);

    vlGallow->addWidget(_lblSecretWord);
    hlMain->addLayout(vlGallow);

    // create the letter button to guesse letter in the word.
    auto vlForLetter = new QVBoxLayout();
    auto glLetters = new QGridLayout();

    // letters
    for(char c='a';c<='z';++c)
    {
        auto btn = new QPushButton();
        btn->setMinimumSize(75,75);
        btn->setMaximumSize(75,75);
        btn->setText(QString(c));
        QFont f( "Cooper Black", 15, QFont::Bold);
        btn->setFont(f);
        int idx = c - 'a'; // c-'a' is 0 base index
        glLetters->addWidget(btn, idx /6,idx%6);

        _letterButtons.push_back(btn);
        connect(btn, &QPushButton::clicked, this, &MainWindow::onLetterClicked);
    }

    // new phrase puch button
    vlForLetter->addLayout(glLetters);

    auto vlForNewPhraseBtn = new QVBoxLayout();

    auto newPhrasebtn = new QPushButton();
    newPhrasebtn->setObjectName("btnNewPhrase");
    newPhrasebtn->setMinimumSize(250,75);
    newPhrasebtn->setMaximumSize(250,75);
    QFont phraseBtnFont( "Cooper Black", 15, QFont::Bold);
    newPhrasebtn->setFont(phraseBtnFont);
    newPhrasebtn->setText("New Phrase");

    connect (newPhrasebtn, &QPushButton::clicked, this, &MainWindow::onNewPhraseClicked);

    vlForNewPhraseBtn->addWidget(newPhrasebtn);

    vlForLetter->addLayout(vlForNewPhraseBtn);
    hlMain->addLayout(vlForLetter);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::draw()
{
    QString phrase = QString::fromStdString(_hangmanGame->phraseWithDashes());
   _lblSecretWord->setText(phrase);

   // check if the player have lost if true display the secret word
   if(_hangmanGame->lost())
   {
       QString phrase = QString::fromStdString(_hangmanGame->phrase());
      _lblSecretWord->setText(phrase);

   }
   // check if the player won the game if true change the gallow to youWin image.
   if(_hangmanGame->won())
   {
       _lblGallow->setStyleSheet("border-image:url(:/media/media/youWin.png)");
       QString phrase = QString::fromStdString(_hangmanGame->phrase());
      _lblSecretWord->setText(phrase);

   }

   // go to the letter buttons and check id the letter have been guesse or not and enable or not
   for(auto letter : _letterButtons)
   {
       if(_hangmanGame->findGoodGuesse(letter->text().data()->toLatin1()))
          {
           letter->setStyleSheet("border-image:url(:/media/media/good.png)");
           letter->setEnabled(false);
       }
       if (_hangmanGame->findWrongGuesse(letter->text().data()->toLatin1()))
       {
           letter->setStyleSheet("border-image:url(:/media/media/wrong.png)");
           letter->setEnabled(false);
       }



       else
        letter->setEnabled(true);
   }

   // check for the number of wrong guesse and decide with image of the gallow to display
   QString qstr = QString::fromStdString(_gallowImage.at(_hangmanGame->wrongGuessCount()));
   _lblGallow->setStyleSheet(qstr);
}


void MainWindow::onLetterClicked()
{
    // send the letter that is been click
    QPushButton* btn = dynamic_cast<QPushButton*>(sender());

    // change the letter to a char.
    char c = btn->text().data()->toLatin1();
    _hangmanGame->processGuess(c);
    draw();
}

void MainWindow::onNewPhraseClicked()
{
    // reset all the letter button to be enable and take of the image border.
    for(auto letter : _letterButtons)
    {
        letter->setEnabled(true);
        letter->setStyleSheet(false);
    }

    // check if the player have play all the word from the file if yes message box informe the player and close the program
    if(_hangmanGame->phraseSize())
    {
        _lblSecretWord->setText("No more words in the file");
        QMessageBox::information(
            this,
            tr("Hangman Game"),
            tr("No more words in the file thanks for playing") );
        qApp->exit();
        return;
    }

    // reste the gallow to 0 for the next phrase
    _hangmanGame->newPhrase();
    QString qstr = QString::fromStdString(_gallowImage.at(_hangmanGame->wrongGuessCount()));
    _lblGallow->setStyleSheet(qstr);

    // set the secret word lable for the next word
    QString phrase = QString::fromStdString(_hangmanGame->phraseWithDashes());
   _lblSecretWord->setText(phrase);


}


