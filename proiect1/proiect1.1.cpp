#include <iostream>
#include <string>
using namespace std;

class HangMan {
private:
    string word, word_guessed, tried_letters;
    int guesses;
public:
    HangMan() {
        word = word_guessed = tried_letters = "";
        guesses = 6;
    }
    HangMan(string _word) {
        word = _word;
        word_guessed = word;
        guesses = 6;
        tried_letters = "";
        for (int i = 0;i < word.length();i++)
            if (word[i] == string(" ")[0])
                word_guessed.replace(i,1, " ");
            else
                word_guessed.replace(i, 1, "_");
    }
    void printUnknownWord() {
        cout << word_guessed << endl;
    }
    void guess(string x) {
        int ok = 1;
        if (playerHasWon())
            cout << "The game is already over." << endl << endl;
        else
        {
            for (int i = 0; i < tried_letters.length() && ok; i++)
                if (tried_letters[i] == x[0] || tried_letters[i] == x[0] + 32 || tried_letters[i] + 32 == x[0])
                {
                    cout << "You already tried this letter. Try another." << endl << endl;
                    ok = 0;
                }
            if (ok) {
                ok = 0;
                tried_letters += x;
                for (int i = 0; i < word.length(); i++)
                    if (word[i] == x[0] || word[i] + 32 == x[0] || word[i] == x[0] + 32)
                    {
                        word_guessed[i] = word[i];
                        ok = 1;
                    }
                if (ok)
                {
                    if (word != word_guessed)
                        if (guesses)
                            cout << "You hit the spot! Now you only have to guess "
                            << word_guessed << endl << endl;
                        else
                            cout << "You hit the spot! But unfortunately you're out of guesses."
                            << endl << "You managed to guess " << word_guessed << "." << endl << endl;
                    else
                        cout << "Congratulations! You've guessed the word " << word
                        << " and won the game!" << endl << endl;
                }
                else
                {
                    guesses--;
                    if (guesses)
                        cout << "Unlucky! That was not it, but you still have " << guesses
                        << " guesses left" << endl << endl;
                    else
                        cout << "Mega-unlucky! That was not it, and you're also out of guesses."
                        << endl << "You managed to guess " << word_guessed << "." << endl << endl;
                }
            }
        }
    }
    int playerHasWon() {
        return word == word_guessed || guesses==0;
    }
    void printStats() {
        cout << "Guess " << word_guessed << endl << "Tried letters: "
            << tried_letters << endl << "You have " << guesses << " guesses left" << endl<<endl;
    }
};

int main()
{
    HangMan game{ "Thug POO" };

    game.printStats(); /*
    functia membra va afisa:

    Guess  _ _ _ _   _ _ _
    Tried letters:
    You have 6 guesses left.

 */
    game.printUnknownWord(); // Va afisa: "_ _ _ _   _ _ _"
    game.guess("P"); // Va afisa: "You hit the spot! Now you only have to guess _ _ _ _ _ P _ _"
    game.guess("o"); // Va afisa: "You hit the spot! Now you only have to guess _ _ _ _ _ P O O"
    game.printStats(); /* va afisa:
        Guess  _ _ _ _ _ P O O
        Tried letters: PO
        You have 6 guesses left.
 */

    game.guess("z"); // "Unlucky! That was not it, but you still have 5 guesses left"
    game.guess("t");
    game.guess("h");
    game.guess("O");
    cout << game.playerHasWon() << endl;
    game.guess("u");
    game.guess("a");
    game.guess("g");
    // dupa ultimul apel se va afisa: "Congratulations! You've guessed the WORD won the GAME"
    cout << game.playerHasWon()<<endl;
    game.guess("s");
    return 0;
}

