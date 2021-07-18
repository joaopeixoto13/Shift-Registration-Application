#pragma once
#include <iostream>

using namespace std;

class AbstractMenu
{
public:
	virtual void process() = 0;
	void method();
};

