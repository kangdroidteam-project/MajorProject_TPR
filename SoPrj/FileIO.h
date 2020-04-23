#include <fstream>
#include <cstdio>
#include "Date.h"

using namespace std;

class FileIO {
public:
    void save(Date* date);
    void load(Date* date);
private:
    ifstream reader_file; // input file var
    ofstream writer_file; // output file var
    int key = -2;
    const int max = 366;
    string encryptString(string decoded);
    string decryptString(string encoded);
};