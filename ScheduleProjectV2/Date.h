#pragma once
#include "Schedule.h"
#include <iostream>
#include <ctime>
#include <vector>

using namespace std;

class Date {
public:
    Date(time_t cur_timestamp, vector<Schedule>* tmpVector);
    void add(int schedule_sid);
    void initSid();
    void print_date();
    void deleteSchedule(vector<int> list_arr);
    void editSchedule(int idx, Schedule& sc);
    Schedule getSchedule(int schedule_sid);
    int findOffset(int schedule_sid);
    int GetLengthSid();
private:
    time_t cur_timestamp;
    vector<int> sid;
    vector<Schedule>* schedule_tmp;
    int year;
    int month;
    int day;
    int wday;
};