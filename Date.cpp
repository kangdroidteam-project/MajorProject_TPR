//
// Created by kangd on 2020-05-14.
//

#include "Date.h"

Date::Date(time_t rawtime) {
    this->rawtime = rawtime;
    struct tm * dt;
    char buffer [50];
    dt = localtime(&this->rawtime);
    this->year = dt->tm_year;
    this->month = dt->tm_mon;
    this->day = dt->tm_mday;
    this->wday = dt->tm_wday;
}

time_t Date::getRawTime() {
    return this->rawtime;
}

Date::Date() {
}
