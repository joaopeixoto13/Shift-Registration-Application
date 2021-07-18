#ifndef REPORT_H
#define REPORT_H

#include <ostream>
#include <iomanip>
#include <string>
using namespace std;

struct Error
{
    size_t line;                                                                                                // Linha que ocorre o erro
    string fail;                                                                                                // Motivo do erro
};

ostream& operator<<(ostream& os, const Error& error);

struct feedBack
{
    size_t line;                                                                                                // Linha que ocorre o erro
    string info;
};

ostream& operator<<(ostream& os, const feedBack& error);

#endif