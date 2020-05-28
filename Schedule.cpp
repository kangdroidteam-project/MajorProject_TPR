//
// Created by kangd on 2020-05-28.
//

#include "Schedule.h"
#include "Schedule.h"
#include "TimeCalculator.h"

Schedule::Schedule(string con, string key, int sid){
    this->content = con;
    this->keyword = key;
    this->sid = sid;
}

Schedule::~Schedule(){

}

void Schedule::add(time_t t){
    this->tmp.push_back(t);
}

string Schedule::getKeyword(){
    return this->keyword;
}

string Schedule::getContent() {
    return this->content;
}

void Schedule::setKeyword(string& s) {
    this->keyword = s;
}

void Schedule::setContent(string& s) {
    this->content = s;
}

bool Schedule::isDayExists(time_t ts) {
    for (int i = 0; i < tmp.size(); i++) {
        if (ts == tmp.at(i)) {
            return true;
        }
    }
    return false;
}

void Schedule::setRepeat(time_t start_timestamp, time_t limit_timestamp, int specifier, int duration) {
    TimeCalculator tc;
    int y, m, d, wd;
    tc.calculateDateFromStamp(y, m, d, wd, start_timestamp);

    if (specifier == 1) { // year
        while (start_timestamp <= limit_timestamp) {
            cout << "ST: " << start_timestamp << " ED: " << limit_timestamp << endl;
            if (tc.calcDayCorrection(y, m, d)) {
                tmp.push_back(start_timestamp);
            }
            // Re-Calculate stamp
            y += duration;
            start_timestamp = tc.dateToStamp(y, m, d);

        }
    } else if (specifier == 2) { // month
        while (start_timestamp <= limit_timestamp) {
            cout << "ST: " << start_timestamp << " ED: " << limit_timestamp << endl;
            if (tc.calcDayCorrection(y, m, d)) {
                tmp.push_back(start_timestamp);
            }
            // Re-Calculate stamp
            m += duration;
            start_timestamp = tc.dateToStamp(y, m, d);
        }
    } else if (specifier == 3) { // day
        while (start_timestamp <= limit_timestamp) {
            cout << "ST: " << start_timestamp << " ED: " << limit_timestamp << endl;
            tmp.push_back(start_timestamp);

            // Re-Calculate stamp
            d += duration;
            start_timestamp = tc.dateToStamp(y, m, d);
        }
    }
}

int Schedule::getSid() {
    return this->sid;
}