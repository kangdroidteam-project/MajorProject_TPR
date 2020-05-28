#include "Date.h"

Date::Date(time_t cur_timestamp, vector<Schedule>* tmpVector) {
    this->cur_timestamp = cur_timestamp;
    struct tm* dt;
    char buffer[50];
    dt = localtime(&this->cur_timestamp);
    this->year = dt->tm_year;
    this->month = dt->tm_mon;
    this->day = dt->tm_mday;
    this->wday = dt->tm_wday;
    this->schedule_tmp = tmpVector;

    // TODO: SID should be init in this constructor.
    initSid();
}

void Date::add(int schedule_sid) {
    sid.push_back(schedule_sid);
}

void Date::initSid() {
    // Search SID for that date(timestamp)
    for (int i = 0; i < schedule_tmp->size(); i++) {
        if (schedule_tmp->at(i).isDayExists(this->cur_timestamp)) {
            add(schedule_tmp->at(i).getSid());
        }
    }
}

void Date::print_date() {
    struct tm* dt;
    char buffer[50];
    //time_t rawtime = 0;//std::time(0);
    dt = localtime(&cur_timestamp);
    strftime(buffer, sizeof(buffer), "%Y.%m.%d (%a)", dt);

    cout << string(buffer) << " ";

    for (int i = 0; i < sid.size(); i++) {
        Schedule tmpS = getSchedule(sid.at(i));
        if (tmpS.getContent() == "something" && tmpS.getKeyword() == "something" && tmpS.getSid() == -200) {
            // Failed to search, skip it
        } else {
            cout << "\n" << i+1 << ". " << tmpS.getContent();
        }
    }
    cout << endl;
}

void Date::deleteSchedule(vector<int> list_arr) {
    for (int i = 0; i < list_arr.size(); i++) {
        // its list number-1 is actual index value of sid
        // Find offset from Schedule vector
        int offset = findOffset(sid.at(list_arr.at(i) - 1));
        if (offset != -1) {
            schedule_tmp->erase(schedule_tmp->begin() + offset);
        }
    }
}

void Date::editSchedule(int idx, Schedule& sc) {
    // Remove idx;th schedule
    int offset = findOffset(sid.at(idx - 1));
    if (offset != -1) {
        schedule_tmp->erase(schedule_tmp->begin() + offset);
        Schedule tmp = sc; // Need correct declare: is really using reference would NOT invalidate its ptr number?
        schedule_tmp->push_back(tmp);
    }
}

Schedule Date::getSchedule(int schedule_sid) {
    for (int i = 0; i < schedule_tmp->size(); i++) {
        if (schedule_tmp->at(i).getSid() == schedule_sid) {
            return schedule_tmp->at(i);
        }
    }
    return Schedule("something", "something", -200); // Failed to search
}

int Date::findOffset(int schedule_sid) {
    for (int i = 0; i < schedule_tmp->size(); i++) {
        if (schedule_tmp->at(i).getSid() == schedule_sid) {
            return i;
        }
    }
    return -1;
}

int Date::GetLengthSid(){
    return sid.size();
}