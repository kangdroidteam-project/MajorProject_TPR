#include <iostream>
#include "Manager.h"
#include <unistd.h>
#pragma warning(disable:4996)

using namespace std;

bool hasNext(string& input) {
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
	srand(time(NULL));
	Manager manager;
	string menu;
	#if defined(TESTCASE_MAIN_ENABLED)
	string case_men[14] = {"02", "6", "0", "-2", "일", "one", "!", "(스페이스바 엔터)", "(엔터)", " 3", "3 ", " 3 ", "1234567890123456789", "-1234567890123456789"
};
	int iter_ctr = 0;
	#endif
	while (true) {
		cout << endl;
		cout << "(1) Show Schedule\n";
		cout << "(2) Add Schedule\n";
		cout << "(3) Edit Schedule\n";
		cout << "(4) Delete Schedule\n";
		cout << "(5) Exit Program\n";
		cout << "Enter Menu Number >";

		#if defined(TESTCASE_MAIN_ENABLED)
		if (iter_ctr >= 14) break;
		cout << " " << case_men[iter_ctr] << endl;
		menu = case_men[iter_ctr++];
		#else
		getline(cin, menu);
		#endif
		if (menu.length() < 1) {
			cout << "Only numbers are allowed. Please enter again." << endl; continue;
		}
		else if (menu.at(0) == '0' && hasNext(menu)) {
			// Prefix 0 detected.
			cout << "Invalid number format(ex: prefix 0) entered. Please enter again." << endl;
			continue;
		}
		else if (menu.at(0) < '0' || menu.at(0) > '9') {
			// Only number are allowed
			cout << "Only numbers are allowed. Please enter again." << endl;
			continue;
		}
		else if (menu.at(0) < '1' || menu.at(0) > '5' || menu.length() > 1) {
			// Number out of range
			cout << "Argument out of range. Please enter again." << endl;
			continue;
		}
		else if (menu.at(0) == '1') {
			manager.showSchedule();
		}
		else if (menu.at(0) == '2') {
			manager.addSchedule();
		}
		else if (menu.at(0) == '3') {
			manager.editSchedule();
		}
		else if (menu.at(0) == '4') {
			manager.deleteSchedule();
		}
		else if (menu.at(0) == '5') {
			// exit
			manager.callSave();
			exit(0);
		}
		else if (menu.at(0) == '6') {
			manager.callLoad();
		}
		sleep(10);
	}
	return 0;
}