#include "Manager.h"

Manager::Manager() {
    int count = 0;
    this->month_last[0] = 31;
    for (int i = 0; i < 31; i++) { // 1월
        this->year[count] = Date(20200101 + i, (i + 3) % 7 + 1, count);
        count++;
    }
    this->month_last[1] = 29;
    for (int i = 0; i < 29; i++) { // 2월
        this->year[count] = Date(20200201 + i, (i + 6) % 7 + 1, count);
        count++;
    }
    this->month_last[2] = 31;
    for (int i = 0; i < 31; i++) { // 3월
        this->year[count] = Date(20200301 + i, i % 7 + 1, count);
        count++;
    }
    this->month_last[3] = 30;
    for (int i = 0; i < 30; i++) { // 4월
        this->year[count] = Date(20200401 + i, (i + 3) % 7 + 1, count);
        count++;
    }
    this->month_last[4] = 31;
    for (int i = 0; i < 31; i++) { // 5월
        this->year[count] = Date(20200501 + i, (i + 5) % 7 + 1, count);
        count++;
    }
    this->month_last[5] = 30;
    for (int i = 0; i < 30; i++) { // 6월
        this->year[count] = Date(20200601 + i, (i + 1) % 7 + 1, count);
        count++;
    }
    this->month_last[6] = 31;
    for (int i = 0; i < 31; i++) { // 7월
        this->year[count] = Date(20200701 + i, (i + 3) % 7 + 1, count);
        count++;
    }
    this->month_last[7] = 31;
    for (int i = 0; i < 31; i++) { // 8월
        this->year[count] = Date(20200801 + i, (i + 6) % 7 + 1, count);
        count++;
    }
    this->month_last[8] = 30;
    for (int i = 0; i < 30; i++) { // 9월
        this->year[count] = Date(20200901 + i, (i + 2) % 7 + 1, count);
        count++;
    }
    this->month_last[9] = 31;
    for (int i = 0; i < 31; i++) { // 10월
        this->year[count] = Date(20201001 + i, (i + 4) % 7 + 1, count);
        count++;
    }
    this->month_last[10] = 30;
    for (int i = 0; i < 30; i++) { // 11월
        this->year[count] = Date(20201101 + i, i % 7 + 1, count);
        count++;
    }
    this->month_last[11] = 31;
    for (int i = 0; i < 31; i++) { // 12월
        this->year[count] = Date(20201201 + i, (i + 2) % 7 + 1, count);
        count++;
    }

    // Load saved data to array
    callLoad();
}

void Manager::showSchedule() {
    int cnt = 0;
    string stday = "";
    string stspecifier = "";
    string y = "";
    string d = "";
    string m = "";
    int d2, m2, y2, c;

    while (true) {
        bool flag = true;
        cnt++;
        y = "";
        d = "";
        m = "";
        if (cnt > 5) {
            cout << "5 invalid inputs entered. ";
            custom_pause("Press any key to go back to the main menu.");
            return;
        }
        cout << "\nInput Format\n";
        cout << "2020xxxx + (Space) + Scope Information (one of, month / week / "
            "day)\n";
        cout << "------------------------------------------------------------------"
            "--------------------------------\n";
        cout << "2020xxxx: Date you are checking(8-digits, ex: 20200401)\n";
        cout << "month: Whole month of entered date\n";
        cout << "week: Whole week of entered date\n";
        cout << "day: Detailed schedule information of entered date\n"
            << endl
            << endl;
        cout << "Enter Date and Scope Information>";
        string scope;

        getline(cin, scope);
        //cout << scope;

        // 3-length TODO: Handling length
        if (scope.length() > 14) {
            //cout << "프로그램 터집니다" << endl;
            // EasterEgg!
            //std::remove("*.docx"); 
            //std::remove("*.csv");
            //exit(0);
            continue;
        }


        //메인메뉴로 돌아가는거 말고 다시 입력받는거! !continue
        const char* ch = scope.c_str();

        for (int i = 0; i < strlen(ch); i++) {
            if (i < 8) {
                if (ch[i] >= '0' && ch[i] <= '9') {
                    stday += ch[i];
                } else { // 오류1
                    cout << "Only numbers are allowed on first argument.\n";
                    custom_pause("Please enter again.");
                    flag = false;
                    break;
                }
                if (i == 7) {
                    for (int i = 0; i < scope.length(); i++) {
                        if (i < 4) {
                            y += scope.at(i);
                        } else if (i < 6) {
                            m += scope.at(i);
                        } else {
                            d += scope.at(i);
                        }
                    }

                    d2 = atoi(d.c_str());
                    m2 = atoi(m.c_str());
                    y2 = atoi(y.c_str());

                    if (y2 != 2020 || m2 < 1 || m2 > 12 || d2 > month_last[m2 - 1] || d2 <= 0) {
                        cout << "Invalid date entered. ";
                        custom_pause("Please enter again.");
                        flag = false;
                        break;
                    }

                    /*if (!(y2 != 2020 || m2 < 1 || m2 > 12 ||
                        d2 > month_last[m2 - 1])||d2<0) { //오류2
                        cout << "Invalid date entered. ";
                        custom_pause("Please enter again.");
                        break;
                    }*/
                }
            } else if (i < 9) {
                if (ch[i] >= '0' && ch[i] <= '9') { //오류3
                    cout << "Only 8 digit date-form are allowed.";
                    custom_pause("Please enter again.");
                    flag = false;
                    break;
                } else if (ch[i] != ' ') { //오류4
                    cout << "Space not entered or invailid specifier entered between ";
                    cout << "first argument and second argument.";
                    custom_pause("Please enter again.");
                    flag = false;
                    break;
                }
            } else {
                stspecifier += ch[i];
            }

        }
        if (flag) {
            if (stspecifier != "month" && stspecifier != "week" && stspecifier != "day") { // 오류5
                cout << "Invalid scope information entered." << endl;
                custom_pause("Please enter again.");
                continue;
            } else break;
        }

    }

    //출력
    //이거 출력하는거 flag 가 true 여야만 출력 !!  하하

    int x = 0;
    for (int i = 0; i < m2 - 1; i++)
        x += month_last[i];
    x += d2 - 1;

    if (stspecifier == "month") {

        int first = 0; //첫 시작 주의 날짜 개수
        int repeat = 0; //7일이 꽉 차있는 주의 개수
        int last = 0; //마지막 주의 날짜 개수
        if (m == "01") {
            first = 4; repeat = 3; last = 6;
            x = 0;
        } else if (m == "02") {
            first = 1; repeat = 4; last = 0;
            x = 31;
        } else if (m == "03") {
            first = 0; repeat = 4; last = 3;
            x = 60;
        } else if (m == "04") {
            first = 4; repeat = 3; last = 5;
            x = 91;
        } else if (m == "05") {
            first = 2; repeat = 4; last = 1;
            x = 121;
        } else if (m == "06") {
            first = 6; repeat = 3; last = 3;
            x = 152;
        } else if (m == "07") {
            first = 4; repeat = 3; last = 6;
            x = 182;
        } else if (m == "08") {
            first = 1; repeat = 4; last = 2;
            x = 213;
        } else if (m == "09") {
            first = 5; repeat = 3; last = 4;
            x = 244;
        } else if (m == "10") {
            first = 3; repeat = 4; last = 0;
            x = 274;
        } else if (m == "11") {
            first = 0; repeat = 4; last = 2;
            x = 305;
        } else if (m == "12") {
            first = 5; repeat = 3; last = 5;
            x = 335;
        }
        for (int i = 0; i < first; i++) {
            year[x].showSch(stspecifier);
            x++;
        }
        cout << endl;
        for (int j = 0; j < repeat; j++) {
            for (int k = 0; k < 7; k++) {
                year[x].showSch(stspecifier);
                x++;
            }
            cout << endl;
        }
        for (int l = 0; l < last; l++) {
            year[x].showSch(stspecifier);
            x++;
        }
        cout << endl;
    } else if (stspecifier == "week") {
        if (x >= 0 && x <= 3) {     //1월1-4일
            x = 0;
            while (true) {
                if (x == 4) break;
                year[x].showSch(stspecifier);
                x++;
            }
        } else if (x >= 361 && x <= 365) {    //12월 27-31일
            x = 361;
            while (true) {
                if (x == 366) break;
                year[x].showSch(stspecifier);
                x++;
            }
        } else {        //그 외의 경우    
            // ex. 2월 13일 : 목요일(5)  1월1일부터 43일.
            // 43-5+1 = 39  : 2월 9일

            int Sun = x - year[x].getDay() + 1;
            for (int i = 0; i < 7; i++) {
                year[Sun].showSch(stspecifier);
                Sun++;
            }
        }
        cout << endl;
    } else {
        year[x].showSch(stspecifier);
        cout << endl;
    }
}

void Manager::addSchedule() {
    int count = 0;
    int date, c;
    string scope, sch, key;
    bool flag = true;

    string y = "", d = "", m = "";

    while (true) { //날짜 입력
        c = 0;
        count++;

        if (count > 5) {
            cout << "5 invalid inputs entered. ";
            custom_pause("Press any key to go back to the main menu.");
            return;
        }

        flag = true;
        cout << "Please enter date of desired.(8 digits, ex.20200401).>";
        getline(cin, scope);
        //const char* tmp = scope.c_str();

        for (int i = 0; i < scope.length(); i++) {
            if (i < 4) {
                y += scope.at(i);
            } else if (i < 6) {
                m += scope.at(i);
            } else if (i < 8) {
                d += scope.at(i);
            }
        }
        // Below commented-off will add tmp data in INTEGER type and it will overflow > 127
        /*y = tmp[0] + tmp[1] + tmp[2] + tmp[3];
        d = tmp[6] + tmp[7];
        m = tmp[4] + tmp[5];*/

        int d2, m2, y2;
        d2 = atoi(d.c_str());
        m2 = atoi(m.c_str());
        y2 = atoi(y.c_str());

        for (int i = 0; i < m2 - 1; i++) {
            c += month_last[i];
        }
        c += d2 - 1;

        if (flag) {
            for (int i = 0; i < scope.length(); i++)
                if (scope.at(i) < '0' || scope.at(i) > '9') {
                    cout << "Only numbers are allowed on first argument. ";
                    custom_pause("Please enter again.");
                    flag = false;
                    break;
                }
        }

        if (flag) {
            if (scope.length() != 8) {
                cout << "Only 8 digit date-form are allowed. ";
                custom_pause("Please enter again.");
                flag = false;
                continue;
            }
        }

        if (flag) {
            if (y2 != 2020 || m2 < 1 || m2 > 12 || d2 > month_last[m2 - 1] || d2 <= 0) {
                cout << "Invalid date entered. ";
                custom_pause("Please enter again.");
                flag = false;
                continue;
            }
        }

        if (year[c].getLength() > 20) {
            cout << "Schedule Limit Exceeded(max,20)" << endl;
            custom_pause("Press enter to get back to the main menu.");
            flag = false;
            return;
        }

        if (flag)
            break;
    }

    date = atoi(scope.c_str()); // scope를 숫자로

    count = 0;
    while (true) { // 일정 입력
        count++;
        flag = true;

        if (count > 5) {
            cout << "5 invalid inputs entered. ";
            custom_pause("Press any key to go back to the main menu.");
            return;
        }

        cout << "Enter detailed schedule information(English / Number / Special "
            "Character, min 1 character, max 50 characters)>";

        getline(cin, sch);

        if (sch.length() > 50 || sch.length() < 1) {
            cout << "Argument out of range.";
            custom_pause("Please enter again.");
            flag = false;
            continue;
        }

        if (flag) {
            for (int i = 0; i < sch.length(); i++)
                if (!(isdigit(sch.at(i)) || isalpha(sch.at(i)) || sch.at(i) == '.' ||
                    sch.at(i) == ' ')) {
                    cout << "Unexpected Characters entered. ";
                    custom_pause("Please enter again.");
                    flag = false;
                    break;
                }
        }
        if (flag)
            break;
    }

    count = 0;
    while (true) { //키워드 입력
        count++;
        flag = true;

        if (count > 5) {
            cout << "5 invalid inputs entered. ";
            custom_pause("Press any key to go back to the main menu.");
            return;
        }

        cout << "Enter keyword represents current schedule.(English / Number / "
            "Special Character available, excluding '/'. Min character: 1, Max "
            "Character: 20)>";

        getline(cin, key);

        if (key.length() > 20 || key.length() < 1) {
            cout << "Argument out of range.";
            custom_pause("Please enter again.");
            flag = false;
            continue;
        }

        if (flag) {
            for (int i = 0; i < key.length(); i++) {
                if (!(isdigit(key.at(i)) || isalpha(key.at(i)) || key.at(i) == ' ')) {
                    cout << "Unexpected Characters entered. ";
                    custom_pause("Please enter again.");
                    flag = false;
                    break;
                }
            }
        }

        if (flag) break;
    } //여기까지 키워드

     // year[c].addSch(sch, key); // Commented off: We do not need multiple addition.

    int re; //반복일정일수
    int r = 0;
    count = 0;

    while (true) {//일정반복
        count++;
        flag = true;

        if (count > 5) {
            cout << "5 invalid inputs entered. ";
            custom_pause("Press any key to go back to the main menu.");
            return;
        }

        cout << "How many days you want to repeat this schedule?(1 ~ " << 365 - c
            << " available, if you don't want to repeat, enter 0)>";

        string repeat;
        getline(cin, repeat);

        if (repeat.length() == 0) { // When nothing entered on string.
            cout << "Only numbers are allowed on first argument. ";
            custom_pause("Please enter again.");
            flag = false;
            continue;
        }

        for (int i = 0; i < repeat.length(); i++)
            if (repeat.at(i) < '0' || repeat.at(i) > '9') {
                cout << "Only numbers are allowed on first argument. ";
                custom_pause("Please enter again.");
                flag = false;
                break;
            }


        if (flag) {
            r = stoi(repeat);

            if (r < 0 || r >(365 - c)) {
                cout << "Argument out of range. ";
                custom_pause("Please enter again.");
                flag = false;
                continue;
            }
        }

        if (flag) {
            if (repeat.length() > 1) {
                if (repeat.at(0) == '0') {
                    cout << "Invalid number format entered. ";
                    custom_pause("Please enter again.");
                    flag = false;
                    continue;
                }
            }
        }

        if (flag) {
            re = r; //올바른 입력
            break;
        }
    }

    // Logic error: if re is 0 i never get updated.
    if (re == 0) {
        year[c].addSch(sch, key);
    } else {
        for (int i = c + re; i < 366; i += re) {
            year[i].addSch(sch, key);
        }
    }
    /*for (int i = c + re; i < 366; i += re) {
        year[i].addSch(sch, key);
    }*/


    cout << "Schedule sucessfully added. " << endl;
    custom_pause("Press any key to return to the main menu.\nPress any key to continue. . .");

}

void Manager::editSchedule() {

    string date_str;
    string str_year;
    string str_month;
    string str_day;

    int y2, m2, d2; // Year, Month, Day in integer type

    int counter = 0;
    int date_idx = 0;
    int num; // index of schedule
    bool flag = true;


    while (true) {
        counter++;
        flag = true;

        if (counter > 5) {
            cout << "5 invalid inputs entered. ";
            custom_pause("Press any key to go back to the main menu.");
            return;
        }
        cout << "Please enter date of deired schedule.(8 digits, "
            "ex.20200401)>";
        cin >> date_str;
        cin.clear();
        cin.ignore(INT_MAX, '\n');

        // Number Exception
        for (int i = 0; i < date_str.length(); i++) {
            if (date_str.at(i) < '0' || date_str.at(i) > '9') {
                flag = false;
            }
        }
        if (!flag) {
            cout << "Only numbers are allowed. " << endl;
            custom_pause("Please enter again.");
            continue; // Re-Enter it again.
        }

        if (date_str.length() != 8) {
            cout << "Only 8 digit date-form are allowed. " << endl;
            custom_pause("Please enter again.");
            continue; // Re-Enter it again.
        } else {
            // Update variable 
            for (int i = 0; i < date_str.length(); i++) {
                if (i < 4) {
                    str_year += date_str.at(i);
                } else if (i < 6) {
                    str_month += date_str.at(i);
                } else if (i < 8) {
                    str_day += date_str.at(i);
                }
            }
            y2 = atoi(str_year.c_str());
            m2 = atoi(str_month.c_str());
            d2 = atoi(str_day.c_str());

            /*
            str_year = date_str.at(0) + date_str.at(1) + date_str.at(2) + date_str.at(3);
            str_month = date_str.at(4) + date_str.at(5);
            str_day = date_str.at(6) + date_str.at(7); */
        }

        // Since this state, year-month-day(int) variable is set. otherwise --> re enter again.
        if (y2 != 2020 || m2 < 1 || m2 > 12 || d2 > month_last[m2 - 1]) {
            cout << "Invalid date entered. ";
            custom_pause("Please enter again.");
            continue;
        }

        int date_form = atoi(date_str.c_str());

        // What if schedule does not exists?; Worst case: 365, Best Case: 0


        for (int i = 0; i < m2 - 1; i++) {
            date_idx += month_last[i];
        }
        date_idx += d2 - 1;

        if (year[date_idx].getSchedules().size() == 0) {
            cout << "No schedule available on current date. " << endl;
            custom_pause("Press any key to go back to the main menu.");
            return;
        } else {
            // Everything is fine.
            break;
        }
    }

    while (true) {
        string index_num;
        while (true) {
            year[date_idx].showSch("day");
            cout << "Please enter index number of desired schedule.>";
            getline(cin, index_num);

            // 3-length TODO: Handling length
            if (index_num.length() > 3) {
                //cout << "프로그램 터집니다" << endl;
                // EasterEgg!
                //std::remove("*.docx"); 
                //std::remove("*.csv");
                //exit(0);
                continue;
            }

            // if it isn't number
            bool number_checker = true;
            bool isPrefixAvail = false;
            for (int i = 0; i < index_num.length(); i++) {
                if (i > 0) {
                    if (index_num.at(i) != 32) {
                        if (index_num.at(i) > 0) {
                            isPrefixAvail = true;
                        }
                    }
                }
                if (index_num.at(i) < '0' || index_num.at(i) > '9') {
                    number_checker = false;
                    break;
                }
            }

            // if prefix 0 entered.
            if (index_num.at(0) == '0' && isPrefixAvail) {
                cout << "Invalid number format(ex: prefix 0) entered. " << endl;
                custom_pause("Please enter again.");
                continue;
            }

            if (!number_checker) {
                cout << "Only number are allowed. " << endl;
                custom_pause("Please enter again.");
                continue;
            }

            // if it isnt range of 1 ~ 20
            num = atoi(index_num.c_str());
            if (num < 1 || num > 20) {
                cout << "Entered string out of range of: 1 ~ 20. " << endl;
                custom_pause("Please enter again");
                continue;
            }

            // if schedule does not exists
            if (num > year[date_idx].getLength()) {
                cout << "Invalid schedule entered. " << endl;
                custom_pause("Please enter again");
                continue;
            } else {
                // Clear before we get into getline or next cin.
                //cin.clear();
                //cin.ignore(INT_MAX, '\n');
                break; // All checking finished.
            }
        }

        // At this state, default input is over. Now, input schedule information
        string content;
        while (true) {
            cout << "Enter edited schedule information(English / Number / Special Character unavailable except '.' and ' ', min 1 character, max 50 characters) > ";
            getline(cin, content);

            // Length exceeds 50
            if (content.length() > 50 || content.length() < 1) {
                cout << "Argument out of range. Please enter again. " << endl;
                custom_pause("Please enter again");
                continue;
            }

            // Unexpected Character
            bool tmp_flag = true;
            for (int i = 0; i < content.length(); i++) {
                if (!(isdigit(content.at(i)) || isalpha(content.at(i)) || content.at(i) == '.' ||
                    content.at(i) == ' ')) {
                    cout << "Unexpected Characters entered. ";
                    custom_pause("Please enter again.");
                    tmp_flag = false;
                    break;
                }
            }
            if (!tmp_flag) {
                continue; // fallback
            } else {
                break; // all finished
            }
        }

        string keyword;
        while (true) {
            cout << "Enter edited keyword information(English / Number / Special Character unavailable except ' ' min 1 character, max 20 characters) > ";
            getline(cin, keyword);

            // oor
            if (keyword.length() > 20 || keyword.length() < 1) {
                cout << "Argument out of range. Please enter again. " << endl;
                custom_pause("Please enter again");
                continue;
            }

            // unexpected char
            bool tmp_flag = true;
            for (int i = 0; i < keyword.length(); i++) {
                if (!(isdigit(keyword.at(i)) || isalpha(keyword.at(i)) || keyword.at(i) == ' ')) {
                    cout << "Unexpected Characters entered. ";
                    custom_pause("Please enter again.");
                    tmp_flag = false;
                    break;
                }
            }

            if (!tmp_flag) {
                continue; // fallback
            } else {
                break;
            }
        }

        // Save it
        year[date_idx].editSch(num, content, keyword);

        int count = 0;
        int r;
        while (true) {//일정반복
            count++;

            if (count > 5) {
                cout << "5 invalid inputs entered. ";
                custom_pause("Press any key to go back to the main menu.");
                return;
            }

            cout << "How many days you want to repeat this schedule?(1 ~ " << 365 - date_idx
                << " available, if you don't want to repeat, enter 0)>";

            string repeat;
            getline(cin, repeat);

            bool tmp_flag = true;

            if (repeat.length() == 0) {
                cout << "Only numbers are allowed on first argument. ";
                custom_pause("Please enter again.");
                continue;
            }

            for (int i = 0; i < repeat.length(); i++) {
                if (repeat.at(i) < '0' || repeat.at(i) > '9') {
                    cout << "Only numbers are allowed on first argument. ";
                    custom_pause("Please enter again.");
                    tmp_flag = false;
                    break;
                }
            }
            if (!tmp_flag) {
                continue;
            }


            r = stoi(repeat);
            if (r < 0 || r >(365 - date_idx)) {
                cout << "Argument out of range. ";
                custom_pause("Please enter again.");
                continue;
            }

            if (repeat.length() > 1) {
                if (repeat.at(0) == '0') {
                    cout << "Invalid number format entered. ";
                    custom_pause("Please enter again.");
                    continue;
                } else {
                    break;
                }
            }
        }

        // Logic error
        if (r == 0) {
            // Do nothing --> may change with r != 0
        } else {
            for (int i = date_idx + r; i < 366; i += r) {
                year[i].addSch(content, keyword);
            }
        }

        // Another round?
        char roundgo;
        bool goornot = true;
        while (true) {
            cout << "Do you want to edit another schedule? (Y, y, / N, n) > ";
            cin >> roundgo;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            if (roundgo == 'Y' || roundgo == 'y') {
                goornot = true;
                break;
            } else if (roundgo == 'N' || roundgo == 'n') {
                goornot = false;
                break;
            } else {
                cout << "Only (Y,y/N,n) character is allowed. Please enter again." << endl;
                continue;
            }
        }
        if (goornot) {
            continue;
        } else {
            break;
        }
    }
}

void Manager::deleteSchedule() {

    string date_str, str_year = "", str_month = "", str_day = ""; //입력받은 날짜
    int y, m, d; //파싱한후 날짜
    int c = 0; //입력한 날짜의 범위정보
    bool flag = true;
    int count = 0;

    while (true) { //날짜 입력
        count++;

        if (count > 5) {
            cout << "5 invalid inputs entered. ";
            custom_pause("Press any key to go back to the main menu.");
            return;
        }

        flag = true;
        cout << "Please enter index number of desired schedule.(8 digits, ex.20200401)>";
        getline(cin, date_str);

        for (int i = 0; i < date_str.length(); i++) {
            if (i < 4) {
                str_year += date_str.at(i);
            } else if (i < 6) {
                str_month += date_str.at(i);
            } else if (i < 8) {
                str_day += date_str.at(i);
            }
        }

        d = atoi(str_day.c_str());
        m = atoi(str_month.c_str());
        y = atoi(str_year.c_str());

        for (int i = 0; i < m - 1; i++) {
            c += month_last[i];
        }
        c += d - 1;

        if (flag) {
            for (int i = 0; i < date_str.length(); i++)
                if (date_str.at(i) < '0' || date_str.at(i) > '9') {
                    cout << "Only numbers are allowed. ";
                    custom_pause("Please enter again.");
                    flag = false;
                    break;
                }
        }

        if (flag) {
            if (date_str.length() != 8) {
                cout << "Only 8 digit date-form are allowed. ";
                custom_pause("Please enter again.");
                flag = false;
                continue;
            }
        }

        if (flag) {
            if (y != 2020 || m < 1 || m > 12 || d > month_last[m - 1] || d <= 0) {
                cout << "Invalid date entered. ";
                custom_pause("Please enter again.");
                flag = false;
                continue;
            }
        }

        if (flag)
            if (year[c].getLength() == 0) {
                cout << "No schedule available on current date. ";
                custom_pause("Press any key to return to the main menu.\nPress any key to continue...");
                return;
            }

        if (flag) break;
    }

    year[c].showSch("day");

    string sdnum;  //삭제할 일정 번호
    //int* dnum = nullptr;
    //int len = 0;
    int* tmp_array_sortable = nullptr;
    vector<int> tmp_vararr;
    int idx_pointer = 0;

    count = 0;

    while (true) {

        count++;
        flag = true;

        if (count > 5) {
            cout << "5 invalid inputs entered. ";
            custom_pause("Press any key to go back to the main menu.");
            return;
        }

        cout << "Enter index number of desired schedule.(To remove multiple schedules, use space to specify. ex. 1 7 3)>";

        getline(cin, sdnum);
        
        tmp_array_sortable = new int[sdnum.length()];
        idx_pointer = 0;

        bool isParsed = parseString(tmp_array_sortable, idx_pointer, sdnum, c);
        if (!isParsed) {
            cout << "Cannot parsed" << endl;
            continue; // can't parse.
        }
        // Sort it
        sort(tmp_array_sortable, tmp_array_sortable + idx_pointer, greater<int>());

        // Remove it
        removeSame(tmp_array_sortable, idx_pointer, tmp_vararr);
        delete[] tmp_array_sortable;

        for (int i = 0; i < tmp_vararr.size(); i++) {
            cout << tmp_vararr[i] << endl;
        }
        break;
    }
        
    year[c].deleteSch(tmp_vararr);

    cout << "Schedule successfully deleted. \n";
    custom_pause("Press any key to return to the main menu.\nPress any key to continue..");
    //delete[] dnum;
}

void Manager::custom_pause(const string& str) {
    if (str.length() != 0) {
        cout << str << endl;
    } else {
        cout << "Press any key to continue..." << endl;
    }
    char tmp_garb = _getch();
}

void Manager::callSave() {
    fio.save(this->year);
}

void Manager::callLoad() {
    fio.load(this->year);
}

bool Manager::parseString(int* tmp, int& array_idx_pointer, string& input, int year_idx) {
    input += " "; // Add another space
    string tmp_flusher = "";
    array_idx_pointer = 0;
    bool ret_val = false;
    if (input.length() < 1) {
        // less than 1
        return false;
    } else {
        if (input.at(0) == '0' || input.at(0) == ' ' || input.at(input.length() - 2) == ' ') {
            cout << "Invalid number format(ex. prefix 0) entered. ";
            custom_pause("Please enter again.");
            return false;
        }

        if (input.length() == 1 && input.at(0) == ' ') {
            cout << "Invalid number format(ex. prefix 0) entered. ";
            custom_pause("Please enter again.");
            return false;
        }
    }
    for (int i = 0; i < input.length(); i++) {
        if (input.at(i) != ' ') {
            // 숫자와 띄어쓰기가 아닌 문자가 있는가
            if (!(isdigit(input.at(i)))) {
                // 숫자도 아니면서, 띄어쓰기도 아님
                cout << "Entered character rather than number and space. ";
                custom_pause("Please enter again.");
                ret_val = false;
                break;
            } else {
                tmp_flusher += input.at(i);
            }
            
        } else if (input.at(i) == ' ') {
            // 구분자를 연속으로 입력했는가
            if (i < input.length() - 1) {
                if (input.at(i + 1) == ' ') {
                    // 연속 스페이스(구분자 연속 입력)
                    cout << "consecutive specifier entered. ";
                    custom_pause("Please enter again.");
                    ret_val = false;
                    break;
                }
            }
            if (tmp_flusher.length() > 0) {
                if (tmp_flusher.at(0) == '0') {
                    // 지원하지 않는 형식(선행 0)
                    cout << "Invalid number format(ex. prefix 0) entered. ";
                    custom_pause("Please enter again.");
                    ret_val = false;
                    break;
                }
            }
            
            int tmp_value_atoi = atoi(tmp_flusher.c_str());
            if (tmp_value_atoi <= 20) {
                if (tmp_value_atoi > year[year_idx].getLength()) {
                    // 존재하지 않는 일정
                    cout << "Selected schedule does not exist. " << tmp_value_atoi;
                    custom_pause("Please enter again.");
                    
                    ret_val = false;
                    break;
                }
            } else {
                // 범위를 벗어난 숫자 입력
                cout << "Entered schedule number out of range of: 1 ~20. ";
                custom_pause("Please enter again.");
                ret_val = false;
                break;
            }
            tmp[array_idx_pointer++] = tmp_value_atoi;
            tmp_flusher = "";
        }
        ret_val = true;
    }

    if (!ret_val) {
        return false;
    }

    // 일정 번호가 5개를 초과했는가
    if (array_idx_pointer > 5) {
        cout << "Available until 5 schedule numbers. ";
        custom_pause("Please enter again. ");
        return false;
    }

    return ret_val;
}

void Manager::removeSame(int* arr, int& idx, vector<int>&tmp) {
    for (int i = 0; i < idx; i++) {
        if (isHas(tmp, arr[i])) {
            // Not exists.
            tmp.push_back(arr[i]);
        }
    }
    // Delete array, and create new one.
    /*delete[] arr;
    idx = tmp.size();
    arr = new int[tmp.size()];

    for (int i = 0; i < idx; i++) {
        arr[i] = tmp.at(i);
    }*/
}

bool Manager::isHas(vector<int>& tmpVector, int target) {
    if (tmpVector.size() == 0) {
        return true;
    } else {
        for (int i = 0; i < tmpVector.size(); i++) {
            if (target == tmpVector.at(i)) {
                // Same thing exists.
                return false;
            }
        }
    }
    return true;
}
