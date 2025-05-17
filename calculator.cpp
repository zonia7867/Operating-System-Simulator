#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <string>
#include <chrono>
#include <thread>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <pthread.h>
#include <ctime>
#include <cstring>
#include <limits>

using namespace std;

// Define color constants
#define COLOR_RESET "\033[0m"
#define COLOR_CYAN "\033[1;36m"
#define COLOR_YELLOW "\033[1;33m"
#define COLOR_GREEN "\033[1;32m"
#define COLOR_RED "\033[1;31m"
#define COLOR_BLUE "\033[1;34m"
#define COLOR_MAGENTA "\033[1;35m"

// Function to clear input buffer
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Function to validate and get operation choice
int getValidChoice() {
    int choice;
    while (true) {
        cout << COLOR_GREEN << "Enter your choice (1-5): " << COLOR_RESET;
        if (cin >> choice && choice >= 1 && choice <= 5) {
            clearInputBuffer();
            return choice;
        } else {
            cout << COLOR_RED << "Invalid choice. Please enter a number from 1 to 5.\n" << COLOR_RESET;
            clearInputBuffer();
        }
    }
}

// Function to validate and get a number
float getValidNumber(const string& prompt) {
    float num;
    while (true) {
        cout << COLOR_CYAN << prompt << COLOR_RESET;
        if (cin >> num) {
            clearInputBuffer();
            return num;
        } else {
            cout << COLOR_RED << "Invalid number. Please enter a valid number.\n" << COLOR_RESET;
            clearInputBuffer();
        }
    }
}

// Function to display result in a boxed format
void displayResult(float num1, float num2, char op, float result) {
    cout << COLOR_GREEN << "┌──────────────────────────┐\n";
    cout << "│ " << COLOR_YELLOW << "Result: " << num1 << " " << op << " " << num2 << " = " << result << COLOR_GREEN << " │\n";
    cout << "└──────────────────────────┘\n\n" << COLOR_RESET;
}

// Function to ask if user wants to continue
bool askToContinue() {
    char cont;
    while (true) {
        cout << COLOR_MAGENTA << "Do you want to perform another calculation? (y/n): " << COLOR_RESET;
        cin >> cont;
        clearInputBuffer();
        if (cont == 'y' || cont == 'Y') return true;
        if (cont == 'n' || cont == 'N') return false;
        cout << COLOR_RED << "Invalid input. Please enter 'y' or 'n'.\n" << COLOR_RESET;
    }
}

// Function to notify main process of termination
void deallocateResources() {
    const char *moyemoyeFifo = "/tmp/moyemoyeFifo";
    int fd = open(moyemoyeFifo, O_WRONLY | O_NONBLOCK);
    if (fd != -1) {
        const char *msg = "CALCULATOR";
        write(fd, msg, strlen(msg) + 1);
        close(fd);
    } else {
        perror("Error opening FIFO for deallocation");
    }
}

int main() {
    // Display ASCII art header
    system("clear");
    cout << COLOR_YELLOW << "\tWelcome to NEXIS Calculator!\n\n" << COLOR_RESET;

    bool exitFlag = false;
    do {
        // Display menu options
        cout << COLOR_BLUE << "┌────────────── Menu ─────────────┐\n";
        cout << "│ " << COLOR_MAGENTA << "1. Addition (+)" << COLOR_BLUE << "                 │\n";
        cout << "│ " << COLOR_MAGENTA << "2. Subtraction (-)" << COLOR_BLUE << "              │\n";
        cout << "│ " << COLOR_MAGENTA << "3. Multiplication (*)" << COLOR_BLUE << "           │\n";
        cout << "│ " << COLOR_MAGENTA << "4. Division (/)" << COLOR_BLUE << "                 │\n";
        cout << "│ " << COLOR_MAGENTA << "5. Exit" << COLOR_BLUE << "                         │\n";
        cout << "└─────────────────────────────────┘\n\n" << COLOR_RESET;

        // Get user input for choice
        int choice = getValidChoice();

        if (choice == 5) {
            exitFlag = true;
            break;
        }

        // Get two numbers for arithmetic operations
        float num1 = getValidNumber("Enter the first number: ");
        float num2 = getValidNumber("Enter the second number: ");

        // Execute chosen operation
        switch (choice) {
            case 1:
                displayResult(num1, num2, '+', num1 + num2);
                break;
            case 2:
                displayResult(num1, num2, '-', num1 - num2);
                break;
            case 3:
                displayResult(num1, num2, '*', num1 * num2);
                break;
            case 4:
                if (num2 == 0) {
                    cout << COLOR_RED << "┌──────────────────────────┐\n";
                    cout << "│ Error: Division by zero! │\n";
                    cout << "└──────────────────────────┘\n\n" << COLOR_RESET;
                } else {
                    displayResult(num1, num2, '/', num1 / num2);
                }
                break;
            default:
                cout << COLOR_RED << "Unexpected error in choice selection.\n\n" << COLOR_RESET;
                break;
        }

        // Ask if user wants to continue
        if (!askToContinue()) {
            exitFlag = true;
        }
        system("clear");
    } while (!exitFlag);

    // Notify main process of termination
    deallocateResources();

    cout << COLOR_CYAN << "\nThank you for using NEXIS Calculator! Close window to end task\n" << COLOR_RESET;
    sleep(1);
    return 0;
}