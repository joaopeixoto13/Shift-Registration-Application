#ifndef HOMEMENU_H
#define HOMEMENU_H
#include "BaseMenu.h"

class HomeMenu : public BaseMenu
{
public:
	void print();
	void read_option();
	int process_option();
};

#endif