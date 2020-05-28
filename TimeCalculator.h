//
// Created by kangd on 2020-05-28.
//

#ifndef LINUXMAJORPROJECT_TIMECALCULATOR_H
#define LINUXMAJORPROJECT_TIMECALCULATOR_H


#pragma once
#include <iostream>
#include <ctime>
#pragma warning(disable:4996)

#define MAX_ARR_CTR 36500 // Approx. 100 years from 1970
#define DAY_SEC 86400

using namespace std;

class TimeCalculator {
public:
    // Human readable date to raw timestamp
    time_t dateToStamp(int year, int month, int day);

    // Calculate Week
    time_t calculateWeek(int year, int month, int day, bool max = false);

    // Show all information about that day
    void showDate(time_t rawtime);

    // Print information
    // printDate(2020, 5, 14, "month") means prints May
    void printDate(int year, int month, int day, string specifier);

    // Calculate and return(modify) year, month, day, wday information based on timestamp
    void calculateDateFromStamp(int& year, int& month, int& day, int& wday, time_t ts);

    time_t roundOffTimeStamp(time_t ts);

    // whaaatever
    bool isCorrectDay(int year, int month, int day);

    bool calcDayCorrection(int year, int month, int day);
};


#endif //LINUXMAJORPROJECT_TIMECALCULATOR_H
