#ifndef CONFIGMENU_H
#define CONFIGMENU_H
#include "BaseMenu.h"

class ConfigMenu : public BaseMenu
{
public:
	void print();
	void read_option();
	int process_option();
};

#endif