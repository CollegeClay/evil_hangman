#ifndef _HANGMAN_H
#define _HANGMAN_H

/*
    hangman.h
        
    Class definition for the hangman class.

    assignment: CSCI 262 Project - Evil Hangman        

    author: Clayton Christensen

    last modified: 3/12/2021
*/

#include <string>
#include <fstream>
#include <map>
#include <vector>


using namespace std;

/******************************************************************************
   class hangman

   Maintains game state for a game of hangman.

******************************************************************************/

class hangman {
public:
    hangman();

    // start a new game where player gets num_guesses unsuccessful tries
	void start_new_game(int word_length, int num_guesses);

    // player guesses letter c; return whether or not char is in word
    bool process_guess(char c);

    // display current state of word - guessed characters or '-'
    string get_display_word();

    // How many guesses remain?
	int get_guesses_remaining();

    // What characters have already been guessed (for display)?
    string get_guessed_chars();

    // Has this character already been guessed?
    bool was_char_guessed(char c);

    // Has the game been won/lost?  (Else, it continues.)
    bool is_won();
    bool is_lost();

    // Return the true hidden word.
    string get_hidden_word();

    //returns true if there is at least one word in the dictionary of n length
    bool hangman::IsValidWordLength(int n);

    string hangman::LengthOfPossibleWords();


private:
    map<int, vector<string>> dictionary;

    int wordLength;
    int numGuesses = 1;
    vector<string> possibleSecretWords;

    string alreadyGuessedLetters = "";

    string currentWord;
    string losingWord;
};

#endif
