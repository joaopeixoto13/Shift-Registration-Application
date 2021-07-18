#include "Shift.h"
#include <sstream>
#include <fstream>

Shift::Shift(const string& name, const int& max_elements)
	: name(name) , max_elements(max_elements)
{ }

bool Shift::add(Student& student)
{
	remove(student._number());

	if (elements.size() == max_elements)												// se turno estiver cheio
		return false;
	if (!elements.size())																// se o turno estiver vazio
	{
		elements.push_back(student);
		return true;
	}
	for (list<Student>::iterator it = elements.begin(); it != elements.end(); it++)
	{
		if (student._number() <= it->_number())											//Caso o numero do aluno for inferior ao numero da posi��o
		{
			elements.insert(it, student);												//Insere o aluno na posi��o
			return true;
		}
	}
	elements.push_back(student);														
	return true;
}

bool Shift::remove(const int& number)
{
	for (list<Student>::iterator it = elements.begin(); it != elements.end(); it++)
	{
		if (number == it->_number())
		{
			elements.erase(it);				
			return true;
		}
	}
	return false;
}

size_t Shift::size()
{
	return elements.size();
}

void Shift::readFromFile(const string& filename)
{
	ifstream fin(filename + name + ".csv");
	if (!fin.is_open())
		throw runtime_error("Error: Cannot open " + name + " file!");

	string line, token, name, ee;
	int number = 0;
	while (getline(fin, line))
	{
		stringstream ss(line);
		int count = 0;
		while (getline(ss, token, ';'))
		{
			if (count == 0)
				number = stoi(token);
			else if (count == 1)
				name = token;
			else if (count == 2)
				ee = token;
			count++;
		}
		Student aux(number, name, Student::statusInt(ee));
		elements.push_back(aux);
	}
	fin.close();
}

void Shift::saveToFile(const string& filename)
{
	ofstream fou(filename + name + ".csv");
	if (!fou.is_open())
		throw runtime_error("Error: Cannot create " + name + " file!");
	for (list <Student>::iterator it = elements.begin(); it != elements.end(); it++)
		fou << *it << ";" << endl;
	fou.close();
}

string Shift::find(int number)
{
	for (list<Student>::iterator it = elements.begin(); it != elements.end(); it++)
	{
		if (number == it->_number())
			return this->name;
	}
	return "";
}