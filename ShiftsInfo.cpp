#include "ShiftsInfo.h"
#include <fstream>
#include "Parsing.h"
#include "Validator.h"

void ShiftsInfo::readFromFile(const string& filename)
{
	string line, token;
	vector<string> aux;
	int i = 0;
	ifstream fin(filename);
	if (!fin.is_open())                                                                                                 // se deu erro a abrir o ficheiro
		throw invalid_argument("Error: Cannot open the " + filename + " file");

	while (getline(fin, line))
	{
		if (!validateFileLine(line))																					// Validação da linha do ficheiro
		{
			fin.close();
			throw invalid_argument("Error: Invalid argument in " + filename + " file!");
		}
	}
	fin.clear();
	fin.seekg(0);
	while (getline(fin, line))
	{
		i++;
		Parsing::getParameters(line, ';', aux);
		if (aux[0] == "")
			aux[0] = "PL" + to_string(i);                                                                                 // Default Name
		shifts.push_back({ aux[0],stoi(aux[1]) });
	}

	fin.close();

	int j = 1;
	for (list<ShiftInfo>::iterator it = shifts.begin(); it != shifts.end(); it++, j++)									// Verificar existência de Turnos com o mesmo nome
	{
		for (list<ShiftInfo>::iterator it2 = next(shifts.begin(), j); it2 != shifts.end(); it2++)
		{
			if (it->name == it2->name) 
			{
				shifts.clear();
				throw invalid_argument("Error: Shifts with same name!");
			}
				
		}
	}
}

void ShiftsInfo::readFromBody(istringstream& body)
{
	istringstream validatebody(body.str());
	string line, token;
	vector<string> aux;
	int i = 0;
	getline(body, line);
	getline(body, line);
	getline(body, line);
	getline(body, line);

	while (getline(body, line) && line.size() > 1 && line[0] != '-')
	{
		if (!validateFileLine(line))																					// Validação da linha do ficheiro
			throw invalid_argument("Error: Invalid argument in file!");
	}

	getline(validatebody, line);
	getline(validatebody, line);
	getline(validatebody, line);
	getline(validatebody, line);

	while (getline(validatebody, line) && line.size() > 1 && line[0] != '-')
	{
		i++;
		Parsing::getParameters(line, ';', aux);
		if (aux[0] == "")
			aux[0] = "PL" + to_string(i);                                                                                 // Default Name
		shifts.push_back({ aux[0],stoi(aux[1]) });
	}

	int j = 1;
	for (list<ShiftInfo>::iterator it = shifts.begin(); it != shifts.end(); it++, j++)									// Verificar existência de Turnos com o mesmo nome
	{
		for (list<ShiftInfo>::iterator it2 = next(shifts.begin(), j); it2 != shifts.end(); it2++)
		{
			if (it->name == it2->name)
			{
				shifts.clear();
				throw invalid_argument("Error: Shifts with same name!");
			}

		}
	}
}


bool ShiftsInfo::validateFileLine(const string& line)
{
	int i = 0, integer;
	string token, aux[2];
	stringstream s(line);
	while (getline(s, token, ';'))																				
	{
		if (i < 2)
			aux[i] = token;
		else
			return false;
		i++;
	}
	if (aux[1] == "" || !Validator::validateInteger(aux[1], integer) || integer < 0)							
		return false;
	return true;
}

void ShiftsInfo::saveToFile(const string& filename)
{
	ofstream fou(filename);
	if (!fou.is_open())
		throw runtime_error("Error: Cannot create file!");
	for (list<ShiftInfo>::iterator it = shifts.begin(); it != shifts.end(); it++)
		fou << it->name << ";" << it->max_elements << endl;
	fou.close();
}

void ShiftsInfo::clear()
{
	shifts.clear();
}

int ShiftsInfo::index(string name)
{
	int index = 0;
	for (ShiftInfo i : shifts) 
	{
		if (i.name == name)
			return index;
		index++;
	}
	return 0;
}

void ShiftsInfo::add(const string& name, int max_elements)
{
	shifts.push_back({ name, max_elements });
}

bool ShiftsInfo::confirmPreferences(const string& preferences)
{
	stringstream ss(preferences);
	string token;
	bool flag = false;
	while (getline(ss, token, ';'))
	{
		for (ShiftInfo i : shifts)
		{
			if (token == i.name)
				flag = true;
		}
		if (flag == false)
			return false;
		flag = false;
	}
	return true;
}

string ShiftsInfo::info()
{
	string info;
	for (ShiftInfo i : shifts)
		info += i.name + " has " + to_string(i.max_elements) + " places\n";
	return info;
}

size_t ShiftsInfo::totalPlaces()
{
	size_t total = 0;
	for (ShiftInfo i : shifts)
		total += i.max_elements;
	return total;
}

size_t ShiftsInfo::size() 
{
	return shifts.size();
}