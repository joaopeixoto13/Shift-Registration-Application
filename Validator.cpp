#include "Validator.h"
#include <sstream>

#define IS_DIGIT(i) (i >= '0' && i <= '9')


bool Validator::validateName(const string& x)
{
	for (int i = 0; x[i] != '\0'; i++) {
		if (IS_DIGIT(x[i]))
			return false;
	}
	return true;
}


bool Validator::validateInteger(const string& x, int& integer)
{
	for (int i = 0; x[i] != '\0'; i++) {
		if (!IS_DIGIT(x[i]))
			return false;
	}
	integer = stoi(x);
	return true;
}

bool Validator::validateDate(const string& date)
{
    stringstream ss(date);
    string token, aux, save[3];
    char delimiter = '/';
    int save_date[3], i = 0, actual_position = 0;
    int dias[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };

    if (date.length() == 0)
        return false;

    while (getline(ss, token, ' '))
    {
        stringstream sss(token);

        if (actual_position == 0)
            delimiter = '/';
        else if (actual_position == 1)
            delimiter = ':';

        while (getline(sss, aux, delimiter)) 
        {
            if (aux == "")
                return false;
            save[i++] = aux;
        }
        if(i != 3)
            return false;
        for (int j = 0; j < 3; j++)
        {
            if (!validateInteger(save[j], save_date[j]))
                return false;
        }
        if (actual_position == 0)                    // Validar dia, mês e ano
        {
            if (save_date[2] % 4 == 0 && (save_date[2] % 400 == 0 || save_date[2] % 100 != 0))
                dias[2] = 29;
            else
                dias[2] = 28;
            if (save_date[1] <= 0 || save_date[0] < 1 || save_date[0] > 12 || save_date[2] <= 0 || save_date[1] > dias[save_date[0]])
                return false;
        }
        else if (actual_position == 1)                // Validar hora, minutos e segundos
        {
            if (save_date[0] > 23 || save_date[0] < 0 || save_date[1] > 59 || save_date[1] < 0 || save_date[2] > 59 || save_date[2] < 0)
                return false;
        }
        else
            return false;
        actual_position++;
        i = 0;
    }

    if (actual_position == 2)
        return true;

    return false;
}