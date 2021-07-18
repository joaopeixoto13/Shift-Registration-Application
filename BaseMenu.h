#ifndef BASEMENU_H
#define BASEMENU_H
#include <iostream>
#include "Parsing.h"
#include "Context.h"
#include "Console.h"
#define EXIT			0 
#define CONFIG_MENU		1 
#define BOOKING_MENU	2
#define GENERATE		3
#define HOME_MENU		4 

using namespace std;

class BaseMenu
{
public:
	int option = 0;
	virtual void print() = 0;
	virtual void read_option() = 0;
	virtual int process_option() = 0;
};

#endif