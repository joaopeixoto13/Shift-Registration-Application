#ifndef SHIFTS_H
#define SHIFTS_H
#include "Shift.h"

class Shifts
{
	list<Shift> shifts;

public:
	void setInfo();
	int add(Student& student, list <int> preferences);						// Adicionar um Aluno a um turno
	int remove(const int& number);											// Remover um Aluno de um turno
	void readFromFile(const string& filename);								
	void saveToFile(const string& filename);
	size_t size();															// Número de Alunos nos Turnos
	string find(int number);
	void clear();
};


#endif
