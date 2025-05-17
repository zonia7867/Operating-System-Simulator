#include <cstdlib>
#include <iostream>
#include <string>
#include <unistd.h> 

using namespace std;

const string RESET = "\033[0m";
const string BLUE = "\033[34m";
int main()
{
    string filename;
    cout << BLUE << "Enter the name of the video file to play: "<< RESET;
    getline(cin, filename);

    
    if (access((filename + ".mpv").c_str(), F_OK) != -1)
    {
        string command = "mpv " + filename + ".mpv &";
        system(command.c_str());

        cout << "Press any key to stop playing the video...";
        cin.ignore();
        cin.get();

        
        system("killall mpv");

         system("g++ -o deallocate dealloc_resource.cpp");
         system("./deallocate VIDEO_PLAYER");
    }
    else
    {
        cerr << "Error: File not found." << endl;
    }

    return 0;
}


