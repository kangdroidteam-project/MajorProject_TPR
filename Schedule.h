//
// Created by kangd on 2020-05-28.
//

#ifndef LINUXMAJORPROJECT_SCHEDULE_H
#define LINUXMAJORPROJECT_SCHEDULE_H

#include <iostream>
#include <vector>
#include <ctime>
#pragma warning(disable:4996)
using namespace std;

class Schedule {

private:
    int sid;
    string content;
    string keyword;
    vector<time_t> tmp;

public:
    Schedule(string con, string key, int sid);
    ~Schedule();
    void add(time_t t);
    string getKeyword();
    string getContent();
    void setKeyword(string& s);
    void setContent(string& s);
    bool isDayExists(time_t ts); // returns true if day exists, returns false if not exists.
    void setRepeat(time_t start_timestamp, time_t limit_timestamp, int specifier, int duration); // Set Repeat
    int getSid();
};


#endif //LINUXMAJORPROJECT_SCHEDULE_H
