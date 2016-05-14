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


#include "Hangman.h"


Hangman::Hangman()
{
    // open the file and read it throug to pu all word and prase to a vector
    std::ifstream myFile("C:\\hangman.txt");


    // if file is not there inform the player that the file is missing and exit
    if (myFile.fail())
    {
        std::cerr << "The file is mising" << std::endl;
        system("pause");
        exit(EXIT_FAILURE);
    }

    // go in file and put all word in vector
    std::string word;
        while (!myFile.eof())
        {
            getline(myFile, word);
            std::transform(word.begin(), word.end(), word.begin(), tolower);
            if (!myFile.eof() && word.size() > 0)
                _phrase.push_back(word);
        }
        myFile.close();

        // pu the last word or phrase in a string
        newPhrase();
}

// check if the player win the game.
bool Hangman::won()
{
    for (auto c : _secretWord) {
            if (_correctGuesses.find(c) == _correctGuesses.end())
                return false;
        }
    return true;
}

// check if the player lost the game
bool Hangman::lost()
{
    if (_wrongGuesses.size() >= ALLOWED_MISSES)
            return true;
        else
        return false;
}

// process the guesse made by the player and put it to the wrong or good guesse <map>.
// also if the player won or lost the game it juste return and nothing apend if the player click another letter.
void Hangman::processGuess(char c)
{
    if(won()|| lost())
        return;
    if (_wrongGuesses.find(c) != _wrongGuesses.end() || _correctGuesses.find(c) != _correctGuesses.end())
            return;

        std::string::size_type idx = _secretWord.find(c);
        if (idx == std::string::npos)
            _wrongGuesses.insert(c);
        else
            _correctGuesses.insert(c);
}

// push the new phrase from the vector from the back to a string and pop it. it also clear correct guesse and wonrg,
void Hangman::newPhrase()
{
  _secretWord = _phrase.back();
  _phrase.pop_back();

  _correctGuesses.clear();
  _wrongGuesses.clear();
  _correctGuesses.insert(' ');

}

// check for the letter that have alredy been guesse good or not
bool Hangman::letterGuessed(char c)
{
    if (_wrongGuesses.find(c) != _wrongGuesses.end() || _correctGuesses.find(c) != _correctGuesses.end())
        return true;
    else
        return false;
}

// find the good guesse made by the player
bool Hangman::findGoodGuesse(char c)
{
    if (_correctGuesses.find(c) != _correctGuesses.end())
        return true;
    else
        return false;

}

// fin the wrong guesse made by the player
bool Hangman::findWrongGuesse(char c)
{
    if (_wrongGuesses.find(c) != _wrongGuesses.end())
        return true;
    else
        return false;

}

// set the string to have dashes to be easy for the player to know how may letter are in the word
std::string Hangman::phraseWithDashes() const
{
    std::string phrase = "";
    for (int i = 0; i < _secretWord.size(); i++)
        {
            char c = _secretWord.at(i);

            const bool is_in = _correctGuesses.find(c) != _correctGuesses.end();

            std::string tmp =  std::string(1,c);
            if (is_in)
            {
                phrase += tmp + " ";
            }

            else if (tmp == " ")
            {
                phrase +="  ";
            }

            else if (!is_in && tmp != " ")
            {
                phrase +="_ ";
            }
        }

    return phrase;
}

// count the wrong guesse to be able to decise witch gallow to display
int Hangman::wrongGuessCount() const
{
    int wrongGuess = _wrongGuesses.size();

    return wrongGuess;
}

// check if the vector of phrase is enpty and return true or not
bool Hangman::phraseSize()
{
    if(_phrase.empty())
        return true;
    else
        return false;
}

// get the secret word and convert to a string to display in the secretWord lable if the user lost
std::string Hangman::phrase() const
{
    std::string phrase = _secretWord;
    return phrase;
}




