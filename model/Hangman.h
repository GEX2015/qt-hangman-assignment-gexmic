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

#ifndef HANGMAN_H
#define HANGMAN_H
#include <set>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <QThread>

static const int ALLOWED_MISSES = 5;

class Hangman
{
public:
    Hangman();

    bool won();
    bool lost();
    bool letterGuessed(char c);
    bool findGoodGuesse(char c);
    bool findWrongGuesse (char c);
    bool phraseSize();

    void processGuess(char c);
    void newPhrase();
    static void sleep(unsigned long secs){QThread::sleep(secs);}

    std::string phrase()const;
    std::string phraseWithDashes()const;

    int wrongGuessCount()const;

private:
    std::vector<std::string> _phrase;
    std::set<char> _correctGuesses;
    std::set<char> _wrongGuesses;
    std::string _secretWord;
};

#endif // HANGMAN_H
