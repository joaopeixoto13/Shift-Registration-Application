#include "Console.h"
#include <iostream>
#include "Validator.h"
int Console::readNumber(const string& text)
{
	int x;
	do
	{
		if (!cin)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		cout << text;
		cin >> x;
	} while (!cin || x <= 0);
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return x;
}

string Console::readString(const string& text)
{
	string return_string;
	cout << text;
	getline(cin >> std::ws, return_string);
	return return_string;
}

string Console::readName(const string& text)
{
	string return_string;
	do
	{
		cout << text;
		getline(cin >> std::ws, return_string);
	} while (!Validator::validateName(return_string));
	return return_string;
    return string();
}
