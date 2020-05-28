//
// Created by kangd on 2020-05-28.
//

#ifndef LINUXMAJORPROJECT_MANAGER_H
#define LINUXMAJORPROJECT_MANAGER_H

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#if defined(_WIN64)
#include <Windows.h>
#include <conio.h>
#else
#include <termios.h>
#endif
#include <vector>

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
    vector<int> sid_container;

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
    bool parseString(int* tmp, int& array_idx_pointer, string& input, int year_idx);
    void removeSame(int* arr, int& idx, vector<int>&tmp);
    bool isHas(vector<int>& tmpVector, int target);
    int repeatSchedule(time_t time,int menu);
    time_t input_finishDay();
    time_t get_date();

    // Generate SID and push to duplication checker container
    int generateSID();

    // Check whether arg's sid exists on SID Dup checker container
    bool hasSID(int sid_checker);
    void setColor(int color);
};

#endif //LINUXMAJORPROJECT_MANAGER_H
