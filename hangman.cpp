/*
    hangman.cpp
        
    Method implementations for the hangman class.
    
    assignment: CSCI 262 Project - Evil Hangman        

    author: Clayton Christensen

    last modified: 3/7/2019
*/

#include "hangman.h"

using namespace std;

// constructor
hangman::hangman() { 
    ifstream fin("dictionary.txt");
    string str = "";

    while(!fin.eof()){
        getline(fin, str);
        dictionary[str.length()].push_back(str);
    }
}


// start_new_game()
//
// Setup a new game of hangman.
void hangman::start_new_game(int inputLength, int inputGuesses) {
    wordLength = inputLength;
    numGuesses = inputGuesses;
    currentWord = "";
    alreadyGuessedLetters = "";


    possibleSecretWords = dictionary[wordLength];

    for(int a = 0; a < wordLength; a++){
        currentWord += "-";
    }
}

bool hangman::IsValidWordLength(int n){
    if(dictionary.find(n) != dictionary.end()){
        return true;
    }
    return false;
}

string hangman::LengthOfPossibleWords(){
    return to_string(possibleSecretWords.size());
}


// process_guess()
//
// Process a player's guess - should return true/false depending on whether
// or not the guess was in the hidden word.  If the guess is incorrect, the
// remaining guess count is decreased.
bool hangman::process_guess(char c) {

    map<string, vector<string>> m;


    string key = "";


    for(string s : possibleSecretWords){
        key = currentWord;

        size_t found = s.find(c);

        if(found == string::npos){
            m["none"].push_back(s);
            continue;
        }


        for(int i = 0; i < wordLength; i++){
            if(s[i] == c){
                key[i] = c;
            }
        }
        m[key].push_back(s);
    }



    int biggest = 0;
    string newWordListKey = "";
    for(auto entry: m){
        if(entry.second.size() > biggest)
        {
            biggest = entry.second.size();
            newWordListKey = entry.first;
        }
    }

    alreadyGuessedLetters += c;

    if(newWordListKey == "none"){
        possibleSecretWords = m["none"];
        numGuesses--;
        if(numGuesses == 0){
            losingWord = m["none"].front();
        }
        return false;
    }
    currentWord = newWordListKey;
    possibleSecretWords = m[currentWord];
    return true;


}


// get_display_word()
//
// Return a representation of the hidden word, with unguessed letters
// masked by '-' characters.
string hangman::get_display_word() {
    return currentWord;
}


// get_guesses_remaining()
//
// Return the number of guesses remaining for the player.
int hangman::get_guesses_remaining() {
    return numGuesses;
}


// get_guessed_chars()
//
// What letters has the player already guessed?  Return in alphabetic order.
string hangman::get_guessed_chars() {
    return alreadyGuessedLetters;
}


// was_char_guessed()
//
// Return true if letter was already guessed.
bool hangman::was_char_guessed(char c) {

    size_t found = alreadyGuessedLetters.find(c);

    if(found != string::npos){
        return true;
    }
    return false;
}


// is_won()
//
// Return true if the game has been won by the player.
bool hangman::is_won() {
    size_t found = currentWord.find("-");

    if(found == string::npos){
        return true;
    }
    return false;
}


// is_lost()
//
// Return true if the game has been lost.
bool hangman::is_lost() {
    if(numGuesses < 1){
        if(!is_won()){
            return true;
        }
    }
    return false;
}


// get_hidden_word
//
// Return the true hidden word to show the player.
string hangman::get_hidden_word() {
    if(is_lost()){
        return losingWord;
    }
    return currentWord;
}


