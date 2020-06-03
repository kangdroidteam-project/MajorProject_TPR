#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include <string>

#if defined(_WIN64)
#pragma warning(disable:4996)
#endif
using namespace std;

class Schedule {

private:
    unsigned long long sid;
    string content;
    string keyword;
    vector<time_t> tmp;

public:
    // 시작 timestamp, 리밋 timestamp, duration(반복)
    // void setRepeat(time_t start_timestamp, time_t limit_timestamp, time_t duration); // 보류
    //Schedule();
    Schedule(string con, string key, unsigned long long sid);
    ~Schedule();
    void add(time_t t);
    string getKeyword();
    string getContent();
    void setKeyword(string& s);
    void setContent(string& s);
    bool isDayExists(time_t ts); // returns true if day exists, returns false if not exists.
    void setRepeat(time_t start_timestamp, time_t limit_timestamp, int specifier, int duration); // Set Repeat
    unsigned long long getSid();
    void setSid(unsigned long long val);
    string getAllInfo();
};

