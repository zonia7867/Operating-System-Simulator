#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const string RESET = "\033[0m";
const string CYAN = "\033[36m";
const string GREEN = "\033[32m";
const string RED = "\033[31m";
const string YELLOW = "\033[34m";
const string BOLD = "\033[1m";

int main() {
    string fileName;
    string extention;
    int choice;

    cout << BOLD << GREEN << "--> Enter File Name: " << RESET;
    cin >> fileName;

    do {
        cout << YELLOW << "\nSelect file extension:\n"
             << "1. Text (.txt)\n"
             << "2. Data (.dat)\n"
             << "Choice: " << RESET;
        cin >> choice;

        if (choice == 1) {
            extention = ".txt";
        } else if (choice == 2) {
            extention = ".dat";
        } else {
            cout << RED << " Invalid choice. Please select 1 or 2." << RESET << endl;
        }
    } while (choice < 1 || choice > 2);

    fileName += extention;

    ofstream obj;
    ifstream temp(fileName);

    if (temp.fail()) {
        obj.open(fileName);
        if (obj.fail()) {
            cout << RED << " File could not be created." << RESET << endl;
        } else {
            cout << GREEN << " File created successfully: " << fileName << RESET << endl;
        }
    } else {
        cout << CYAN << " File already exists: " << fileName << RESET << endl;
    }

    cin.ignore();
    cout << YELLOW << "\n\t\tPress ENTER to exit..." << RESET << endl;
    cin.get();

    // Notify deallocation
    system("g++ -o deallocate dealloc_resource.cpp");
    system("./deallocate CREATE");

    return 0;
}
