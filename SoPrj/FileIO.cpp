#include "FileIO.h"

void FileIO::save(Date* date_data) {
    // File structure
    // File descriptor
    // Date count(366-constant variable)
    // Date (20200101)
    // Schedule count;
    // Schedule
    // Schedule keyword
    // Schedule content

    // Date again(iterated)

    ofstream outfile("userInfo");
    string tmp = "";

    // File Descriptor
    tmp.append("This is T3 from SoPrj\n");
    tmp.append(to_string(max).append("\n"));

    for (int i = 0; i < max; i++) {
        // Date
        tmp.append(to_string(date_data[i].getDate()).append("\n"));
        
        // Schedule count
        tmp.append(to_string(date_data[i].getSchedules().size()).append("\n"));

        // Schedule
        for (int a = 0; a < date_data[i].getSchedules().size(); a++) {
            // Schedule keyword
            tmp.append(date_data[i].getSchedules().at(a).getKeyword() + "\n");
            // Schedule content
            tmp.append(date_data[i].getSchedules().at(a).getContent() + "\n");
        }
    }
    tmp = encryptString(tmp);

    // save string data to file
    outfile << tmp;
    outfile.close();
}

void FileIO::load(Date* date_data) {
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

    // Decrypt String first.
    tmpEncoded = decryptString(tmpEncoded);

    // Save decrypted string to file
    ofstream outputTmp("userInfoTMP");
    outputTmp << tmpEncoded;
    outputTmp.close(); // close

    /* Class should be created by now. Skipping nullptr check. */

    // Open decrypted file
    string tmp;
    ifstream fileDecrypted("userInfoTMP");

    // Check File descriptor
    getline(fileDecrypted, tmp);
    if (tmp == "This is T3 from SoPrj") { // File descriptor IS CORRECT
        // Check Maximum number of 2020(should be 366)
        getline(fileDecrypted, tmp);
        if (tmp != "366") {
            // Max number is NOT 366  --> Ignore file reading, fall back to normal data(=0)
            return;
        }
    } else {
        // that kinda thing does not exists
        return;
    }

    // Assume descriptor is Correct.
    for (int i = 0; i < max; i++) {
        // Date determination - do we need this?
        // Anyway. flush away buffer since its in string data;
        getline(fileDecrypted, tmp); // Ahhh handling needed if something happens
        if (tmp.length() != 8) {
            // Wrong or corrupted file format. Falling back to default data;
            return;
        }

        // Schedule count --> Reserve
        getline(fileDecrypted, tmp);
        int schedule_count = atoi(tmp.c_str());
        if (schedule_count < 0 || schedule_count > 20) {
            // Wrong or corrupted file format. Falling back to default data
            // This is caused when count of schedule is below 0 or more than 20.(Program sets its limit to 0 ~ 20)
            return;
        }

        // Schedule
        string keyword_file;
        string content_file;
        for (int a = 0; a < schedule_count; a++) {
            // Schedule keyword
            getline(fileDecrypted, keyword_file);

            // Schedule content
            getline(fileDecrypted, content_file);

            if (keyword_file.length() > 20 || content_file.length() > 50) {
                // Something went wrong. Skipping THIS schedule only.
                continue;
            } else {
                // Since we have "continue" just two lines above, else phrase might not be necessary, 
                // But thinking of read-ability of code, writing else might be more better.
                date_data[i].addSch(content_file, keyword_file);
            }
        }
    }
    fileDecrypted.close();
    remove("userInfoTMP");
}

string FileIO::decryptString(string encoded) {
    string decoded = "";
    for (int i = 0; i < encoded.length(); i++) {
        decoded += encoded.at(i) - key;
    }

    return decoded;
}

string FileIO::encryptString(string decoded) {
    string encoded = "";
    for (int i = 0; i < decoded.length(); i++) {
        encoded += decoded.at(i) + key;
    }

    return encoded;
}