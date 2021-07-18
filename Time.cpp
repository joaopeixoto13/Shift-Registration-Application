#include "Time.h"

string Time::timeNow()
{
	time_t t = time(0);
	tm* now = localtime(&t);
	string aux =  to_string(now->tm_year + 1900) + "/" + to_string(now->tm_mon + 1) + 
				"/" + to_string(now->tm_mday) + " " + to_string(now->tm_hour) +
				":" + to_string(now->tm_min) + ":" + to_string(now->tm_sec);
	return aux;
}
