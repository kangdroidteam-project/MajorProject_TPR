#pragma once
#include "Schedule.h"
#include <iostream>
#include <ctime>
#include <vector>

using namespace std;

class Date {
public:
    Date(time_t cur_timestamp, vector<Schedule>* tmpVector);
    void add(unsigned long long schedule_sid);
    void initSid();
    void deleteSchedule(vector<unsigned long long> list_arr);
    void editSchedule(unsigned long long idx, Schedule& sc);
    Schedule getSchedule(unsigned long long schedule_sid);
    unsigned long long findOffset(unsigned long long schedule_sid);
    unsigned long long GetLengthSid();
    void print_date();
private:
    time_t cur_timestamp;
    vector<unsigned long long> sid;
    vector<Schedule>* schedule_tmp;
    int year;
    int month;
    int day;
    int wday;
};