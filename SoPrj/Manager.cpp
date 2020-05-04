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
    string scope_whatever;
    string y = "";
    string d = "";
    string m = "";
    int d2, m2, y2;

    while (true) {
        bool flag = true;
        cnt++;
        y = "";
        d = "";
        m = "";
        scope_whatever = "";
        if (cnt > 5) {
            cout << "5 invalid inputs entered. ";
            custom_pause("Press any key to go back to the main menu.");
            return;
        } //
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

        //메인메뉴로 돌아가는거 말고 다시 입력받는거! !continue
        const char* ch = scope.c_str();
        string day_tmp_t = "";
        int ctr = 0;
	
        for (int i = 0; i < scope.length(); i++) {
            if (scope.at(i) == 32) {
                ctr++;
            }
        }

        if (ctr > 1 || ctr == 0) {
            cout << "Space not entered or invailid specifier entered between ";
            cout << "first argument and second argument.";
            custom_pause("Please enter again.");

            // Get out somehow
            continue;
        }
        
        // Get Date
        for (int i = 0; i < scope.length(); i++) {
            if (scope.at(i) != 32) {
                // if at(i) neq integer
                if (scope.at(i) < '0' || scope.at(i) > '9') {
                    cout << "Only numbers are allowed on first argument.";
                    custom_pause("Please enter again.");
                    flag = false;
                    break;
                    // get out of whole loop.
                } else {
                    // it is integer, store it to tmp string
                    day_tmp_t += scope.at(i);
                }
            } else if (scope.at(i) == 32) {
                if (i + 1 < scope.length()) {
                    // no specifier enetered.
                    scope_whatever = scope.substr(i+1, scope.length());
                } else {
                    cout << "Invalid scope information entered." << endl;
                    custom_pause("Please enter again.");
                    flag = false;
                }
                break;
            }
        }

        if (!flag) continue;

        if (day_tmp_t.length() == 8) {
            for (int i = 0; i < day_tmp_t.length(); i++) {
                if (i < 4) {
                    y += day_tmp_t.at(i);
                } else if (i < 6) {
                    m += day_tmp_t.at(i);
                } else {
                    d += day_tmp_t.at(i);
                }
            }
            y2 = atoi(y.c_str());
            m2 = atoi(m.c_str());
            d2 = atoi(d.c_str());
            if (y2 != 2020 || m2 < 1 || m2 > 12 || d2 > month_last[m2 - 1] || d2 <= 0) {
                cout << "Invalid date entered. ";
                custom_pause("Please enter again.");
                flag = false;
            }
        } else {
            // Not 8 digit --> Error
            cout << "Only 8 digit date-form are allowed.";
            custom_pause("Please enter again.");
            flag = false;
        }

        // got scope at this point.
        if (flag) {
            if (scope_whatever != "month" && scope_whatever != "week" && scope_whatever != "day") { // 오류5
                cout << "Invalid scope information entered." << endl;
                custom_pause("Please enter again.");
                continue;
            } else break;
        }

        if (flag) break;
    }

    //출력
    //이거 출력하는거 flag 가 true 여야만 출력 !!  하하

    int x = 0;
    for (int i = 0; i < m2 - 1; i++)
        x += month_last[i];
    x += d2 - 1;

    if (scope_whatever == "month") {

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
            year[x].showSch(scope_whatever);
            x++;
        }
        cout << endl;
        for (int j = 0; j < repeat; j++) {
            for (int k = 0; k < 7; k++) {
                year[x].showSch(scope_whatever);
                x++;
            }
            cout << endl;
        }
        for (int l = 0; l < last; l++) {
            year[x].showSch(scope_whatever);
            x++;
        }
        cout << endl;
    } else if (scope_whatever == "week") {
        if (x >= 0 && x <= 3) {     //1월1-4일
            x = 0;
            while (true) {
                if (x == 4) break;
                year[x].showSch(scope_whatever);
                x++;
            }
        } else if (x >= 361 && x <= 365) {    //12월 27-31일
            x = 361;
            while (true) {
                if (x == 366) break;
                year[x].showSch(scope_whatever);
                x++;
            }
        } else {        //그 외의 경우    
            // ex. 2월 13일 : 목요일(5)  1월1일부터 43일.
            // 43-5+1 = 39  : 2월 9일

            int Sun = x - year[x].getDay() + 1;
            for (int i = 0; i < 7; i++) {
                year[Sun].showSch(scope_whatever);
                Sun++;
            }
        }
        cout << endl;
    } else {
        year[x].showSch(scope_whatever);
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
        y = "", d = "", m = "";

        if (count > 5) {
            cout << "5 invalid inputs entered. ";
            custom_pause("Press any key to go back to the main menu.");
            return;
        }

        flag = true;
        cout << "Please enter date of desired schedule.(8 digits, ex.20200401)>";
        getline(cin, scope);
  
        for (int i = 0; i < scope.length(); i++) {
            if (i < 4) {
                y += scope.at(i);
            } else if (i < 6) {
                m += scope.at(i);
            } else if (i < 8) {
                d += scope.at(i);
            }
        }

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

        if (year[c].getLength() > 19) {
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
            cout << "Argument out of range. ";
            custom_pause("Please enter again.");
            flag = false;
            continue;
        }

        if (flag) {
            for (int i = 0; i < sch.length(); i++)
                if (!((sch.at(i)>='a'&&sch.at(i)<='z')||(sch.at(i) >= 'A' && sch.at(i) <= 'Z')|| (sch.at(i) >= '0' && sch.at(i) <= '9')|| (sch.at(i) == ' ' || sch.at(i) == '.'))) {
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
            cout << "Argument out of range. ";
            custom_pause("Please enter again.");
            flag = false;
            continue;
        }

        if (flag) {
            for (int i = 0; i < key.length(); i++) {
                if (!((key.at(i)>='a'&&key.at(i)<='z')||(key.at(i) >= 'A' && key.at(i) <= 'Z')|| (key.at(i) >= '0' && key.at(i) <= '9')|| (key.at(i) == ' '))) {
                    cout << "Unexpected Characters entered. ";
                    custom_pause("Please enter again.");
                    flag = false;
                    break;
                }
            }
        }

        if (flag) break;
    } //여기까지 키워드

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
        cout << "How many days you want to repeat this schedule?(";
        if ((365 - c) > 1)cout << "1 ~ ";
        cout << 365 - c;
        cout << " available, if you don't want to repeat, enter 0)>";

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
        for (int i = c ; i < 366; i += re) {        //수정
            year[i].addSch(sch, key);
        }
    }

    cout << "Schedule sucessfully added. " << endl;
    custom_pause("Press any key to return to the main menu.\nPress any key to continue. . .");

}

void Manager::editSchedule() {

    string date_str;
    string str_year;
    string str_month;
    string str_day;

    int y2, m2, d2; // Year, Month, Day in integer type

    int counter = 0; //5번 빠져나가기
    int date_idx = 0; //date 인덱스 번호
    int num; // index of schedule
    bool flag = true;

    while (true) {
        str_year = "";
        str_month = "";
        str_day = "";
        date_idx = 0;
        num = 0;
        counter++;
        flag = true;
        
        if (counter > 5) {
            cout << "5 invalid inputs entered. ";
            custom_pause("Press any key to go back to the main menu.");
            return;
        }
        cout << "Please enter date of deired schedule.(8 digits, "
            "ex.20200401)>";

        getline(cin,date_str);

        // Number Exception
        for (int i = 0; i < date_str.length(); i++) {
            if (date_str.at(i) < '0' || date_str.at(i) > '9') {
                flag = false;
                break;
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
        }

        // Since this state, year-month-day(int) variable is set. otherwise --> re enter again.
        if (y2 != 2020 || m2 < 1 || m2 > 12 || d2 > month_last[m2 - 1]) {
            cout << "Invalid date entered. ";
            custom_pause("Please enter again.");
            continue;
        }

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
       
            if (counter > 5) {
                cout << "5 invalid inputs entered. ";
                custom_pause("Press any key to go back to the main menu.");
                return;
            }

            year[date_idx].showSch("day");
            cout << "Please enter index number of desired schedule.>";
            getline(cin, index_num);
            if (index_num.length() == 0) {
                counter++;
                cout << "Invalid number format(ex: prefix 0) entered. " << endl;
                custom_pause("Please enter again.");
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
                counter++;
                cout << "Invalid number format(ex: prefix 0) entered. " << endl;
                custom_pause("Please enter again.");
                continue;
            }

            if (!number_checker) {
                counter++;
                cout << "Only number are allowed. " << endl;
                custom_pause("Please enter again.");
                continue;
            }

            // if it isnt range of 1 ~ 20
            num = atoi(index_num.c_str());
            if (num < 1 || num > 20) {
                counter++;
                cout << "Entered string out of range of: 1 ~ 20. " << endl;
                custom_pause("Please enter again");
                continue;
            }

            // if schedule does not exists
            if (num > year[date_idx].getLength()) {
                counter++;
                cout << "Invalid schedule entered. " << endl;
                custom_pause("Please enter again");
                continue;
            } else {
                break; // All checking finished.
            }
        }

        // At this state, default input is over. Now, input schedule information
        string content;
        while (true) {
            if (counter > 5) {
                cout << "5 invalid inputs entered. ";
                custom_pause("Press any key to go back to the main menu.");
                return;
            }
            cout << "Enter edited schedule information(English / Number / Special Character unavailable except '.' and ' ', min 1 character, max 50 characters) >";
            getline(cin, content);

            // Length exceeds 50
            if (content.length() > 50 || content.length() < 1) {
                counter++;
                cout << "Argument out of range. Please enter again. " << endl;
                custom_pause("Please enter again");
                continue;
            }

            // Unexpected Character
            bool tmp_flag = true;
            for (int i = 0; i < content.length(); i++) {
                if (!((content.at(i)>='a'&&content.at(i)<='z')||(content.at(i) >= 'A' && content.at(i) <= 'Z')|| (content.at(i) >= '0' && content.at(i) <= '9')|| (content.at(i) == ' ' || content.at(i) == '.'))) {
                    counter++;
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
            if (counter > 5) {
                cout << "5 invalid inputs entered. ";
                custom_pause("Press any key to go back to the main menu.");
                return;
            }

            cout << "Enter edited keyword information(English / Number / Special Character unavailable except ' ' min 1 character, max 20 characters) >";
            getline(cin, keyword);

            // oor
            if (keyword.length() > 20 || keyword.length() < 1) {
                counter++;
                cout << "Argument out of range. Please enter again. " << endl;
                custom_pause("Please enter again");
                continue;
            }

            // unexpected char
            bool tmp_flag = true;
            for (int i = 0; i < keyword.length(); i++) {
                if (!((keyword.at(i)>='a'&&keyword.at(i)<='z')||(keyword.at(i) >= 'A' && keyword.at(i) <= 'Z')|| (keyword.at(i) >= '0' && keyword.at(i) <= '9')|| (keyword.at(i) == ' '))) {
                    counter++;
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

        int r;
        while (true) {//일정반복
            if (counter > 5) {
                cout << "5 invalid inputs entered. ";
                custom_pause("Press any key to go back to the main menu.");
                return;
            }
           
            cout << "How many days you want to repeat this schedule?(";
            if ((365 - date_idx) > 1)cout << "1 ~ ";
            cout << 365 - date_idx;
            cout << " available, if you don't want to repeat, enter 0)>";

            string repeat;
            getline(cin, repeat);

            bool tmp_flag = true;

            if (repeat.length() == 0) {
                counter++;
                cout << "Only numbers are allowed on first argument. ";
                custom_pause("Please enter again.");
                continue;
            }

            for (int i = 0; i < repeat.length(); i++) {
                if (repeat.at(i) < '0' || repeat.at(i) > '9') {
                    counter++;
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
                counter++;
                cout << "Argument out of range. ";
                custom_pause("Please enter again.");
                continue;
            }

            if (repeat.length() > 1) {
                if (repeat.at(0) == '0') {
                    counter++;
                    cout << "Invalid number format entered. ";
                    custom_pause("Please enter again.");
                    continue;
                }
            }
            break;
        }

        // Logic error
        if (r == 0) {
            // Save it
            year[date_idx].editSch(num, content, keyword);
        } else {
            for (int i = date_idx + r; i < 366; i += r) {
                year[i].addSch(content, keyword);
            }
        }

        // Another round?
        string roundgo;
        bool goornot = true;
        bool lineCheck = true;
        while (true) {
            if (counter > 5) {
                cout << "5 invalid inputs entered. ";
                custom_pause("Press any key to go back to the main menu.");
                return;
            }

            cout << "Do you want to edit another schedule? (Y, y, / N, n) >";
            lineCheck = true;
            getline(cin,roundgo);

            if (roundgo.length()!=1) {
                counter++;
                cout << "Only (Y,y/N,n) character is allowed. Please enter again." << endl;
                custom_pause("Please enter again.");
                lineCheck = false;
                continue;
            }
            if (lineCheck) {
                if (roundgo.at(0) == 'Y' || roundgo.at(0) == 'y') {
                    goornot = true;
                    break;
                }
                else if (roundgo.at(0) == 'N' || roundgo.at(0) == 'n') {
                    goornot = false;
                    cout << "Schedule successfully edited.\nPress any key to return to the main menu." << endl;
                    custom_pause("Press any key to continue.");
                    break;
                }
                else {
                    counter++;
                    cout << "Only (Y,y/N,n) character is allowed. Please enter again." << endl;
                    continue;
                }
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
        c = 0;

        if (count > 5) {
            cout << "5 invalid inputs entered. ";
            custom_pause("Press any key to go back to the main menu.");
            return;
        }

        flag = true;
		
        cout << "Please enter date of desired schedule.(8 digits, ex.20200401). >";
        getline(cin, date_str);
        str_year = "", str_month = "", str_day = "";

        if (date_str.length() < 1) { // 엔터
            cout << "Only numbers are allowed. ";
            custom_pause("Please enter again.");
            flag = false;
            continue;
        }
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
            continue;
        }
        // Sort it
        sort(tmp_array_sortable, tmp_array_sortable + idx_pointer, greater<int>());

        // Remove it
        removeSame(tmp_array_sortable, idx_pointer, tmp_vararr);
        delete[] tmp_array_sortable;

        break;
    }
        
    year[c].deleteSch(tmp_vararr);

    cout << "Schedule successfully deleted. \n";
    custom_pause("Press any key to return to the main menu.\nPress any key to continue..");
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
    string tmp_flusher = "";
    array_idx_pointer = 0;
    bool ret_val = false;

    if (input.length() < 1) { // 엔터 입력
        // less than 1
        cout << "Entered character rather than number and space.";
        custom_pause("Please enter again.");
        return false;
    }
    else if (input.length() < 2 && input.at(0) == ' ') {
        //스페이스 하나만 입력했을 경우(빈문자)
        cout << "Invalid number format(ex. prefix 0) entered.";
        custom_pause("Please enter again.");
        return false;
    }
    // 숫자와 띄어쓰기가 아닌 문자가 있는가
    // 이걸 input 에 대해 먼저 수행해야 우선순위 1
    for (int i = 0; i < input.length(); i++) {
        if (input.at(i) != ' ' && !((input.at(i) >= '0' && input.at(i) <= '9'))) {
            cout << "Entered character rather than number and space.";
            custom_pause("Please enter again.");
            return false;
        }
    }

    input += " "; // Add another space // 번호 구분을 위해서

    if ((input.at(0) == ' ' && input.at(1) != ' ') || (input.at(input.length() - 2) == ' ' && input.at(input.length() - 3) != ' ')) {
        //맨 앞 혹은 맨 뒤에 스페이스 하나를 입력한 경우 (연속 구분자x)
        cout << "Invalid number format(ex. prefix 0) entered.";
        custom_pause("Please enter again.");
        return false;
    }
    
    // 구분자 연속 or 5개 초과의 번호를 입력헀는가 
    int cnt = 0; // 몇개 입력받았는지 (단순히 구분자로 나눔)
    for (int i = 0; i < input.length(); i++) {
        if (input.at(i) == ' ') {
            // 구분자를 연속으로 입력했는가
            if (i < input.length() - 2) {   // 추가한 space 는 연속 구분자 x
                if (input.at(i + 1) == ' ') {
                    // 연속 스페이스(구분자 연속 입력)
                    cout << "consecutive specifier entered. ";
                    custom_pause("Please enter again.");
                    return false;
                }
            }
            cnt++;
        }
    }

    if (cnt > 5) {
        cout << "Available until 5 schedule numbers. ";
        custom_pause("Please enter again. ");
        return false;
    }

    for (int i = 0; i < input.length(); i++) {
        if (input.at(i) != ' ')
            tmp_flusher += input.at(i);
        else {            
            if (tmp_flusher.length() > 2) { // 0 입력한 경우는 범위를 벗어난 숫자
                if (tmp_flusher.at(0) == '0') {
                    // 지원하지 않는 형식 (선행 0)
                    cout << "Invalid number format(ex. prefix 0) entered. ";
                    custom_pause("Please enter again.");
                    ret_val = false;
                    break;
                }
            }
            
            int tmp_value_atoi = atoi(tmp_flusher.c_str());
            if (tmp_value_atoi <= 20 && tmp_value_atoi > 0) {
                if (tmp_value_atoi > year[year_idx].getLength()) {
                    // 존재하지 않는 일정
                    cout << "Selected schedule does not exist.";
                    custom_pause("Please enter again.");
                    ret_val = false;
                    break;
                }
            } else {
                // 범위를 벗어난 숫자 입력
                cout << "Entered schedule number out of range of: 1 ~ 20. ";
                custom_pause("Please enter again.");
                ret_val = false;
                break;
            }
            tmp[array_idx_pointer++] = tmp_value_atoi;
            tmp_flusher = "";
        }
        ret_val = true;
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
