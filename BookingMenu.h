#ifndef BOOKINGMENU_H
#define BOOKINGMENU_H
#include "BaseMenu.h"

class BookingMenu : public BaseMenu
{
public:
	void print();
	void read_option();
	int process_option();
};

#endif