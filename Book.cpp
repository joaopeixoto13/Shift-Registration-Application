#include "Book.h"
#include "StringUtils.h"


Book::Book(string& date, int number, list<int>& preferences)
	:date(date),number(number),preferences(preferences)
{}

void Book::formatDate()
{
	StringUtils::orderDate(date);
}

ostream& operator<<(ostream& os, const Book& book)
{
	os << book.date << ";x;" << book.number << ";";
	for (int j : book.preferences)
		os << j << ";";
	return os;
}