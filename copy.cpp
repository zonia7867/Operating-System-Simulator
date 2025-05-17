#include <iostream>
#include <fstream>
#include <string>
using namespace std;


const string RESET = "\033[0m";
const string CYAN = "\033[36m";
const string GREEN = "\033[32m";
const string RED = "\033[31m";
const string YELLOW = "\033[33m";
const string BOLD = "\033[1m";

int main() {
    string sourceFileName, destinationFileName;

    cout << BOLD << CYAN << "Enter the name of the source file: " << RESET;
    cin >> sourceFileName;

    cout << CYAN << "Enter the name of the destination file: " << RESET;
    cin >> destinationFileName;

    ifstream sourceFile(sourceFileName);
    if (!sourceFile) {
        cout << RED << "Failed to open the source file." << RESET << endl;
        system("g++ -o deallocate dealloc_resource.cpp");
        system("./deallocate COPY");
        return 1;
    }

    ofstream destinationFile(destinationFileName);
    if (!destinationFile) {
        cout << RED << "Failed to create or open the destination file." << RESET << endl;
        system("g++ -o deallocate dealloc_resource.cpp");
        system("./deallocate COPY");
        return 1;
    }

    string line;
    while (getline(sourceFile, line)) {
        destinationFile << line << endl;
    }

    cout << GREEN << "File copied successfully from '" 
         << sourceFileName << "' to '" << destinationFileName << "'." << RESET << endl;

    sourceFile.close();
    destinationFile.close();

    system("g++ -o deallocate dealloc_resource.cpp");
    system("./deallocate COPY");

    return 0;
}
