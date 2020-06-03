#include "Date.h"

Date::Date(time_t cur_timestamp, vector<Schedule>* tmpVector) {
    this->cur_timestamp = cur_timestamp;
    struct tm* dt;
    dt = localtime(&this->cur_timestamp);
    this->year = dt->tm_year;
    this->month = dt->tm_mon;
    this->day = dt->tm_mday;
    this->wday = dt->tm_wday;
    this->schedule_tmp = tmpVector;

    // TODO: SID should be init in this constructor.
    initSid();
}

void Date::add(unsigned long long schedule_sid) {
    sid.push_back(schedule_sid);
}

void Date::print_date() {
    struct tm* dt;
    char buffer[50];
    //char mon_buf[20];
    //time_t rawtime = 0;//std::time(0);
    dt = localtime(&cur_timestamp);
    if (dt->tm_wday == 0) {
        strftime(buffer, sizeof(buffer), "\033[0;31m%Y.%m.%d (%a)\033[0m", dt);
    } else {
        strftime(buffer, sizeof(buffer), "%Y.%m.%d (%a)", dt);
    }
    //strftime(buffer, sizeof(mon_buf), "(%a)", dt);

    cout << string(buffer) << " ";

    for (int i = 0; i < sid.size(); i++) {
        Schedule tmpS = getSchedule(sid.at(i));
        if (tmpS.getContent() == "something" && tmpS.getKeyword() == "something" && tmpS.getSid() == -200) {
            // Failed to search, skip it
        } else {
            cout << "\n" << i + 1 << ". " << tmpS.getContent();
        }
    }
    cout << endl;
}

void Date::initSid() {
    // Search SID for that date(timestamp)
    for (unsigned long long i = 0; i < schedule_tmp->size(); i++) {
        if (schedule_tmp->at(i).isDayExists(this->cur_timestamp)) {
            add(schedule_tmp->at(i).getSid());
        }
    }
}

void Date::deleteSchedule(vector<unsigned long long> list_arr) {
    for (unsigned long long i = 0; i < list_arr.size(); i++) {
        // its list number-1 is actual index value of sid
        // Find offset from Schedule vector
        unsigned long long offset = findOffset(sid.at(list_arr.at(i) - 1));
        if (offset != -1) {
            schedule_tmp->erase(schedule_tmp->begin() + offset);
        }
    }
}

void Date::editSchedule(unsigned long long idx, Schedule& sc) {
    // Remove idx;th schedule
    unsigned long long offset = findOffset(sid.at(idx - 1));
    if (offset != -1) {
        schedule_tmp->erase(schedule_tmp->begin() + offset);
        Schedule tmp = sc; // Need correct declare: is really using reference would NOT invalidate its ptr number?
        schedule_tmp->push_back(tmp);
    }
}

Schedule Date::getSchedule(unsigned long long schedule_sid) {
    for (unsigned long long i = 0; i < schedule_tmp->size(); i++) {
        if (schedule_tmp->at(i).getSid() == schedule_sid) {
            return schedule_tmp->at(i);
        }
    }
    return Schedule("something", "something", -200); // Failed to search
}

unsigned long long Date::findOffset(unsigned long long schedule_sid) {
    for (unsigned long long i = 0; i < schedule_tmp->size(); i++) {
        if (schedule_tmp->at(i).getSid() == schedule_sid) {
            return i;
        }
    }
    return -1;
}

unsigned long long Date::GetLengthSid(){
    return sid.size();
}