#include <iostream>
#include <iomanip>
using namespace std;

#define COLOR_RESET "\033[0m"
#define COLOR_CYAN "\033[1;36m"
#define COLOR_YELLOW "\033[1;33m"
#define COLOR_GREEN "\033[1;32m"
#define COLOR_RED "\033[1;31m"
#define COLOR_MAGENTA "\033[1;35m"
#define BOLD "\033[1m"

int main() {
    // Get input for the year and month
    int year, month;
    cout << COLOR_MAGENTA << "Enter the year: " <<COLOR_RESET;
    cin >> year;
    cout << COLOR_MAGENTA << "Enter the month (1-12): " << COLOR_RESET;
    cin >> month;

    if(month<1 || month >12) {
	cout << COLOR_RED << "Invalid Input. Enter number from 1 to 12\n" << COLOR_RESET;
	cin >> month;
	}

    // Calculate the total number of days in the month
    int daysInMonth;
    if (month == 2) {
        // Check for leap year
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            daysInMonth = 29;
        } else {
            daysInMonth = 28;
        }
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        daysInMonth = 30;
    } else {
        daysInMonth = 31;
    }

    // Calculate the weekday of the first day of the month
    int q = 1;  // Day of the month
    int m = month < 3 ? month + 12 : month;
    int K = year % 100;
    int J = year / 100;
    int h = (q + 13 * (m + 1) / 5 + K + K / 4 + J / 4 + 5 * J) % 7;
    

    const int calendarWidth = 33; 
    const int padding = (80 - calendarWidth) / 2; 

    
    cout << string(padding, ' ') << COLOR_CYAN << "┌───────────────────────────────┐" << COLOR_RESET << endl;
    cout << string(padding, ' ') << COLOR_CYAN << "│" << COLOR_RED << BOLD << setw(14) << year << "      " << month << setw(14) << COLOR_RESET << COLOR_CYAN << "│" << COLOR_RESET << endl;
    cout << string(padding, ' ') << COLOR_CYAN << "├───────────────────────────────┤" << COLOR_RESET << endl;
    cout << string(padding, ' ') << COLOR_CYAN << "│" << COLOR_GREEN << " Sun Mon Tue Wed Thu Fri Sat" << COLOR_CYAN << "   │" << COLOR_RESET << endl;
    cout << string(padding, ' ') << COLOR_CYAN << "├───────────────────────────────┤" << COLOR_RESET << endl;


    int day = 1;
    for (int row = 0; row < 6; row++) {
        cout << string(padding, ' ') << COLOR_CYAN << "│" << COLOR_RESET;
        for (int col = 0; col < 7; col++) {
            if ((row == 0 && col < h) || day > daysInMonth) {
                cout << setw(4) << " ";
            } else {

                if (col == 0 || col == 6) {
                    cout << COLOR_MAGENTA << setw(4) << day << COLOR_RESET;
                } else {
                    cout << COLOR_GREEN << setw(4) << day << COLOR_RESET;
                }
                day++;
            }
        }
        cout << COLOR_CYAN << "   │" << COLOR_RESET << endl;

        // Break if all days of the month have been printed
        if (day > daysInMonth) {
            break;
        }
    }

    // Print footer
    cout << string(padding, ' ') << COLOR_CYAN << "└───────────────────────────────┘" << COLOR_RESET << endl << endl;
cout << COLOR_MAGENTA << "Thank you for using NEXIS Calendar! Close window to end task\n" << COLOR_RESET;

   // Compile the deallocate resource file before running it
    system("g++ -o deallocate dealloc_resource.cpp");
    // Run the deallocate resource file with an argument CALCULATOR
    system("./deallocate CALENDER");
   
    return 0;
}

