#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <string>
using namespace std;

class Validator
{
public:
	static bool validateName(const string& x);														// Validação das strings
	static bool validateInteger(const string& x, int& integer);										// Validação de um número inteiro
	static bool validateDate(const string& date);													// Validação da Data
};

#endif