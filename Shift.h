#ifndef SHIFT_H
#define SHIFT_H
#include <list>
#include "Student.h"

class Shift
{
	string name;																	// Nome do Turno
	int max_elements;																// Número de vagas do Turno
	list<Student> elements;															// Elementos do turno

public:
	Shift(const string& name, const int& max_elements);
	bool add(Student& student);														// Adicionar um aluno ao Turno
	bool remove(const int& number);													// Remover um aluno do Turno
	size_t size();																	// Número de elementos do turno
	void readFromFile(const string& filename);
	void saveToFile(const string& filename);
	string find(int number);
};

#endif