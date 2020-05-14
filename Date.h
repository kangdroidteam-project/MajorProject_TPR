//
// Created by kangd on 2020-05-14.
//
#ifndef DATEPROJECT_DATE_H
#define DATEPROJECT_DATE_H

#include <iostream>
#include <ctime>

using namespace std;

class Date {
private:
    time_t rawtime;
    int year;
    int month;
    int day;
    int wday;

public:
    Date(time_t rawtime);
    Date();
    time_t getRawTime();
};


#endif //DATEPROJECT_DATE_H
