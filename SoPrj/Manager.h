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
	bool parseString(int* tmp, int& array_idx_pointer, string& input, int year_idx);
	void removeSame(int* arr, int& idx, vector<int>&tmp);
	bool isHas(vector<int>& tmpVector, int target);
};




