#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

using namespace std;

#define COLOR_RESET "\033[0m"
#define COLOR_CYAN "\033[1;36m"
#define COLOR_YELLOW "\033[1;33m"
#define COLOR_GREEN "\033[1;32m"
#define COLOR_RED "\033[1;31m"
#define COLOR_MAGENTA "\033[1;35m"

bool isValidLetter(char letter)
{
    return (letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z');
}

vector<string> initializeWordList()
{
    vector<string> wordList = {
        "Hassan",
        "Ahmed",
        "lab",
        "viva"
    };
    return wordList;
}

string getRandomWord(const vector<string> &wordList)
{
    int index = rand() % wordList.size();
    return wordList[index];
}

string initializeHiddenWord(const string &word)
{
    string hiddenWord(word.length(), '_');
    return hiddenWord;
}

void updateHiddenWord(const string &word, string &hiddenWord, char letter)
{
    for (size_t i = 0; i < word.length(); i++)
    {
        if (word[i] == letter)
        {
            hiddenWord[i] = letter;
        }
    }
}

bool isWordGuessed(const string &hiddenWord)
{
    return hiddenWord.find('_') == string::npos;
}

void deallocateResources()
{
    const char *moyemoyeFifo = "/tmp/moyemoyeFifo";
    int fd = open(moyemoyeFifo, O_WRONLY | O_NONBLOCK);
    if (fd != -1)
    {
        const char *msg = "HANGMAN";
        write(fd, msg, strlen(msg) + 1);
        close(fd);
    }
}

int main()
{
    cout << endl;
    cout << COLOR_MAGENTA << "Welcome to NEXIS Hangman!\n\n" << COLOR_RESET;

    int n = 1;
    cout << COLOR_GREEN << "To exit enter 0, To play enter 1: " << COLOR_RESET;
    cin >> n;
    if (n == 0)
    {
        deallocateResources();
        cout << COLOR_MAGENTA << "\nThank you for playing NEXIS Hangman! Close window to end task\n" << COLOR_RESET;
        sleep(1);
        return 0;
    }
    else
    {
        do
        {
            srand(static_cast<unsigned int>(time(0)));
            vector<string> wordList = initializeWordList();
            string word = getRandomWord(wordList);
            string hiddenWord = initializeHiddenWord(word);
            string guessedLetters;
            int attempts = 6;

            while (attempts > 0 && !isWordGuessed(hiddenWord))
            {
                cout  << "Word -> " << hiddenWord << endl;
                cout  << "Attempts left -> " << attempts << endl;
                cout  << "Guessed letters -> " << guessedLetters << endl;

                char guess;
                cout << COLOR_GREEN << "Enter your guess: " << COLOR_RESET;
                cin >> guess;
                guess = tolower(guess);

                if (!isValidLetter(guess))
                {
                    cout << COLOR_RED << "Invalid guess! Please enter a valid letter." << COLOR_RESET << endl;
                    continue;
                }

                if (guessedLetters.find(guess) != string::npos)
                {
                    cout << COLOR_RED << "You have already guessed that letter!" << COLOR_RESET << endl;
                    continue;
                }

                guessedLetters += guess;

                if (word.find(guess) != string::npos)
                {
                    updateHiddenWord(word, hiddenWord, guess);
                    cout << COLOR_GREEN << "Correct guess!" << COLOR_RESET << endl;
                }
                else
                {
                    attempts--;
                    cout << COLOR_RED << "WRONG GUESS!!" << COLOR_RESET << endl;
                }
                cout << endl;
            }

            cout << COLOR_YELLOW << "Word: " << hiddenWord << COLOR_RESET << endl;
            if (isWordGuessed(hiddenWord))
            {
                cout << COLOR_MAGENTA << "CONGRATULATIONS!! You guessed the word correctly." << COLOR_RESET << endl;
            }
            else
            {
                cout << COLOR_MAGENTA << "Game over! You failed to guess the word. The word was: " << word << COLOR_RESET << endl;
            }
            cout << COLOR_GREEN << "To exit enter 0: " << COLOR_RESET;
            cin >> n;
            if (n != 0)
                system("clear");
        } while (n != 0);

        deallocateResources();
        cout << COLOR_MAGENTA << "\nThank you for playing NEXIS Hangman! Close window to end task\n" << COLOR_RESET;
        sleep(1);
        return 0;
    }
}
