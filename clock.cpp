#include <iostream>
#include <cstdlib>
#include <unistd.h>

using namespace std;

const string COLOR_RESET = "\033[0m";
const string COLOR_GREEN = "\033[1;32m";
const string COLOR_YELLOW = "\033[1;33m";
const string COLOR_RED = "\033[1;31m";

int main()
{
    system("clear");
    cout << COLOR_GREEN << "\n\n\t\t NEXIS Clock\n" << COLOR_RESET;
    cout << "\t\t*---------------*\n";
sleep(2);
system("clear");
    
    system("tty-clock -Sra 100000000 -d 0");

    
    cout << COLOR_RED << "\t\t\tPress ENTER to Exit..." << COLOR_RESET << endl;
    cin.ignore(); 
    cin.get();    

    
    system("g++ -o deallocate dealloc_resource.cpp");
    system("./deallocate CLOCK");

    return 0;
}
