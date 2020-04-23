#include <iostream>
#include "Manager.h"

using namespace std;

bool hasNext(string &input) {
    for (int i = 1; i < input.length(); i++) {
        if (input.at(i) != 32) {
            if (input.at(i) > 0) {
                return true;
            }
        }
    }
    return false;
}

int main(void) {
    Manager manager;
    string menu;
    while (true) {
        cout << "(1) Show Schedule\n";
        cout << "(2) Add Schedule\n";
        cout << "(3) Edit Schedule\n";
        cout << "(4) Delete Schedule\n";
        cout << "(5) Exit Program\n";
        cout << "Enter Menu Number >";

        cin >> menu;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        if (menu.length() > 1) {
            // Re-Input --> NEED TO DISCUSS
            continue;
        } else if (menu.at(0) == '0' && hasNext(menu)) {
            // Prefix 0 detected.
            cout << "Invalid number format(ex: prefix 0) entered. Please enter again." << endl;
            continue;
        } else if (menu.at(0) < '0' || menu.at(0) > '9') {
            // Only number are allowed
            cout << "Only numbers are allowed. Please enter again." << endl; 
            continue;
        } else if (menu.at(0) < '1' || menu.at(0) > '5') {
            // Number out of range
            cout << "Argument out of range. Please enter again." << endl;
            continue;
        } else if (menu.at(0) == '1') {
            manager.showSchedule();
        } else if (menu.at(0) == '2') {
            manager.addSchedule();
        } else if (menu.at(0) == '3') {
            manager.editSchedule();
        } else if (menu.at(0) == '4') {
            manager.deleteSchedule();
        } else if (menu.at(0) == '5') {
            // exit
            manager.callSave();
            exit(0);
        }
    }
    return 0;
}