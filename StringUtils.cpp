#include "StringUtils.h"
#include <sstream>

void StringUtils::toUpper(string& x)
{
	for (size_t i = 0; i < x.size(); i++)
	{
		if (x[i] >= 97 && x[i] <= 122)
			x[i] -= 32;
	}
}

void StringUtils::orderDate(string& x)        
{											  
	stringstream ss(x);
	string token, save[6];
	int i = 0, j = 0;
	while (getline(ss, token, ' ')) 
	{
		stringstream sss(token);
		if (j++ == 0) 
		{
			while (getline(sss, token, '/'))
				save[i++] = token;
		}
		else 
		{
			while (getline(sss, token, ':'))
				save[i++] = token;
		}
	}
	x = save[2] + "/" + save[0] + "/" + save[1] + " " + save[3] + ":" + save[4] + ":" + save[5];
}

istringstream StringUtils::formatBody(istringstream& str)
{
	string aux = str.str();
	string final;
	for (int i = 0; i < aux.size(); i++) {
		if (aux[i] != '\r')
			final += aux[i];
	}
	return istringstream(final);
}
