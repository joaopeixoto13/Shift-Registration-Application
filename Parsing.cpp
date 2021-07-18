#include "Parsing.h"

void Parsing::bodyParameter(const string& line, vector<string>& save, bool flag)
{
	string aux = line;
	for (int i = 0; i < aux.size(); i++)
	{
		if (aux[i] == '&')
			aux[i] = '=';
		if (aux[i] == '+')
			aux[i] = ' ';
	}
	save.clear();
	stringstream ss(aux);
	string token;
	int i = 0;
	while (getline(ss, token, '=') && token != "") {
		if (i++ % 2) 
			save.push_back(token);
		else if(flag)
			save.push_back(token);
	}

}

bool Parsing::findLimiter(const string& line, char& limiter)
{
	for (int i = 0; line[i] != '\n'; i++)
	{
		if (line[i] == ',' || line[i] == ';' || line[i] == ':' || line[i] == '=')
		{
			limiter = line[i];
			return true;
		}
	}
	return false;
}

bool Parsing::getPositions(const string& line, const char limiter, int& number_index, int& name_index, int& EE_index)
{
	int actual_position = 0;
	bool name_lock = false, number_lock = false, EE_lock = false;
	string token;
	stringstream ss(line);
	while (getline(ss, token, limiter))														// Achar ordem que aparecem as variáveis no ficheiro
	{																						// Exemplo: 
		if (token == "Numero" && !number_lock)												// 1. Numero;Nome;Estatuto Especial
		{																					// 2. Nome;Estatuto Especial;Numero
			number_index = actual_position;													// 3. Estatuto Especial;Numero;Nome
			number_lock = true;																// 4. ....
		}
		else if (token == "Nome" && !name_lock)
		{
			name_index = actual_position;
			name_lock = true;
		}
		else if (token == "Estatuto Especial" && !EE_lock)
		{
			EE_index = actual_position;
			EE_lock = true;
		}
		else
			return false;
		actual_position++;
	}
	return true;
}

void Parsing::getParameters(const string& line, const char limiter, vector<string>& save)
{
	stringstream s(line);
	string token;
	int i = 0;
	save.clear();
	while (getline(s, token, limiter))
		save.push_back(token);
}




