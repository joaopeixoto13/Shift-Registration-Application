#include "HomeMenu.h"

void HomeMenu::print()
{
	system("pause");
	system("cls");
	cout << "Shifts and Students  -> 1" << endl;
	cout << "Students SignUp      -> 2" << endl;
	cout << "Generate Shifts      -> 3" << endl;
	cout << "Exit                 -> 4" << endl;
}

void HomeMenu::read_option()
{
	do {
		option = Console::readNumber("Insert your option: ");
	} while (option < 1 || option > 4);
}

int HomeMenu::process_option()
{
	if (option == 4)
		return EXIT;
	return option;
}