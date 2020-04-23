#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include "Date.h"
#include "FileIO.h"
#include <algorithm>
#include <Windows.h>
#include <conio.h>
using namespace std;

class Manager {
private:
	Date year[366];
	int month_last[12];
	FileIO fio; // File input/out

public:
	Manager();
	
	void showSchedule();

	void addSchedule();
	void editSchedule();
	void deleteSchedule();

	void custom_pause(const string& str);// str = something you want to print
	//int findRange(int date);

	void callSave();
	void callLoad();
};




