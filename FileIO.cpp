//
// Created by kangd on 2020-05-28.
//

#include "FileIO.h"

/**
 * File Descriptor
 * Current saved Schedule Count
 * Current Schedule[i] SID
 * Current Schedule[i] Timestamp Count
 * Current Schedule[i] Key
 * Current Schedule[i] Content
 */
void FileIO::save(vector<Schedule>& dt) {
     ofstream outfile("userInfo");
     string tmp = "";
     tmp.append("This is T3 From SoPrj\n");
     tmp.append(to_string(dt.size()).append("\n"));
     for (int i = 0; i < dt.size(); i++) {
         tmp.append(dt.at(i).getAllInfo());
     }
     tmp = encryptString(tmp);
     outfile << tmp;
     outfile.close();
}

/**
 * File Descriptor
 * Current saved Schedule Count
 * Current Schedule[i] SID
 * Current Schedule[i] Timestamp Count
 * Current Schedule[i] Key
 * Current Schedule[i] Content
 */
void FileIO::load(vector<Schedule>& dt) {
    int st_it = 0;
    ifstream inputFile("userInfo");
    if (!(inputFile.is_open())) {
        return; // File dose not exists. Skipping reading
    }
    string tmpEncoded; // File to string storation directory

    // Allocate memory dynamically
    inputFile.seekg(0, ios::end);
    tmpEncoded.reserve(inputFile.tellg());
    inputFile.seekg(0, ios::beg);

    tmpEncoded.assign((std::istreambuf_iterator<char>(inputFile)),
                      std::istreambuf_iterator<char>());
    tmpEncoded = decryptString(tmpEncoded);

    string descriptor = parseString(tmpEncoded, st_it);

    if (descriptor == "This is T3 From SoPrj") {
        int schedule_count = stoi(parseString(tmpEncoded, st_it));
        Schedule tmp_sc("", "", -1);
        for (int i = 0; i < schedule_count; i++) {
            int sid = stoi(parseString(tmpEncoded, st_it));
            tmp_sc.setSid(sid);
            int ts_ctr = stoi(parseString(tmpEncoded, st_it));
            for (int v = 0; v < ts_ctr; v++) {
                int val = stoi(parseString(tmpEncoded, st_it));
                tmp_sc.add(val);
            }
            string key = parseString(tmpEncoded, st_it);
            string con = parseString(tmpEncoded, st_it);
            tmp_sc.setKeyword(key);
            tmp_sc.setContent(con);
            dt.push_back(tmp_sc);
        }
        inputFile.close();
    } else {
        // this isn't our file
        inputFile.close();
    }
}

string FileIO::parseString(const string str, int& iterator_loc) {
    string tmp = "";
    for (iterator_loc; iterator_loc < str.size(); iterator_loc++) {
        if (str.at(iterator_loc) != '\n') {
            tmp += str.at(iterator_loc);
        } else {
            iterator_loc++;
            break;
        }
    }
    return tmp;
}

string FileIO::encryptString(string decoded) {
    string encoded = "";
    for (int i = 0; i < decoded.length(); i++) {
        encoded += decoded.at(i) + key;
    }

    return encoded;
}

string FileIO::decryptString(string encoded) {
    string decoded = "";
    for (int i = 0; i < encoded.length(); i++) {
        decoded += encoded.at(i) - key;
    }

    return decoded;
}