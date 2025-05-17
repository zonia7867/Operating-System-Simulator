#include <iostream>
#include <unistd.h>
#include <stdlib.h> 
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <cstring>
#include <dirent.h>
#include <vector> 
#include <signal.h>
#include <limits>
#include <fstream>

using namespace std;
const string RESET = "\033[0m";
const string CYAN = "\033[36m";
const string YELLOW = "\033[32m";
const string RED = "\033[31m";
const string BOLD = "\033[1m";
bool is_running(pid_t pid) {
    char status_path[64];
    sprintf(status_path, "/proc/%d/status", pid);
    return access(status_path, F_OK) == 0;
}

void force_terminate(pid_t pid) {
    cout << "Attempting to terminate PID " << pid << "..." << endl;

    kill(pid, SIGTERM);
    sleep(1);

    if (is_running(pid)) {
        cout << "Still alive. Sending SIGKILL..." << endl;
        kill(pid, SIGKILL);
        sleep(1);
    }

    int wait_time = 0;
    while (is_running(pid) && wait_time < 20) {
        usleep(100000); // 100ms
        wait_time++;
    }

    if (is_running(pid)) {
        cerr << "Process " << pid << " is still running after SIGKILL.\n";
    } else {
        cout << "Process " << pid << " terminated successfully.\n";
    }
}

int main() {
    system("tput setaf 3");
    cout << "\n------------------------------------------------------------\n";
    cout << "--------------- KERNEL PANEL ---------------\n";
    cout << "------------------------------------------------------------\n\n";
    system("tput sgr0");

    cout << CYAN << "\nProcesses running with cmdline ./obj:\n" << RESET;

    DIR* dir = opendir("/proc");
    if (!dir) {
        cerr << "Failed to open directory /proc.\n";
        return -1;
    }

    struct dirent* ent;
    vector<pid_t> pids;
    while ((ent = readdir(dir)) != NULL) {
        if (ent->d_type != DT_DIR) continue;
        string pid_str = ent->d_name;
        if (pid_str.find_first_not_of("0123456789") != string::npos) continue;
        
        pid_t pid = stoi(pid_str);
        char cmdline_path[64];
        sprintf(cmdline_path, "/proc/%d/cmdline", pid);
        FILE* cmdline_file = fopen(cmdline_path, "r");
        if (!cmdline_file) continue;

        char cmdline[1024];
        size_t len = fread(cmdline, 1, sizeof(cmdline) - 1, cmdline_file);
        fclose(cmdline_file);
        if (len == 0) continue;
        cmdline[len] = '\0';

        if (strstr(cmdline, "./") == cmdline && strstr(cmdline, "./obj") != cmdline + 2) {
            if (is_running(pid)) {
                pids.push_back(pid);
                cout << "PID: " << pid << " → " << cmdline << endl;
            }
        }
    }
    closedir(dir);

    string name;
    int pid;

    while (true) {
        cout << YELLOW << "\n🔧 Enter the process name and PID to deallocate (or -1 to exit): " << RESET;
        if (!(cin >> name >> pid) || name == "-1" || pid == -1) {
            break;
        }

        force_terminate(pid);

        // Compile and run helper to notify deallocation
        string compile_cmd = "g++ -o help helper.cpp";
        string deallocate_cmd = "./help " + name;

        system(compile_cmd.c_str()); 
        system(deallocate_cmd.c_str());  
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\nPress ENTER to exit..." << endl;
    cin.get();

    system("g++ -o deallocate dealloc_resource.cpp");
    system("./deallocate KERNEL");

    return 0;
}
