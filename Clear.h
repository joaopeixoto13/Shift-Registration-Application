#ifndef CLEAR_H
#define CLEAR_H
#include <fstream>

class Clear
{
public:
	static void removeLoadFiles();
	static bool empty(const std::string& folder);
};

#endif 