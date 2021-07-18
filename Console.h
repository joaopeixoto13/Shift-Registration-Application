#ifndef CONSOLE_H
#define CONSOLE_H

#include "Validator.h"
using namespace std;

class Console
{
public:
	static int readNumber(const string& text);																	// Ler e validar números vindos da consola
	static string readString(const string& text);																// Ler e validar strings vindas da consola
	static string readName(const string& text);																	// Ler e validar nomes vindas da consola
};

#endif