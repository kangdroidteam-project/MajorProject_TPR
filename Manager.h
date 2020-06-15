#pragma once

#include <iostream>
#include <string>
#include <fstream>
//#include "Date.h"
//#include "FileIO.h"
#include <algorithm>
#if defined(_WIN64)
#include <Windows.h>
#include <conio.h>
#else
#include <termios.h>
#endif
#include <vector>

// For automate test
#include "test.h"

#include "Schedule.h"
#include "TimeCalculator.h"
#include "Date.h"
#include "FileIO.h"
using namespace std;

class Manager {
private:
	//FileIO fio; // File input/out
	
    vector<Schedule> date;

	// Schedule SID Container for duplication check
	vector<unsigned long long> sid_container;

	TimeCalculator timecal;

public:
	Manager();

	// KangDroid Added Function
	void showDate(time_t rawtime, string scope_info);
	
	void showSchedule();
	void addSchedule();
	void editSchedule();
	void deleteSchedule();
	bool hasNext(string& input);
	void custom_pause(const string& str);// str = something you want to print
	//int findRange(int date);

	void callSave();
	void callLoad();
	bool parseString(unsigned long long* tmp, unsigned long long& array_idx_pointer, string& input, unsigned long long year_idx);
	void removeSame(unsigned long long* arr, unsigned long long& idx, vector<unsigned long long>&tmp);
	bool isHas(vector<unsigned long long>& tmpVector, unsigned long long target);
	int repeatSchedule(time_t time,int menu);
	time_t input_finishDay(time_t& today);
	time_t get_date();

	// Generate SID and push to duplication checker container
	unsigned long long generateSID();

	// Check whether arg's sid exists on SID Dup checker container
	bool hasSID(unsigned long long sid_checker);
	void setColor(int color);
};




