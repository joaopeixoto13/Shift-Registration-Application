#ifndef BOOK_H
#define BOOK_H
#include <string>
#include <list>
#include <ostream>

using namespace std;
class Book
{
	string date;																		// Data de inscrição
	int number;																			// Número do Aluno
	list<int> preferences;																// Lista de preferências
public:
	Book(string& date, int number, list<int>& preferences);
	void formatDate();
	friend class Booking;
	friend ostream& operator<<(ostream& os, const Book& book);
};

#endif
