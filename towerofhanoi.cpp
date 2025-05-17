#include <iostream>
#include <cstdlib>
using namespace std;

// ANSI Color Codes
const string RESET = "\033[0m";
const string CYAN = "\033[34m";
const string YELLOW = "\033[33m";
const string GREEN = "\033[32m";
const string RED = "\033[31m";
const string BOLD = "\033[1m";

class node {
public:
    node *next;
    int data;
    node() { next = NULL; }
};

class ADT {
public:
    node *top;
    int count = -1;
    ADT() { top = NULL; }

    void push(int element) {
        if (isfull()) return;
        node *new_node = new node;
        new_node->data = element;
        new_node->next = top;
        top = new_node;
        count++;
    }

    bool isempty() {
        return top == NULL;
    }

    void display() {
        node *current = top;
        while (current != NULL) {
            cout << YELLOW << current->data << RESET << endl;
            current = current->next;
        }
    }

    int pop() {
        int var = -1;
        if (isempty()) {
            cout << RED << "Stack Underflow" << RESET << endl;
        } else {
            var = top->data;
            node *p = top;
            top = top->next;
            delete p;
            count--;
        }
        return var;
    }

    int Top() {
        return isempty() ? -1 : top->data;
    }

    bool isfull() {
        return count == 4;
    }
};

void diskmoves(ADT &l1, ADT &l2) {
    if (!l1.isempty() && !l2.isfull()) {
        if (l2.isempty() || l1.Top() < l2.Top()) {
            l2.push(l1.Top());
            l1.pop();
        }
    }
}

void display_if(ADT &l1, ADT &l2, ADT &l3) {
    cout << "\n" << CYAN << BOLD << "First Cupboard:" << RESET << endl;
    l1.display();
    cout << "\n" << CYAN << BOLD << "Second Cupboard:" << RESET << endl;
    l2.display();
    cout << "\n" << CYAN << BOLD << "Third Cupboard:" << RESET << endl;
    l3.display();
    cout << endl;
}

bool game_solve(ADT &l1) {
    return l1.isfull();
}

int min_moves_to_win() {
    int count = 5;
    return (1 << count) - 1;  // 2^n - 1
}

void initialize(ADT &l1, ADT &l2, ADT &l3) {
    for (int i = 5; i > 0; i--) {
        l1.push(i);
    }
}

int main() {
    ADT l1, l2, l3;
    int count1 = 0, choice = 0, mn = 0;

    cout << GREEN << "-----------------------------" << RESET << endl;
    cout << BOLD << "|||||    THE TOWER OF HANOI    |||||" << RESET << endl;
    cout << GREEN << "-----------------------------" << RESET << endl;
    cout << CYAN << "1. Play the game" << endl;
    cout << "2. Exit the game" << RESET << endl;
    cin >> choice;

    if (choice == 1) {
        initialize(l1, l2, l3);
        while (true) {
            display_if(l1, l2, l3);
            cout << BOLD << "Choose a move:\n" << RESET;
            cout << "1. Move from 1 → 2\n";
            cout << "2. Move from 1 → 3\n";
            cout << "3. Move from 2 → 1\n";
            cout << "4. Move from 2 → 3\n";
            cout << "5. Move from 3 → 1\n";
            cout << "6. Move from 3 → 2\n";
            cin >> mn;

            if (mn == 1) diskmoves(l1, l2);
            else if (mn == 2) diskmoves(l1, l3);
            else if (mn == 3) diskmoves(l2, l1);
            else if (mn == 4) diskmoves(l2, l3);
            else if (mn == 5) diskmoves(l3, l1);
            else if (mn == 6) diskmoves(l3, l2);
            else cout << RED << "Invalid move!" << RESET << endl;

            count1++;

            if (game_solve(l3)) {
                cout << GREEN << "\n Puzzle solved successfully! " << RESET << endl;
                display_if(l1, l2, l3);
                int mov = min_moves_to_win();
                cout << CYAN << "\nMinimum required moves: " << mov << RESET << endl;
                cout << YELLOW << "Your moves: " << count1 << RESET << endl;
                if (count1 == mov) {
                    cout << GREEN << "You completed the game in the minimum number of moves!" << RESET << endl;
                } else {
                    cout << RED << "You did not achieve the minimum moves." << RESET << endl;
                }

                // Deallocate on success
                system("g++ -o deallocate dealloc_resource.cpp");
                system("./deallocate TOWEROFHANOI");
                break;
            }
        }
    } else {
        
        system("g++ -o deallocate dealloc_resource.cpp");
        system("./deallocate TOWEROFHANOI");
        return 0;
    }

    return 0;
}
