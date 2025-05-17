#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

using namespace std;

const string RESET = "\033[0m";
const string CYAN = "\033[36m";
const string YELLOW = "\033[33m";
const string BOLD = "\033[1m";
const string MAGENTA = "\033[35m";
const string RED = "\033[31m";  

string repeat(const string& s, int n) {
    string result;
    for (int i = 0; i < n; ++i)
        result += s;
    return result;
}

void display(const string& text) {

    cout << MAGENTA << text << MAGENTA << RESET;
}

int main() {
    const char* quotes[] = {
        "Nothing is heavier on the Scale of Deeds than one’s good manners.",
        "The most beloved of Allah’s slaves to Allah are those with the best manners.",
        "Allah will not show mercy to a person who does not show mercy to other people.",
        "A good word is charity.",
        "Whoever desires more wealth and a long life should maintain family ties.",
        "Show mercy and you will be shown mercy. Forgive and Allah will forgive you."
    };
    const int numQuotes = sizeof(quotes) / sizeof(quotes[0]);
    srand(time(0));
    int randomIndex = rand() % numQuotes;

    cout << "\n\n\t\t Hadith of the Day:\n";
    cout << "\n\t\t*-----------------------*\n\n";

display(quotes[randomIndex]);

    cout << "\nPress ENTER to exit...";
    cin.ignore(); 

    // Notify deallocation
    system("g++ -o deallocate dealloc_resource.cpp");
    system("./deallocate QUOTES");

    return 0;
}
