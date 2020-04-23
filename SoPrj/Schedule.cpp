#include "Schedule.h"

Schedule::Schedule()
	: Schedule("noinfo", "noinfo")
{
}

Schedule::Schedule(string content, string keyword)
    :content(content), keyword(keyword)
{
}

string& Schedule::getContent(){
	return this->content;
}

string& Schedule::getKeyword(){
	return this->keyword;
}

void Schedule::setContent(string& s){
	this->content = s;	
}
void Schedule::setKeyword(string& s){
	this->keyword = s;
}