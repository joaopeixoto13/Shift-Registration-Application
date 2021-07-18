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
	vector<feedBack> report;															// Feedback das Marcações

public:
	void readFromFile(const string& filename,bool externfile);							// Ler de um ficheiro (externo ou interno) as Marcações
	void readFromBody(istringstream& body);												// Ler de um ficheiro (externo ou interno) as Marcações
	bool validateFileLine(string& line, const char limiter);							// Validar linha de um ficheiro que contém marcações
	int add(Book& st , int& shift);														// Adicionar uma Marcação
	void remove(int number);
	void saveToFile(const string& filename);											// Guardar as marcações
	void ReportBook();																	// Feedback das Marcações
	void ReportBookHtml();																// Feedback das Marcações
	size_t size();																		// Número de Marcações
	string find(int number);
	void generateShifts(const string& fliename);
	void clear();
};

#endif