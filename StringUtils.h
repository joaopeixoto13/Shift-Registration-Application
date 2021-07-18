#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <string>
using namespace std;

class StringUtils
{
public:
	static void toUpper(string& x);	
	static void orderDate(string& x);			// aaaa/mm/dd hh:mm:ss
	static istringstream formatBody(istringstream& str);
};

#endif
