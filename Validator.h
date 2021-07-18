#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <string>
using namespace std;

class Validator
{
public:
	static bool validateName(const string& x);														// Valida��o das strings
	static bool validateInteger(const string& x, int& integer);										// Valida��o de um n�mero inteiro
	static bool validateDate(const string& date);													// Valida��o da Data
};

#endif