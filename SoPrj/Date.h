#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "Schedule.h"

using namespace std;

class Date {
private:
	int date;    // 날짜
	int day;     // 요일
	int range;  // 1월1일부터 며칠 
	

	// String data for year - month - day
	// For example, year should be 2020, and month should be 01~ 12, day should be 01 ~ 31
	string str_year = "";
	string str_month = "";
	string str_day = "";

public:
	vector<Schedule> schedules;
	Date();
	Date(int date, int day, int range);
	int getDate();
	void setDate(int date);
	int getDay();
	void setDay(int day);
	int getRange();
	void setRange(int range);
	vector<Schedule> getSchedules();
	void parseDate();

	void showSch(string specifier);
	void addSch(string content, string keyword);
	void editSch(int number, string content, string keyword);
	void deleteSch(int* num, int len);
	string getDayNormFormat();

	int getLength();
    void setColor(int color);

};