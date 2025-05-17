#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;


const string RESET = "\033[0m";
const string CYAN = "\033[34m";
const string GREEN = "\033[32m";
const string RED = "\033[31m";
const string YELLOW = "\033[35m";
const string BOLD = "\033[1m";

int main() {
    srand(static_cast<unsigned int>(time(0)));
    int secretNumber = rand() % 100 + 1;
    int guess, attempts = 0;
    int n;

    cout << BOLD << CYAN << "*----- Welcome to NEXIS Number Guessing Game!-----*" << RESET << endl;
    cout << RED << "To quit anytime, enter 0" << RESET << endl;
    cout << "Enter 1 to play: ";
    cin >> n;

    while (n != 0) {
        attempts = 0;
        secretNumber = rand() % 100 + 1; 

        while (true) {
            cout << YELLOW << "\n Enter your guess (1-100): " << RESET;
            cin >> guess;

            if (guess == 0) {
                cout << RED << " Game exited by user." << RESET << endl;
                break;
            }

            attempts++;

            if (guess == secretNumber) {
                cout << GREEN << " Congratulations! You guessed the correct number in "
                     << attempts << " attempts." << RESET << endl;
                break;
            } else if (guess < secretNumber) {
                cout << "Too low! Try again." << endl;
            } else {
                cout << "Too high! Try again."  << endl;
            }
        }

        cout << CYAN << "\nEnter 0 to exit or 1 to play again: " << RESET;
        cin >> n;
        if (n != 0) system("clear");
    }

    
    system("g++ -o deallocate dealloc_resource.cpp");
    system("./deallocate NUMBERGUESSING");

    return 0;
}
