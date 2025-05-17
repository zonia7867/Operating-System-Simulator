#include <iostream>
#include <cstdlib>
using namespace std;


const string RESET = "\033[0m";
const string CYAN = "\033[36m";
const string GREEN = "\033[32m";
const string RED = "\033[31m";
const string BOLD = "\033[1m";

int main() {
    string mp3File = "song.mp3"; 

    cout << BOLD << CYAN << "Now playing: " << mp3File << RESET << endl;

    
    int status = system(("mpg123 \"" + mp3File + "\"").c_str());

    if (status != 0) {
        cout << RED << "Failed to play the file. Make sure mpg123 is installed and the file exists." << RESET << endl;
    }

    cout << GREEN << "\nFinished playing.\n" << RESET;
    cout << CYAN << "\t\tPress ENTER to exit..." << RESET << endl;
    cin.ignore();
    cin.get();

    
    system("g++ -o deallocate dealloc_resource.cpp");
    system("./deallocate QUOTES");

    return 0;
}
