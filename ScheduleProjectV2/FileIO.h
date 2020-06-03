//
// Created by kangd on 2020-05-28.
//

#pragma once

#include <iostream>
#include <fstream>

#include "Schedule.h"

using namespace std;

class FileIO {
public:
    void save(vector<Schedule>& dt);
    void load(vector<Schedule>& dt);
private:
    string parseString(const string str, unsigned long long& iterator_loc);
    string decryptString(string encoded);
    string encryptString(string decoded);
    ifstream reader_file;
    ofstream writer_file;
    int key = -2;
};