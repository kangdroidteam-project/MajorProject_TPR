#include "Manager.h"
#include <Windows.h>

Manager::Manager() {
	// Load saved data to array
	callLoad();
}

bool Manager::hasNext(string& input) {			
	for (size_t i = 1; i < input.length(); i++) {
		if (input.at(i) != 32) {
			if (input.at(i) > 0) {
				return true;
			}
		}
	}
	return false;
}

void Manager::showDate(time_t rawtime, string scope_info) {
	unsigned long long index_num = 1;//일정 번호
	struct tm* dt;
	char buffer[50];
	//time_t rawtime = 0;//std::time(0);
	dt = localtime(&rawtime);
	if (dt->tm_wday == 0) {
		strftime(buffer, sizeof(buffer), "\033[0;31m%Y.%m.%d (%a)\033[0m", dt);
	} else {
		strftime(buffer, sizeof(buffer), "%Y.%m.%d (%a)", dt);
	}
	
	//std::cout << std::string(buffer) << std::endl;

	cout << string(buffer) << " " << endl;

	// Search needed --> TODO
	for (unsigned long long i = 0; i < date.size(); i++) {
		if (date.at(i).isDayExists(rawtime)) {
			// There is something!
			if (scope_info == "day") {
				cout << index_num << ". " << date.at(i).getContent();
				index_num++;
			} else if (scope_info == "week" || scope_info == "month") {
				cout << " / " << date.at(i).getKeyword();
			}
			cout << endl;
		}
	}
}

void Manager::showSchedule() {
	int count = 0;
	string scope_whatever;
	string y = "";
	string d = "";
	string m = "";
	int d2, m2, y2;

	while (true) {
		bool flag = true;
		count++;
		y = "";
		d = "";
		m = "";
		scope_whatever = "";
		if (count > 5) {
			cout << "5 invalid inputs entered. ";
			custom_pause("Press any key to go back to the main menu.");
			return;
		} //
		cout << "\nInput Format\n";
		cout << "YYYYMMDD + (Space) + Scope Information (one of, month / week / "
			"day)\n";
		cout << "------------------------------------------------------------------"
			"--------------------------------\n";
		cout << "YYYYMMDD: Date you are going to check(8-digits, ex: 20200401)\n";
		cout << "Year available from 1970~2037\n";
		cout << "month: Whole month of entered date\n";
		cout << "week: Whole week of entered date\n";
		cout << "day: Detailed schedule information of entered date\n"
			<< endl
			<< endl;
		cout << "Enter Date and Scope Information>";
		string scope;
		getline(cin, scope);

		string day_tmp_t = "";
		int ctr = 0;

		for (size_t i = 0; i < scope.length(); i++) {
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
		for (size_t i = 0; i < scope.length(); i++) {
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
				if ((i + 1) < scope.length()) {
					// no specifier enetered.
					scope_whatever = scope.substr((i+1), scope.length());
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
			for (size_t i = 0; i < day_tmp_t.length(); i++) {
				if (i < 4) {
					y += day_tmp_t.at(i);
				} else if (i < 6) {
					m += day_tmp_t.at(i);
				} else {
					d += day_tmp_t.at(i);
				}
			}
			try {
				y2 = stoi(y);
				m2 = stoi(m);
				d2 = stoi(d);
			} catch (const exception& expn) {
				return;
			}

			//check true date
			if (!timecal.isCorrectDay(y2, m2, d2)) {
				cout << y2 << m2 << d2 << endl;
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
			}
		}

		if (flag) break;
	}

	//출력
	if (scope_whatever == "month") {
		time_t timestamp_start = timecal.dateToStamp(y2, m2, 1); // first day of that month
		time_t timestamp_end = timecal.dateToStamp(y2, m2 + 1, 1); // last day of that month
		while (timestamp_start < timestamp_end) {
			showDate(timestamp_start, scope_whatever);
			timestamp_start += DAY_SEC; // DAY_SEC defined on TimeCalculator.h
			timestamp_start = timecal.roundOffTimeStamp(timestamp_start); // Round off timestamp
		}
	} else if (scope_whatever == "week") {
		time_t minimum_range = timecal.calculateWeek(y2, m2, d2, false);
		time_t maximum_range = timecal.calculateWeek(y2, m2, d2, true);
		while (minimum_range < maximum_range) {
			showDate(minimum_range, scope_whatever);
			minimum_range += DAY_SEC;
		}
	} else if (scope_whatever == "day") {
		time_t timestmp_raw = timecal.dateToStamp(y2, m2, d2); // First date would be ABSOLUTELY Rounded off
		showDate(timestmp_raw, scope_whatever);
	} else {
		// Something went wrong --> Error, Specifier isnt one of: month, week, day
		cout << "Something went wrong --> Error, Specifier isn't one of : month, week, day. Current entered one: " << scope_whatever << endl;
	}
}

void Manager::addSchedule() {

	int y2, m2, d2, wd;
	time_t today = get_date();	// 날짜 입력
	if (today == -1) return; // 날짜 입력 오류

	timecal.calculateDateFromStamp(y2, m2, d2, wd, today);

	int count = 0;
	bool flag;
	string key = "", sch = "";

	while (true) { // 일정 입력
		sch = "";
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
			for (size_t i = 0; i < sch.length(); i++)
				if (!((sch.at(i) >= 'a' && sch.at(i) <= 'z') || (sch.at(i) >= 'A' && sch.at(i) <= 'Z') || (sch.at(i) >= '0' && sch.at(i) <= '9') || (sch.at(i) == ' ' || sch.at(i) == '.'))) {
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
		key = "";

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
				if (!((key.at(i) >= 'a' && key.at(i) <= 'z') || (key.at(i) >= 'A' && key.at(i) <= 'Z') || (key.at(i) >= '0' && key.at(i) <= '9') || (key.at(i) == ' '))) {
					cout << "Unexpected Characters entered. ";
					custom_pause("Please enter again.");
					flag = false;
					break;
				}
			}
		}

		if (flag) break;
	} //여기까지 키워드


	//여기서부터 입력수정 (2차 기획서)
	//1. 반복일정단위 입력 추가 (1~4)
	//2. 각각의 경우(년/월/일 단위 입력) 추가
	//3. 반복 종료 날짜 입력 추가

	count = 0;
	string menu;
	while (true) {
		count++;
		flag = true;
		if (count > 5) {
			cout << "5 invalid inputs entered. ";
			custom_pause("Press any key to go back to the main menu.");
			return;
		}
		cout << "1. Every n Year    2. Every n Month   3. Every n Day   4. No Repeat\n>";

		// 오류 처리
		getline(cin, menu);

		if (menu.length() < 1) {
			cout << "Only numbers are allowed. Please enter again." << endl; continue;
		} else if (menu.at(0) == '0' && hasNext(menu)) {
			// Prefix 0 detected.
			cout << "Invalid number format(ex: prefix 0) entered. Please enter again." << endl;
			continue;
		} else if (menu.at(0) < '0' || menu.at(0) > '9') {
			// Only number are allowed
			cout << "Only numbers are allowed. Please enter again." << endl;
			continue;
		} else if (menu.at(0) < '1' || menu.at(0) > '4' || menu.length() > 1) {
			// Number out of range
			cout << "Argument out of range. Please enter again." << endl;
			continue;
		} else if (menu.at(0) == '4') {
			//반복 일정 적용x
			//time_t timestamp = timecal.dateToStamp(y2, m2, d2);

			Schedule schedule(sch, key, generateSID());
			schedule.add(today);
			//schedule.setKeyword(key);
			//schedule.setContent(sch);

			date.push_back(schedule);

			cout << "Schedule sucessfully added. " << endl;
			custom_pause("Press any key to return to the main menu.\nPress any key to continue. . .");


			return;

		} else {  // 1번 2번 3번

			int repeat = repeatSchedule(timecal.dateToStamp(y2, m2, d2), menu.at(0) - '0');
			if (repeat == -1) return;
			time_t fin = input_finishDay();
			if (fin == -1) return;

			Schedule schedule(sch, key, generateSID());
			//schedule.setKeyword(key);
			//schedule.setContent(sch);
			schedule.setRepeat(timecal.dateToStamp(y2, m2, d2), fin, menu.at(0) - '0', repeat);
			date.push_back(schedule);
			break;
		}
	}

	cout << "Schedule sucessfully added. " << endl;
	custom_pause("Press any key to return to the main menu.\nPress any key to continue. . .");
}

void Manager::editSchedule() {
	int y2, m2, d2, wd; // Year, Month, Day in integer type
	time_t today = get_date();	// 날짜 입력
	if (today == -1) return; // 날짜 입력 오류

	timecal.calculateDateFromStamp(y2, m2, d2, wd, today);
	unsigned long long size = 0;

	//일정 없는지 확인
	for (unsigned long long i = 0; i < date.size(); i++) {
		if (date.at(i).isDayExists(timecal.dateToStamp(y2, m2, d2))) {
			size++;
		}
	}
	if (size == 0) {
		cout << "No schedule available on current date. " << endl;
		custom_pause("Press any key to go back to the main menu.");
		return;
	}

	
	Date date_tmp(today, &date);

	int count = 0;
	bool flag;
	// unsigned long long date_idx = 0; //date 인덱스 번호
	unsigned long long num; // index of schedule

	while (true) {
		string index_num;
		while (true) {
			count++;

			if (count > 5) {
				cout << "5 invalid inputs entered. ";
				custom_pause("Press any key to go back to the main menu.");
				return;
			}

			//show
			date_tmp.print_date();

			cout << "Please enter index number of desired schedule.>";
			getline(cin, index_num);

			if (index_num.length() == 0) {
				cout << "Invalid number format(ex: prefix 0) entered. " << endl;
				custom_pause("Please enter again.");
				continue;
			}
			// if it isn't number
			bool number_checker = true;
			bool isPrefixAvail = false;
			for (size_t i = 0; i < index_num.length(); i++) {
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
			try {
				num = stoi(index_num);
			} catch (const exception& expn) {
				cout << "Invalid schedule entered. " << endl;
				custom_pause("Please enter again");
				continue;
			}
			if (num < 1 || num > date_tmp.GetLengthSid()) {
				cout << "Entered string out of range of: 1 ~ " << date_tmp.GetLengthSid() << ". " << endl;
				custom_pause("Please enter again");
				continue;
			}

			// if schedule does not exists
			if (num > date_tmp.GetLengthSid()) {
				cout << "Invalid schedule entered. " << endl;
				custom_pause("Please enter again");
				continue;
			} else {
				break; // All checking finished.
			}
		}

		count = 0;
		// At this state, default input is over. Now, input schedule information
		string sch;
		while (true) {
			count++;

			if (count > 5) {
				cout << "5 invalid inputs entered. ";
				custom_pause("Press any key to go back to the main menu.");
				return;
			}
			cout << "Enter edited schedule information(English / Number / Special Character unavailable except '.' and ' ', min 1 character, max 50 characters) >";
			getline(cin, sch);

			// Length exceeds 50
			if (sch.length() > 50 || sch.length() < 1) {
				cout << "Argument out of range. Please enter again. " << endl;
				custom_pause("Please enter again");
				continue;
			}

			// Unexpected Character
			bool tmp_flag = true;
			for (size_t i = 0; i < sch.length(); i++) {
				if (!((sch.at(i) >= 'a' && sch.at(i) <= 'z') || (sch.at(i) >= 'A' && sch.at(i) <= 'Z') || (sch.at(i) >= '0' && sch.at(i) <= '9') || (sch.at(i) == ' ' || sch.at(i) == '.'))) {
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

		count = 0;
		string key;
		while (true) {
			count++;
			if (count > 5) {
				cout << "5 invalid inputs entered. ";
				custom_pause("Press any key to go back to the main menu.");
				return;
			}

			cout << "Enter edited keyword information(English / Number / Special Character unavailable except ' ' min 1 character, max 20 characters) >";
			getline(cin, key);

			// oor
			if (key.length() > 20 || key.length() < 1) {
				cout << "Argument out of range. Please enter again. " << endl;
				custom_pause("Please enter again");
				continue;
			}

			// unexpected char
			bool tmp_flag = true;
			for (size_t i = 0; i < key.length(); i++) {
				if (!((key.at(i) >= 'a' && key.at(i) <= 'z') || (key.at(i) >= 'A' && key.at(i) <= 'Z') || (key.at(i) >= '0' && key.at(i) <= '9') || (key.at(i) == ' '))) {
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

		//일정 추가랑 똑같이 수정(2차기획서)
		//1. 반복일정단위 입력 추가 (1~4)
		//2. 각각의 경우(년/월/일 단위 입력) 추가
		//3. 반복 종료 날짜 입력 추가


		count = 0;
		string menu;



		while (true) {
			count++;

			flag = true;

			if (count > 5) {
				cout << "5 invalid inputs entered. ";
				custom_pause("Press any key to go back to the main menu.");
				return;
			}
			cout << "1. Every n Year    2. Every n Month   3. Every n Day   4. No Repeat\n>";

			// 오류 처리
			getline(cin, menu);

			if (menu.length() < 1) {
				cout << "Only numbers are allowed. Please enter again." << endl; continue;
			} else if (menu.at(0) == '0' && hasNext(menu)) {
				// Prefix 0 detected.
				cout << "Invalid number format(ex: prefix 0) entered. Please enter again." << endl;
				continue;
			} else if (menu.at(0) < '0' || menu.at(0) > '9') {
				// Only number are allowed
				cout << "Only numbers are allowed. Please enter again." << endl;
				continue;
			} else if (menu.at(0) < '1' || menu.at(0) > '4' || menu.length() > 1) {
				// Number out of range
				cout << "Argument out of range. Please enter again." << endl;
				continue;
			} else if (menu.at(0) == '4') {
				//반복 일정 적용x
				time_t timestamp = timecal.dateToStamp(y2, m2, d2);

				Schedule schedule(sch, key, generateSID());
				schedule.add(timestamp);
				date_tmp.editSchedule(num, schedule);

				//cout << "Schedule sucessfully added. " << endl;

			} else {  // 1번 2번 3번

				int repeat = repeatSchedule(timecal.dateToStamp(y2, m2, d2), menu.at(0) - '0');
				if (repeat == -1) return;

				time_t fin = input_finishDay();
				if (fin == -1) return;

				Schedule schedule(sch, key, generateSID());
				//schedule.setKeyword(key);
				//schedule.setContent(sch);
				schedule.setRepeat(timecal.dateToStamp(y2, m2, d2), fin, menu.at(0) - '0', repeat);
				date_tmp.editSchedule(num, schedule);
				//date.push_back(schedule);
				break;
			}
		}
		//once again
		string roundgo;
		bool goornot = true;
		bool lineCheck = true;
		count = 0;
		while (true) {

			count++;

			if (count > 5) {
				cout << "5 invalid inputs entered. ";
				custom_pause("Press any key to go back to the main menu.");
				return;
			}

			cout << "Do you want to edit another schedule? (Y, y, / N, n) >";
			lineCheck = true;
			getline(cin, roundgo);

			if (roundgo.length() != 1) {
				cout << "Only (Y,y/N,n) character is allowed. Please enter again." << endl;
				custom_pause("Please enter again.");
				lineCheck = false;
				continue;
			}
			if (lineCheck) {
				if (roundgo.at(0) == 'Y' || roundgo.at(0) == 'y') {
					goornot = true;
					break;
				} else if (roundgo.at(0) == 'N' || roundgo.at(0) == 'n') {
					goornot = false;
					cout << "Schedule successfully edited.\nPress any key to return to the main menu." << endl;
					custom_pause("Press any key to continue.");
					break;
				} else {
					cout << "Only (Y,y/N,n) character is allowed. Please enter again." << endl;
					continue;
				}
			}
		}
		if (goornot) {
			continue;
		} else {
			return;
		}
	}
}


void Manager::deleteSchedule() {
	int y2, m2, d2, wd;
	time_t today = get_date();	// 날짜 입력
	timecal.calculateDateFromStamp(y2, m2, d2, wd, today);
	if (y2 == -1) return; // 날짜 입력 오류

	//일정 있는지 확인
	unsigned long long size = 0;
	for (unsigned long long i = 0; i < date.size(); i++) {
		if (date.at(i).isDayExists(timecal.dateToStamp(y2, m2, d2))) {
			size++;
		}
	}
	if (size == 0) {
		cout << "No schedule available on current date. " << endl;
		custom_pause("Press any key to go back to the main menu.");
		return;
	}

	Date date_tmp(today, &date);
	date_tmp.print_date();

	int count = 0;
	bool flag = true;

	string sdnum;  //삭제할 일정 번호
	unsigned long long* tmp_array_sortable = nullptr;
	vector<unsigned long long> tmp_vararr;
	unsigned long long idx_pointer = 0;

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

		tmp_array_sortable = new unsigned long long[sdnum.length()];
		idx_pointer = 0;

		bool isParsed = parseString(tmp_array_sortable, idx_pointer, sdnum, date_tmp.GetLengthSid());
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

	//여기 변경
	date_tmp.deleteSchedule(tmp_vararr);

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
	FileIO fio;
	fio.save(this->date);
}

void Manager::callLoad() {
	FileIO fio;
	fio.load(this->date);
}

bool Manager::parseString(unsigned long long* tmp, unsigned long long& array_idx_pointer, string& input, unsigned long long year_idx) {
	string tmp_flusher = "";
	array_idx_pointer = 0;
	bool ret_val = false;

	if (input.length() < 1) { // 엔터 입력
		// less than 1
		cout << "Entered character rather than number and space.";
		custom_pause("Please enter again.");
		return false;
	} else if (input.length() < 2 && input.at(0) == ' ') {
		//스페이스 하나만 입력했을 경우(빈문자)
		cout << "Invalid number format(ex. prefix 0) entered.";
		custom_pause("Please enter again.");
		return false;
	}
	// 숫자와 띄어쓰기가 아닌 문자가 있는가
	// 이걸 input 에 대해 먼저 수행해야 우선순위 1
	for (size_t i = 0; i < input.length(); i++) {
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

	// 구분자 연속 or 5개 초과의 번호를 입력했는가 
	int count = 0; // 몇개 입력받았는지 (단순히 구분자로 나눔)
	for (size_t i = 0; i < input.length(); i++) {
		if (input.at(i) == ' ') {
			// 구분자를 연속으로 입력했는가
			if (i < input.length() - 2) {   // 추가한 space 는 연속 구분자 x
				if (input.at((i + 1)) == ' ') {
					// 연속 스페이스(구분자 연속 입력)
					cout << "consecutive specifier entered. ";
					custom_pause("Please enter again.");
					return false;
				}
			}
			count++;
		}
	}

	if (count > 5) {
		cout << "Available until 5 schedule numbers. ";
		custom_pause("Please enter again. ");
		return false;
	}

	for (size_t i = 0; i < input.length(); i++) {
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

			unsigned long long tmp_value_atoi;
			try {
				tmp_value_atoi = stoi(tmp_flusher);
			} catch (const exception& expn) {
				cout << "Invalid number format(ex. prefix 0) entered. ";
				custom_pause("Please enter again.");
				ret_val = false;
				break;
			}
			if (tmp_value_atoi > 0) {
				if (tmp_value_atoi > year_idx) {
					// 존재하지 않는 일정
					cout << "Selected schedule does not exist.";
					custom_pause("Please enter again.");
					ret_val = false;
					break;
				}
			} else {
				// 범위를 벗어난 숫자 입력
				cout << "Entered schedule number out of range of : 1 ~ " << year_idx << ". ";
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

void Manager::removeSame(unsigned long long* arr, unsigned long long& idx, vector<unsigned long long>& tmp) {
	for (unsigned long long i = 0; i < idx; i++) {
		if (isHas(tmp, arr[i])) {
			// Not exists.
			tmp.push_back(arr[i]);
		}
	}
}

bool Manager::isHas(vector<unsigned long long>& tmpVector, unsigned long long target) {
	if (tmpVector.size() == 0) {
		return true;
	} else {
		for (unsigned long long i = 0; i < tmpVector.size(); i++) {
			if (target == tmpVector.at(i)) {
				// Same thing exists.
				return false;
			}
		}
	}
	return true;
}

int Manager::repeatSchedule(time_t today, int menu) {
	string repeat;
	int count = 0;
	int c, r;
	struct tm* tmp_struct = localtime(&today);

	if (menu == 1) c = 2037 - tmp_struct->tm_year - 1900; //year 계산
	else if (menu == 2) c = (2037 - tmp_struct->tm_year - 1900) * 12 + 12 - tmp_struct->tm_mon;  //month 계산
	else if (menu == 3) c = timecal.dateToStamp(2037, 12, 31) - today;  //day 계산
	else return -1;

	//일정 반복 범위 입력
	while (true) {
		count++;
		if (count > 5) {
			cout << "5 invalid inputs entered. ";
			custom_pause("Press any key to go back to the main menu.");
			return -1;
		}
		bool flag = true;

		if(menu==1) cout << "How many years you want to repeat this schedule?(1~";
		else if(menu==2) cout << "How many months you want to repeat this schedule?(1~";
		else if(menu==3) cout << "How many days you want to repeat this schedule?(1~";
		
		cout << c << " available)";
		getline(cin, repeat);

		if (repeat.length() == 0) { // When nothing entered on string.
			cout << "Only numbers are allowed. ";
			custom_pause("Please enter again.");
			continue;
		}

		for (size_t i = 0; i < repeat.length(); i++) {
			if (repeat.at(i) < '0' || repeat.at(i) > '9') {
				cout << "Only numbers are allowed. ";
				custom_pause("Please enter again.");
				flag = false;
				break;
			}
		}
		if (!flag) continue;

		try {
			r = stoi(repeat);
		} catch (const exception& expn) {
			cout << "Argument out of range. ";
			custom_pause("Please enter again.");
			continue;
		}

		if (r < 0 || r >c) {
			cout << "Argument out of range. ";
			custom_pause("Please enter again.");
			continue;
		}
		if (repeat.length() > 1) {
			if (repeat.at(0) == '0') {
				cout << "Invalid number format entered. ";
				custom_pause("Please enter again.");
				flag = false;
				continue;
			}
		}

		if (flag)
			return r;
	}

}

time_t Manager::input_finishDay() {
	int count = 0;
	string scope;
	string y = "", d = "", m = "";
	int d2, m2, y2;
	time_t fin;
	bool flag;

	while (true) {
		y = "", d = "", m = "";
		count++;

		if (count > 5) {
			cout << "5 invalid inputs entered. ";
			custom_pause("Press any key to go back to the main menu.");
			return -1;
		}

		flag = true;
		cout << "Please enter the date this schedule ends(8 digits, ex.20200401)\n";
		cout << "if you don’t want to set  the date then just press only enter key \n";
		cout << "it will repeat until 2037.12.31 \n";
		cout << ">";


		getline(cin, scope);

		if (scope.length() < 1) {
			fin = timecal.dateToStamp(2037, 12, 31);
			return fin;
		}

		for (size_t i = 0; i < scope.length(); i++) {
			if (i < 4) {
				y += scope.at(i);
			} else if (i < 6) {
				m += scope.at(i);
			} else if (i < 8) {
				d += scope.at(i);
			}
		}

		if (flag) {
			for (size_t i = 0; i < scope.length(); i++)
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

		try {
			d2 = stoi(d);
			m2 = stoi(m);
			y2 = stoi(y);
		}
		catch (const exception & expn) {
			cout << "Invalid date entered. ";
			custom_pause("Please enter again.");
			flag = false;
			continue;
		}

		//check true date
		if (flag) {
			if (!timecal.isCorrectDay(y2, m2, d2)) {
				cout << "Invalid date entered. ";
				custom_pause("Please enter again.");
				flag = false;
				continue;
			}
		}

		if (flag) {
			fin = timecal.dateToStamp(y2, m2, d2);
			break;
		}

	}
	return fin;
}

time_t Manager::get_date() {
	int count = 0;
	string scope;
	bool flag = true;

	string y = "", d = "", m = "";
	int d2, m2, y2;

	while (true) {
		count++;
		if (count > 5) {
			cout << "5 invalid inputs entered. ";
			custom_pause("Press any key to go back to the main menu.");
			return -1;
		}

		flag = true;
		cout << "Please enter date of desired schedule.(8digits, ex.20200401)>";
		getline(cin, scope);
		for (size_t i = 0; i < scope.length(); i++)
			if (scope.at(i) < '0' || scope.at(i) > '9') {
				cout << "Only numbers are allowed on first argument. ";
				custom_pause("Please enter again.");
				flag = false;
				break;
			}
		if (!flag) continue;


		if (scope.length() != 8) {
			cout << "Only 8 digit date-form are allowed. ";
			custom_pause("Please enter again.");
			continue;
		}

		y = "", d = "", m = "";

		for (size_t i = 0; i < scope.length(); i++) {
			if (i < 4) {
				y += scope.at(i);
			} else if (i < 6) {
				m += scope.at(i);
			} else if (i < 8) {
				d += scope.at(i);
			}
		}

		//check true date
		try {
			d2 = stoi(d);
			m2 = stoi(m);
			y2 = stoi(y);
		} catch (const exception& expn) {
			cout << "Invalid date entered. ";
			custom_pause("Please enter again.");
			continue;
		}

		if (!timecal.isCorrectDay(y2, m2, d2)) {
			cout << "Invalid date entered. ";
			custom_pause("Please enter again.");
			continue;
		}

		break;

	}

	return timecal.dateToStamp(y2, m2, d2);
}

unsigned long long Manager::generateSID() {
	unsigned long long sid_num; // Random number
	while (true) {
		sid_num = rand();
		if (!hasSID(sid_num)) {
			break;
		}
	}
	return sid_num;
}

bool Manager::hasSID(unsigned long long sid_checker) {
	if (std::find(sid_container.begin(), sid_container.end(), sid_checker) != sid_container.end()) {
		// has
		return true;
	} else {
		return false;
	}
}