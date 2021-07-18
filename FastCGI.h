#pragma once
#include "fcgio.h"
#include <string>
#include <sstream>

using namespace std;

class FastCGI
{
public:
	static long readBody(FCGX_Request& request, istringstream& body);
};

