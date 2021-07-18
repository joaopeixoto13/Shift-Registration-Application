#include "BookingMenu.h"

void BookingMenu::print()
{
	system("pause");
	system("cls");
	cout << "Insert one file with students preferences   -> 1\n";
	cout << "Insert student shift preferences            -> 2\n";
	cout << "Remove one Student                          -> 3\n";
	cout << "Find Student                                -> 4\n";
	cout << "Booking Information                         -> 5\n";
	cout << "Exit                                        -> 6\n\n";
}

void BookingMenu::read_option()
{
	do {
		option = Console::readNumber("Insert your option: ");
	} while (option < 1 || option > 6);
}

int BookingMenu::process_option()
{
	Context* context = Context::getInstance();
	switch (option)
	{
	// ---------------------------------------------------------------------------------------------------------------------------------
	case(1):																	
	{
		string filename = Console::readString("Insert filename: ");
		try {
			context->getBooking().readFromFile(filename,true);																// Ler o ficheiro recebido e processar a informação
		}
		catch (invalid_argument& e) {
			cout << e.what() << endl;
			break;
		}
		catch (runtime_error& e) {
			cout << e.what() << endl;
			system("pause");																						// Guardar o relatório de eventuais anomalias
		}
		context->getBooking().ReportBook();
		break;
	}
	// ---------------------------------------------------------------------------------------------------------------------------------				
	case(2):																						
	{
		
		int number = Console::readNumber("Insert your number: ");
		string date = "";
		list<int> preferences;
		cout << endl << context->getShiftsInfo().info()<< endl << endl;
		cout << "To choose the preferences, please insert one value [1 - " << context->getShiftsInfo().size() << "] in this range" << endl;
		for (int i = 0; i < context->getShiftsInfo().size(); i++) {
			int preference;
			do {
				preference = Console::readNumber("Insert your " + to_string(i + 1) + "º preference: ");
			} while (preference < 1 || preference > context->getShiftsInfo().size());
			preferences.push_back(preference - 1);
		}
		int x;
		Book a(date,number, preferences);
		int y = context->getBooking().add(a,x);
		if (y >= 0)
			cout << "Student "  + to_string(number) + " not exist!\n";
		else if (y == -1)
			cout << "Student " + to_string(number) + " not placed!\n";
		else if (y == -2)
			cout << "Student " + to_string(number) + " was placed in shift " + to_string(x + 1)<<endl;
		else if (y == -3)
			cout << "Student " + to_string(number) + " was booked!\n";
		break;
	}
	// ---------------------------------------------------------------------------------------------------------------------------------
	case(3):
	{
		int number = Console::readNumber("Insert the number of student to remove: ");
		context->getBooking().remove(number);
		cout << "Student removed successful!" << endl;
		break;
	}
	// ---------------------------------------------------------------------------------------------------------------------------------
	case(4):
	{
		int number = Console::readNumber("Insert the number of student to find: ");
		cout << context->getBooking().find(number) << endl;
		break;
	}
	// ---------------------------------------------------------------------------------------------------------------------------------
	case(5):
	{
		system("cls");
		cout << "-------------BOOKING INFORMATION-------------------" << endl << endl;
		cout << "Total booked students: " << context->getBooking().size() << endl;
		cout << "Students already placed (with priority) : " << context->getShifts().size() << endl << endl;
		cout << "Total number of shifts places: " << context->getShiftsInfo().totalPlaces() << endl;
		cout << "Number of places available (without appointments): " << context->getShiftsInfo().totalPlaces() - context->getShifts().size() << endl;
		break;
	}
	//----------------------------------------------------------------------------------------------------------------------------------
	case(6):
	{
		return HOME_MENU;
		break;
	}
	// ---------------------------------------------------------------------------------------------------------------------------------
	}
	context->getBooking().saveToFile("ficheiros\\my\\Booking.csv");
	context->getShifts().saveToFile("ficheiros\\my\\placed\\");
	return BOOKING_MENU;
}