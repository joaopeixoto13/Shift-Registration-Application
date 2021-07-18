#ifndef BOOK_H
#define BOOK_H
#include <string>
#include <list>
#include <ostream>

using namespace std;
class Book
{
	string date;																		// Data de inscri��o
	int number;																			// N�mero do Aluno
	list<int> preferences;																// Lista de prefer�ncias
public:
	Book(string& date, int number, list<int>& preferences);
	void formatDate();
	friend class Booking;
	friend ostream& operator<<(ostream& os, const Book& book);
};

#endif
