#pragma once
#include "AbstractMenu.h"
#include <string>

using namespace std;

class Factory
{
public:
	static AbstractMenu* create(string uri);
};

