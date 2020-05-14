#include "Date.h"

#define MAX_ARR_CTR 36500 // Approx. 100 years from 1970
#define DAY_SEC 86400

using namespace std;

Date array_used[36500];
int global_iteration = 0;

/**
 * Raw Timestamp to Actual Human-Readable Date
 */
void showDate(time_t rawtime) {
    struct tm * dt;
    char buffer [50];
    //time_t rawtime = 0;//std::time(0);
    dt = localtime(&rawtime);
    strftime(buffer, sizeof(buffer), "%Y.%m.%d (%a)", dt);
    std::cout << std::string(buffer) << std::endl;
    for (int i = 0; i < global_iteration; i++) {
        if (array_used[i].getRawTime() == rawtime) {
            cout << "Schedule Exists!" << endl;
        }
    }
}

/**
 * Human Readable Date to Raw Timestamp
 */
time_t dateToStamp(int year, int month, int day) {
    struct tm  tm;
    time_t rawtime;
    time ( &rawtime );
    tm = *localtime ( &rawtime );
    tm.tm_year = year - 1900;
    tm.tm_mon = month - 1;
    tm.tm_mday = day;
    tm.tm_hour = 0;
    tm.tm_min = 0;
    tm.tm_sec = 0;
    time_t final_tmp = mktime(&tm);
    return final_tmp;
}

time_t calculateWeek(int year, int month, int day, bool max = false) {
    struct tm  tm;
    time_t rawtime;
    time ( &rawtime );
    tm = *localtime ( &rawtime );
    tm.tm_year = year - 1900;
    tm.tm_mon = month - 1;
    tm.tm_mday = day;
    tm.tm_hour = 0;
    tm.tm_min = 0;
    tm.tm_sec = 0;
    mktime(&tm); // calculate tm_wday
    if (!max) {
        tm.tm_mday = tm.tm_mday - tm.tm_wday;
    } else {
        tm.tm_mday = tm.tm_mday + (7 - tm.tm_wday);
    }


    time_t final_tmp = mktime(&tm); // This state, tm contains wday;
    return final_tmp;
}

/**
 * Print information
 * Assume 1970.01.01 to 1970.01.30
 */
void printDate(int year, int month, int day, string specifier) {
    if (specifier == "month") {
        // Whatever, Month means day starts from month to day ends - month
        time_t timestmp_raw = dateToStamp(year, month, 1); // Minum
        time_t tmp = dateToStamp(year, month+1, 1); // Maximum
        while (timestmp_raw < tmp) {
            showDate(timestmp_raw);
            timestmp_raw += DAY_SEC; // one day increment
        }
    } else if (specifier == "day") {
        time_t timestmp_raw = dateToStamp(year, month, day);
        showDate(timestmp_raw);
    } else if (specifier == "week") {
        // Calculate minimum range
        time_t minimum_range = calculateWeek(year, month, day, false);
        time_t maximum_range = calculateWeek(year, month, day, true);
        while (minimum_range < maximum_range) {
            showDate(minimum_range);
            minimum_range += DAY_SEC;
        }
        // Calculate maximum range
        // iterate.
    } else {
    }
}

void add() {
    int year = 2020, month = 5, day = 14;
    time_t raw = dateToStamp(year, month, day);
    array_used[global_iteration++] = Date(raw);
}

int main(void) {
    add();
    printDate(2020, 5, 14, "month");
    //showDate();
    //dateToStamp();
    return 0;
}