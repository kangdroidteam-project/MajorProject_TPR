#include "TimeCalculator.h"

/**
 * Converts date to timestamp
 * Args: user-input year, month, day
 * return: converted timestamp
 */
time_t TimeCalculator::dateToStamp(int year, int month, int day) {
    struct tm  tm;
    time_t rawtime;
    time(&rawtime);
    tm = *localtime(&rawtime);
    tm.tm_year = year - 1900;
    tm.tm_mon = month - 1;
    tm.tm_mday = day;
    if (tm.tm_year == 70 && tm.tm_mon == 0 && tm.tm_mday == 1) {
        tm.tm_hour = 9;
        tm.tm_min = 0;
        tm.tm_sec = 0;
    } else {
        tm.tm_hour = 0;
        tm.tm_min = 0;
        tm.tm_sec = 0;
    }
    
    time_t final_tmp = mktime(&tm);
    return final_tmp;
}

/**
 * Calculate week start info / end info
 * Args: user-input year, month, day / Start || end signal
 * return: start/end info based on signal
 */
time_t TimeCalculator::calculateWeek(int year, int month, int day, bool max) {
    struct tm  tm;
    time_t rawtime;
    time(&rawtime);
    tm = *localtime(&rawtime);
    tm.tm_year = year - 1900;
    tm.tm_mon = month - 1;
    tm.tm_mday = day;
    tm.tm_hour = 0;
    tm.tm_min = 0;
    tm.tm_sec = 0;
    mktime(&tm); // calculate tm_wday
    if (!max) {
        if (tm.tm_year == 70 && tm.tm_mon == 0 && tm.tm_mday == 1) {
            tm.tm_hour = 9;
            tm.tm_mday = 1;
        } else {
            tm.tm_mday = tm.tm_mday - tm.tm_wday;
        }
    } else {
        tm.tm_mday = tm.tm_mday + (7 - tm.tm_wday);
    }

    time_t final_tmp = mktime(&tm); // This state, tm contains wday;
    return final_tmp;
}

/**
 * Calculate Date from timestamp
 * Args: (Ref)year, (Ref)month, (Ref)day, (Ref)wday, timestamp
 * Return: No-Op, but reference value should "act" like return.
 */
void TimeCalculator::calculateDateFromStamp(int& year, int& month, int& day, int& wday, time_t ts) {
    struct tm* tmp_struct;
    tmp_struct = localtime(&ts);
    if (tmp_struct == NULL) {
        year = -1;
        month = -1;
        day = -1;
        wday = -1;
    } else {
        year = tmp_struct->tm_year + 1900;
        month = tmp_struct->tm_mon + 1;
        day = tmp_struct->tm_mday;
        wday = tmp_struct->tm_wday;
    }
}

/**
 * Round Off Timestamp
 * Since when iterating through timestamp with single-date-timestamp, it could not really accurate.
 * Args: timestamp
 * return: Adjusted(Rounded off) timestamp
 */
time_t TimeCalculator::roundOffTimeStamp(time_t ts) {
    struct tm* tmp_struct;
    tmp_struct = localtime(&ts);
    if (tmp_struct == NULL) {
        return -1;
    }
    tmp_struct->tm_hour = 0;
    tmp_struct->tm_min = 0;
    tmp_struct->tm_sec = 0;
    time_t ret = mktime(tmp_struct);
    return ret;
}

/**
 * Check wheter user-input day is actually "existing" date.
 * Args: User - input_ed year/month/day
 * Return: "true" when user enetered world-existing date, "false" when user entered some strange date
 */
bool TimeCalculator::isCorrectDay(int year, int month, int day) {
    // Converted day - will be compared with original y/m/d
    // conv_wday is not-used, but garbage
    int conv_year, conv_month, conv_day, conv_wday;

    // 1. Convert y/m/d to timestamp
    time_t original = dateToStamp(year, month, day);

    // 2. Re-Calc y/m/d again
    if (original == -1) {
        return false;
    }
    calculateDateFromStamp(conv_year, conv_month, conv_day, conv_wday, original);

    // 3. Compare
    if (year > 2037 || year < 1970 || conv_year != year || conv_month != month || conv_day != day) {
        return false;
    } else {
        return true;
    }
}
