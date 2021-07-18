#ifndef BOOKING_H
#define BOOKING_H
#include "Book.h"
#define NOT_EXIST	0
#define NOT_PLACED -1
#define EE_PLACED  -2
#define BOOKED     -3

class Booking
{	
	list<Book> booking;																	// Lista de Book's
	vector<feedBack> report;															// Feedback das Marca��es

public:
	void readFromFile(const string& filename,bool externfile);							// Ler de um ficheiro (externo ou interno) as Marca��es
	void readFromBody(istringstream& body);												// Ler de um ficheiro (externo ou interno) as Marca��es
	bool validateFileLine(string& line, const char limiter);							// Validar linha de um ficheiro que cont�m marca��es
	int add(Book& st , int& shift);														// Adicionar uma Marca��o
	void remove(int number);
	void saveToFile(const string& filename);											// Guardar as marca��es
	void ReportBook();																	// Feedback das Marca��es
	void ReportBookHtml();																// Feedback das Marca��es
	size_t size();																		// N�mero de Marca��es
	string find(int number);
	void generateShifts(const string& fliename);
	void clear();
};

#endif