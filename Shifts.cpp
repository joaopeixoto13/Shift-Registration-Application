#include "Validator.h"
#include "Parsing.h"
#include <fstream>
#include "Context.h"
#define NOT_ALLOCATE -1
#define NOT_REMOVED  -2

void Shifts::setInfo()
{
	Context* context = Context::getInstance();
	shifts.clear();
	for (list<ShiftInfo>::iterator it = context->getShiftsInfo().shifts.begin(); it != context->getShiftsInfo().shifts.end(); it++)
	{
		Shift aux(it->name, it->max_elements);
		shifts.push_back(aux);
	}
}

int Shifts::add(Student& student, list <int> preferences)
{
	int counter = 1;
	list<Shift>::iterator it;

	remove(student._number());

	for (list<int>::iterator i = preferences.begin(); i != preferences.end(); i++)
	{
		int count = 0;
		for (it = shifts.begin(); it != shifts.end(); it++)										//posicionar o iterador no turno de preferencia
		{
			if (count == *i)
				break;
			count++;
		}
		if (it->add(student))																	// Se o aluno já foi colocado no respetivo turno
			return *i;																			// Retorna o Turno que ficou colocado
	}
	return NOT_ALLOCATE;
}

int Shifts::remove(const int& number)
{
	int counter = 1;
	for (list<Shift>::iterator it = shifts.begin(); it != shifts.end(); it++)
	{
		if (it->remove(number))
			return counter;																		// Retorna o Turno 
		counter++;
	}
	return NOT_REMOVED;
}

void Shifts::readFromFile(const string& filename)
{
	for (list<Shift>::iterator it = shifts.begin(); it != shifts.end(); it++)
		it->readFromFile(filename);
}

void Shifts::saveToFile(const string& filename)
{
	for (list<Shift>::iterator it = shifts.begin(); it != shifts.end(); it++)
		it->saveToFile(filename); 
}

size_t Shifts::size()
{
	size_t count = 0;
	for (list<Shift>::iterator it = shifts.begin(); it != shifts.end(); it++)
		count += it->size();
	return count;
}

string Shifts::find(int number)
{
	for (list<Shift>::iterator it = shifts.begin(); it != shifts.end(); it++)
	{
		string shiftName = it->find(number);
		if (shiftName != "")
			return shiftName;
	}
	return "";
}

void Shifts::clear()
{
	shifts.clear();
}
