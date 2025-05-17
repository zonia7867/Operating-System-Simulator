#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <iomanip>
#include <sys/ioctl.h>
#include <pthread.h>
#include <vector>
#include <string>
#include <semaphore.h>
#include <dirent.h>
#include <cstring>

using namespace std;

// Define color constants
#define COLOR_RESET "\033[0m"
#define COLOR_CYAN "\033[1;36m"
#define COLOR_YELLOW "\033[1;33m"
#define COLOR_GREEN "\033[1;32m"
#define COLOR_RED "\033[1;31m"
#define COLOR_BLUE "\033[1;34m"
#define COLOR_MAGENTA "\033[1;35m"

#define MAX 15

string process_sequence_name[MAX] = {"TOWEROFHANOI", "CALCULATOR", "HANGMAN", "NUMBERGUESSING", "MUSICPLAYER", "QUOTES", "CREATE", "DELETE", "COPY", "CALENDER", "CLOCK", "VIDEOPLAYER", "RENAME", "NOTEPAD", "KERNEL"};
const char *moyemoyeFifo = "/tmp/MONMOI/fifo";
long int ramSize = 0, storageDevice = 0, cores = 0;
long int need[MAX] = {0};
int core_threads = 0;
int active_processes[MAX] = {0};
int **active_cores;
bool mode;
int k_choice;
vector<int> readyQueue;
vector<int> waitingQueue;

pthread_t ptid;
pthread_t dispatcher;
pthread_t switcher;

sem_t semaphore;

void printMainMenu();
void displayRunningProcs();

bool check_free_cores()
{
    for (int i = 0; i < cores; ++i)
        for (int j = 0; j < core_threads; ++j)
            if (active_cores[i][j] == -1)
                return true;
    return false;
}

void assign_core(int process)
{
    for (int i = 0; i < cores; ++i)
        for (int j = 0; j < core_threads; ++j)
            if (active_cores[i][j] == -1)
            {
                active_cores[i][j] = process;
                return;
            }
}

void dealloc_core(int process)
{
    for (int i = 0; i < cores; ++i)
        for (int j = 0; j < core_threads; ++j)
            if (active_cores[i][j] == process)
            {
                active_cores[i][j] = -1;
                return;
            }
}

void display_running_cores(void)
{
    for (int i = 0; i < cores; ++i)
    {
        for (int j = 0; j < core_threads; ++j)
        {
            if (active_cores[i][j] != -1)
            {
                cout << COLOR_CYAN << "Core " << i + 1 << " Thread " << j + 1 << " is executing:" << COLOR_RESET << "\n"
                     << COLOR_YELLOW << "Process \"" << process_sequence_name[active_cores[i][j]] << "\"" << COLOR_RESET << "\n"
                     << COLOR_BLUE << "--------------------------------" << COLOR_RESET << "\n\n";
            }
        }
    }
}

void delete_pipefile()
{
    if (access(moyemoyeFifo, F_OK) != -1)
    {
        system("rm /tmp/moyemoyeFifo");
        if (unlink(moyemoyeFifo) != 0)
        {
            perror("Error deleting file");
        }
    }
}

void release_resources(char *str)
{
    string str1, str2;
    int index = -1;

    for (int i = 0; i < 15; ++i)
    {
        str1 = process_sequence_name[i];
        str2 = str;
        if (str1 == str2)
        {
            index = i;
            break;
        }
    }

    if (index != -1)
    {
        system("clear");
        dealloc_core(index);
        sem_wait(&semaphore);
        active_processes[index] -= 1;
        ramSize += need[index];
        sem_post(&semaphore);
        cout << COLOR_GREEN << "Resources freed for " << process_sequence_name[index] << COLOR_RESET << endl;
        displayRunningProcs();
        printMainMenu();
    }
}

void *thread_for_inter_terminal_comm(void *arg)
{
    int fd;
    const char *moyemoyeFifo = "/tmp/moyemoyeFifo";
    mkfifo(moyemoyeFifo, 0666);

    char arr1[80];
    while (true)
    {
        fd = open(moyemoyeFifo, O_RDONLY);
        if (fd == -1) {
            perror("Error opening FIFO");
            sleep(1);
            continue;
        }
        read(fd, arr1, sizeof(arr1));
        string temp = "notify-send '" + string(arr1) + " Has Been Closed!'";
        system(temp.c_str());
        release_resources(arr1);
        close(fd);
    }
}

void print_centered(string message)
{
    system("clear");
    cout << "\n\n";
    cout << COLOR_CYAN;
    cout << "   ___   __   ___  __   __   _   ___\n";
    cout << "  |   \\  | | |   | \\\\  / /  | | | __|\n";
    cout << "  | |\\ \\ | | | __|  \\\\/ /   | | | |__\n";
    cout << "  | | \\ \\| | | |_   / /\\\\   | |  _   |\n";
    cout << "  |_|  \\___| |___| /_/  \\_\\ |_| |____| \n";
    cout << "\n\n";
    cout << COLOR_RESET;
    cout << COLOR_YELLOW << "    Initializing NEXIS Operating System...\n\n" << COLOR_RESET;
    
    for (int i = 0; i <= 100; i += 10)
    {
        cout << COLOR_GREEN << "["; 
        for (int j = 0; j < i / 10; j++)
            cout << "█";
        for (int j = i / 10; j < 10; j++)
            cout << " ";
        cout << "] " << i << "%" << COLOR_RESET << "\r";
        cout.flush();
        usleep(200000);
    }
    cout << "\n\n";
    
    cout << COLOR_MAGENTA << "By Zonia Amer and Abrar Fazal\n\n" << COLOR_RESET;
    sleep(2);
    system("clear");
}

void shut_down()
{
    cout << "Shutting down the system...";
    cout << "Goodbye!";
    cout << COLOR_YELLOW;
    cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << endl;
    cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⣉⣙⣷⡦⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << endl;
    cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢤⣴⠖⠛⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << endl;
    cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⣉⠛⠓⠶⢤⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << endl;
    sleep(1);
    cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣤⣽⡿⠟⠁⠀⠀⠀⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << endl;
    cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠙⠛⠷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << endl;
    cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⣤⣤⣤⣤⣀⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << endl;
    cout << "⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⣤⡶⠶⠛⠉⠉⠉⠉⠁⠀⠀⠀⠀⠉⠙⠿⠓⠒⠶⢺⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << endl;
    cout << "⢶⡶⠶⠶⠶⠖⠖⠛⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣴⡟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << endl;
    sleep(1);
    cout << "⠘⣧⡀⠀⠀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣼⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << endl;
    cout << "⠀⠈⠻⢤⣼⡏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⣏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << endl;
    cout << "⠀⠀⠀⠀⢻⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⡀⢀⣿⡿⠶⠶⣤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << endl;
    cout << "⠀⠀⠀⠀⢸⡇⠀⣀⣀⠀⢀⣀⣤⡀⠀⠀⠀⠀⠸⠶⠶⠚⠛⠋⢹⣿⣿⣟⣉⠉⠒⠀⠻⣦⣠⣤⣤⣤⣄⣀⠀⠀" << endl;
    cout << "⠀⢀⣤⢾⣿⣷⣶⡍⠙⠙⠛⠋⠉⠀⠀⢴⡶⠀⠀⠀⠀⢀⣠⡶⠟⠛⠛⣷⠀⠉⠁⠀⠀⠈⣧⡀⠀⠩⣀⠈⢹⣆" << endl;
    cout << "⠀⣠⢉⡴⢿⣿⡟⠛⠛⠛⠶⣤⣀⠀⠀⠀⠀⠀⠀⣴⡿⠋⠀⠀⠀⢀⡉⠀⠀⠀⠀⢀⣼⠛⠛⢛⣿⡿⠀⣾⡟" << endl;
    sleep(1);
    cout << "⠀⠁⣰⠋⢀⡿⠁⠀⠀⠀⠀⠀⠀⠉⠻⣦⡀⠀⠀⣼⠟⠀⠀⠀⢀⣠⣾⢁⣀⣤⣴⡶⠟⣁⣴⠞⠋⠉⢀⣼⣿⠁" << endl;
    cout << "⠀⠀⠉⠀⠈⠷⣄⡀⠀⠀⠀⠀⠀⠀⠀⠈⢿⡗⠚⡏⠀⢀⣤⡶⠛⠋⠉⠉⠉⠉⠀⣠⣾⠟⢁⣀⣤⣶⣿⠟⠁⠀" << endl;
    cout << "⠀⠀⠀⠀⠀⠀⠀⠈⠉⠑⠲⠤⣄⣦⣤⡴⠞⠁⠀⠉⠙⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠹⠿⠾⠾⠟⠛⠁⠀⠀⠀⠀" << endl;
    sleep(5);
    cout << COLOR_RESET;
}

void *process_shifter(void *argv)
{
    while (true)
    {
        bool foundProcess = false;
        for (int i = 0; i < waitingQueue.size(); ++i)
        {
            if (need[waitingQueue[i] - 1] <= ramSize && check_free_cores())
            {
                int process = waitingQueue[i];
                waitingQueue.erase(waitingQueue.begin() + i);
                readyQueue.push_back(process);
                foundProcess = true;
                cout << COLOR_YELLOW << process_sequence_name[process - 1] << COLOR_RESET << " moved from waiting queue to ready queue!" << endl;
                break;
            }
        }
        if (!foundProcess)
        {
            usleep(100000); // Sleep briefly to avoid busy-waiting
        }
    }
    return NULL;
}

void displayRunningProcs()
{
    bool noProcFlag = true;
    system("clear");
    cout << COLOR_GREEN << "\n\t🚨 RESOURCE MONITOR 🚨\n" << COLOR_RESET;
    cout << COLOR_CYAN << "┌────────────────────────────┐\n";
    cout << "│ " << COLOR_YELLOW << "Remaining RAM    → " << ramSize << " MB" << COLOR_CYAN << "|\n";
    cout << "│ " << COLOR_YELLOW << "Remaining Storage → " << storageDevice << " MB" << COLOR_CYAN << "│\n";
    cout << "│ " << COLOR_YELLOW << "Available Cores  → " << cores << COLOR_CYAN << "       │\n";
    cout << "│ " << COLOR_YELLOW << "Threads per Core → " << core_threads << COLOR_CYAN << "     │\n";
    cout << "└────────────────────────────┐\n\n" << COLOR_RESET;
    display_running_cores();
    cout << COLOR_CYAN << "\nRunning Processes:\n" << COLOR_RESET;
    for (int i = 0; i < 15; ++i)
    {
        if (active_processes[i])
        {
            cout << COLOR_GREEN << "    ✔ " << COLOR_YELLOW << process_sequence_name[i] 
                 << COLOR_RESET << " is running " << COLOR_BLUE << active_processes[i] 
                 << COLOR_RESET << " time(s)\n";
            noProcFlag = false;
        }
    }
    if (noProcFlag)
    {
        cout << COLOR_RED << "\n    No processes are currently running.\n" << COLOR_RESET;
    }
    cout << COLOR_CYAN << "\nReady Queue:\n" << COLOR_RESET;
    if (readyQueue.empty())
    {
        cout << COLOR_RED << "    No processes in ready queue.\n" << COLOR_RESET;
    }
    else
    {
        for (int process : readyQueue)
        {
            cout << COLOR_YELLOW << "    - " << process_sequence_name[process - 1] << COLOR_RESET << "\n";
        }
    }
    cout << COLOR_CYAN << "\nWaiting Queue:\n" << COLOR_RESET;
    if (waitingQueue.empty())
    {
        cout << COLOR_RED << "    No processes in waiting queue.\n" << COLOR_RESET;
    }
    else
    {
        for (int process : waitingQueue)
        {
            cout << COLOR_YELLOW << "    - " << process_sequence_name[process - 1] << COLOR_RESET << "\n";
        }
    }
    cout << COLOR_GREEN << "\n═══════════════════════════════════════════════════════\n" << COLOR_RESET;
}

void *dispatch(void *argv)
{
    int active = -1;
    while (true)
    {
        if (!readyQueue.empty())
        {
            active = readyQueue.front();
            readyQueue.erase(readyQueue.begin());
        }
        else
            active = -1;

        if (active != -1)
        {
            active_processes[active - 1]++;
            ramSize -= need[active - 1];
            cout << COLOR_YELLOW << process_sequence_name[active - 1] << COLOR_RESET << " has been dispatched from the ready queue!" << endl;
            assign_core(active - 1);
            system("clear");
            displayRunningProcs();

            string compile_cmd, exec_cmd;
            switch (active)
            {
            case 1: // Tower of Hanoi
                compile_cmd = "g++ -o towerofhanoi towerofhanoi.cpp";
                exec_cmd = "xterm -hold -e './towerofhanoi' &";
                if (access("towerofhanoi", F_OK) == -1)
                    system(compile_cmd.c_str());
                system(exec_cmd.c_str());
                break;
            case 2: // Calculator
                compile_cmd = "g++ -o calculator calculator.cpp";
                exec_cmd = "xterm -hold -e './calculator' &";
                if (access("calculator", F_OK) == -1)
                    system(compile_cmd.c_str());
                system(exec_cmd.c_str());
                break;
            case 3: // Hangman
                compile_cmd = "g++ -o hangman hangman.cpp";
                exec_cmd = "xterm -hold -e './hangman' &";
                if (access("hangman", F_OK) == -1)
                    system(compile_cmd.c_str());
                system(exec_cmd.c_str());
                break;
            case 4: // Number Guessing
                compile_cmd = "g++ -o numberguessing numberguessing.cpp";
                exec_cmd = "xterm -hold -e './numberguessing' &";
                if (access("numberguessing", F_OK) == -1)
                    system(compile_cmd.c_str());
                system(exec_cmd.c_str());
                break;
            case 5: // Music Player
                compile_cmd = "g++ -o music music.cpp";
                exec_cmd = "xterm -hold -e './music' &";
                if (access("music", F_OK) == -1)
                    system(compile_cmd.c_str());
                system(exec_cmd.c_str());
                break;
            case 6: // Quotes
                compile_cmd = "g++ -o quotes quotes.cpp";
                exec_cmd = "xterm -hold -e './quotes' &";
                if (access("quotes", F_OK) == -1)
                    system(compile_cmd.c_str());
                system(exec_cmd.c_str());
                break;
            case 7: // Create
                compile_cmd = "g++ -o create create.cpp";
                exec_cmd = "xterm -hold -e './create' &";
                if (access("create", F_OK) == -1)
                    system(compile_cmd.c_str());
                system(exec_cmd.c_str());
                break;
            case 8: // Delete
                compile_cmd = "g++ -o delete delete.cpp";
                exec_cmd = "xterm -hold -e './delete' &";
                if (access("delete", F_OK) == -1)
                    system(compile_cmd.c_str());
                system(exec_cmd.c_str());
                break;
            case 9: // Copy
                compile_cmd = "g++ -o copy copy.cpp";
                exec_cmd = "xterm -hold -e './copy' &";
                if (access("copy", F_OK) == -1)
                    system(compile_cmd.c_str());
                system(exec_cmd.c_str());
                break;
            case 10: // Calendar
                compile_cmd = "g++ -o calender calender.cpp";
                exec_cmd = "xterm -hold -e './calender' &";
                if (access("calender", F_OK) == -1)
                    system(compile_cmd.c_str());
                system(exec_cmd.c_str());
                break;
            case 11: // Clock
                compile_cmd = "g++ -o clock clock.cpp";
                exec_cmd = "xterm -hold -e './clock' &";
                if (access("clock", F_OK) == -1)
                    system(compile_cmd.c_str());
                system(exec_cmd.c_str());
                break;
            case 12: // Video Player
                compile_cmd = "g++ -o tictactoe tictactoe.cpp";
                exec_cmd = "xterm -hold -e './tictactoe' &";
                if (access("tictactoe", F_OK) == -1)
                    system(compile_cmd.c_str());
                system(exec_cmd.c_str());
                break;
            case 13: // Rename
                compile_cmd = "g++ -o rename rename.cpp";
                exec_cmd = "xterm -hold -e './rename' &";
                if (access("rename", F_OK) == -1)
                    system(compile_cmd.c_str());
                system(exec_cmd.c_str());
                break;
            case 14: // Notepad
                compile_cmd = "g++ -o notepad notepad.cpp";
                exec_cmd = "xterm -hold -e './notepad' &";
                if (access("notepad", F_OK) == -1)
                    system(compile_cmd.c_str());
                system(exec_cmd.c_str());
                break;
            case 15: // Kernel
                compile_cmd = "g++ -o kernel kernel.cpp";
                exec_cmd = "xterm -hold -e './kernel' &";
                if (access("kernel", F_OK) == -1)
                    system(compile_cmd.c_str());
                system(exec_cmd.c_str());
                break;
            }
        }
    }
}

void printMainMenu()
{
    cout << COLOR_GREEN << "\n┌────────────────────── NEXIS USER DESKTOP ─────────────────────┐\n";
    cout << "└───────────────────────────────────────────────────────────────┘\n\n" << COLOR_RESET;
    cout << COLOR_CYAN << "Choose your next action...\n\n" << COLOR_RESET;
    cout << COLOR_YELLOW << " 1. 🗼 Tower of Hanoi\n";
    cout << " 2. 🧮 Calculator\n";
    cout << " 3. 🎮 Hangman\n";
    cout << " 4. 🔢 Number Guessing\n";
    cout << " 5. 🎵 Music Player\n";
    cout << " 6. 💬 Quote\n";
    cout << " 7. 📄 Create a File\n";
    cout << " 8. 🗑️ Delete a File\n";
    cout << " 9. 📋 Copy a File\n";
    cout << "10. 📅 Calendar\n";
    cout << "11. ⏰ Clock\n";
    cout << "12. 🎥 Video Player\n";
    cout << "13. ✏️ Rename a File\n";
    cout << "14. 📝 Notepad\n";
    cout << "15. ⚙️ Kernel Mode\n";
    cout << "16. 🚪 Terminate the OS\n\n" << COLOR_RESET;
    cout << COLOR_GREEN << "Enter your choice: " << COLOR_RESET;
}

void scheduler(void)
{
    int choice;
    while (true)
    {
        displayRunningProcs();
        printMainMenu();
        cin >> choice;
        if (choice == 16)
        {
            system("clear");
            pthread_cancel(ptid);
            pthread_cancel(dispatcher);
            pthread_cancel(switcher);
            cout << "Terminating all the processes" << endl;
            sleep(2);
            system("clear");
            shut_down();
            sleep(2);
            system("killall -9 xterm");
            exit(0);
        }
        if (choice <= 16 && choice >= 1)
        {
            if ((ramSize >= need[choice - 1]) && check_free_cores())
            {
                readyQueue.push_back(choice);
            }
            else
            {
                system("notify-send 'NOT ENOUGH SPACE OR CORES'");
                waitingQueue.push_back(choice);
                cout << COLOR_YELLOW << process_sequence_name[choice - 1] << COLOR_RESET << " added to waiting queue due to insufficient resources or cores." << endl;
                sleep(1);
                continue;
            }
        }
    }
}

int main()
{
    delete_pipefile();
    sem_init(&semaphore, 0, 1);
    
    // Initialize process resource needs
    need[0] = 150;
    need[1] = 50;
    need[2] = 100;
    need[3] = 900;
    need[4] = 100;
    need[5] = 150;
    need[6] = 100;
    need[7] = 50;
    need[8] = 100;
    need[9] = 50;
    need[10] = 50;
    need[11] = 50;
    need[12] = 50;
    need[13] = 50;
    need[14] = 100;

    // Display welcome screen
    print_centered("");

    // Prompt for kernel or user mode
    cout << COLOR_CYAN << "Select Operating Mode:\n" << COLOR_RESET;
    cout << COLOR_YELLOW << "0. Kernel Mode\n";
    cout << "1. User Mode\n" << COLOR_RESET;
    cout << COLOR_GREEN << "Enter your choice (0 or 1): " << COLOR_RESET;
    cin >> mode;
    system("clear");

    int mod = 0, res;
    if (mode == 0)
    {
        system("notify-send 'Kernel Mode'");
        cout << "Enter 1 to update resources or -1 to not" << endl;
        int c;
        cin >> c;
        if (c == 1)
        {
            for (int i = 0; i < MAX; i++)
            {
                cout << i << " " << process_sequence_name[i] << " " << need[i] << endl;
            }
            while (mod != -1)
            {
                cout << "Enter the number of the process which you want to change the resources for or -1 to exit" << endl;
                cin >> mod;
                if (mod != -1)
                {
                    cout << "Enter the new resources" << endl;
                    cin >> res;
                    need[mod] = res;
                    cout << "to continue press 1 to exit press -1" << endl;
                    cin >> mod;
                }
            }
        }
    }
    system("clear");

    do
    {
        cout << "Enter the amount of RAM in GB: ";
        cin >> ramSize;
        cout << endl;
        cout << "Enter the size of HDD in GB: ";
        cin >> storageDevice;
        cout << endl;
        cout << "Enter the number of cores: ";
        cin >> cores;
        cout << endl;
        cout << "Enter the number of threads per core: ";
        cin >> core_threads;
        cout << endl;
        if (ramSize <= 0)
        {
            cout << "Invalid RAM size. Please enter a positive value." << endl;
            return 1;
        }
        if (storageDevice <= 0)
        {
            cout << "Invalid HDD size. Please enter a positive value." << endl;
            return 1;
        }
        if (cores <= 0)
        {
            cout << "Invalid number of cores. Please enter a positive value." << endl;
            return 1;
        }
        if (core_threads <= 0)
        {
            cout << "Invalid number of threads per core. Please enter a positive value." << endl;
            return 1;
        }
        if (core_threads <= 1)
        {
            cout << "Insufficient number of threads. Please enter a value greater than 1." << endl;
        }
        system("clear");
    } while (ramSize == 0 || storageDevice == 0 || core_threads <= 1 || cores == 0);

    ramSize = ramSize * 1024;
    storageDevice = storageDevice * 1024;

    system("clear");
    int status;
    pthread_create(&dispatcher, NULL, dispatch, NULL);
    pthread_create(&switcher, NULL, process_shifter, NULL);
    pthread_create(&ptid, NULL, thread_for_inter_terminal_comm, NULL);

    active_cores = new int *[cores];
    for (int i = 0; i < cores; ++i)
        active_cores[i] = new int[core_threads];
    for (int i = 0; i < cores; ++i)
        for (int j = 0; j < core_threads; ++j)
            active_cores[i][j] = -1;

    scheduler();
    pthread_join(ptid, NULL);
    pthread_join(dispatcher, NULL);
    pthread_join(switcher, NULL);

    return 0;
}
