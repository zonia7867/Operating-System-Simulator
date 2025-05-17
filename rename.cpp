#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const string RESET = "\033[0m";
const string CYAN = "\033[34m";
const string GREEN = "\033[32m";
const string RED = "\033[31m";
const string YELLOW = "\033[33m";

int main()
{
    string fileName;
    string extension;
    string newName;
    int choice;

    cout << CYAN << "Enter File Name: " << RESET;
    cin >> fileName;

    do {
        cout << GREEN << "Select extension:" << endl
             << "1. Text (.txt)" << endl
             << "2. Data (.dat)" << endl
             << "Choice: " << RESET; 
        cin >> choice;

        if (choice == 1) {
            extension = ".txt";
        } else if (choice == 2) {
            extension = ".dat";
        } else {
            cout << "Wrong Extension" << endl;
        }
    } while (choice < 1 || choice > 2);

    fileName = fileName + extension;
    ifstream temp;
    temp.open(fileName);

    if (temp.fail()) {
        cout  << RED << "No file with this name exists\n" << RESET;
    } else {
        cout << "Enter New Name of File: ";
        cin >> newName;
        temp.close();
        rename(fileName.c_str(), newName.c_str());
    }

    cin.ignore();
    cout << RED << "\t\t\t" << "Press any key to Exit...\n" << RESET;
    cin.get();

    system("g++ -o deallocate dealloc_resource.cpp");
    system("./deallocate RENAME");

    return 0;
}

