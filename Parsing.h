#ifndef PARSING_H
#define PARSING_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

class Parsing
{
public:
	static void bodyParameter(const string& line, vector<string>& save, bool flag);
	static bool findLimiter(const string& line, char& limiter);																				// Validar e encontrar o delimitador de um ficheiro .csv
	static bool getPositions(const string& line, const char limiter, int& number_index, int& name_index, int& EE_index);					// Obter as posi��es/disposi��o em que se encontram as informa��es no ficheiro (Numero;Nome;EE ... Nome;EE;Numero)
	static void getParameters(const string& line, const char limiter, vector<string>& save);												// Obter todos os par�metros de uma linha de um ficheiro .csv

};

#endif 
