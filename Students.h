#ifndef STUDENTS_H
#define STUDENTS_H
#include "HashTable.h"
#include "Parsing.h"
#include "Report.h"
#include <fstream>

using namespace std;

class Students
{
    HashTable table;                                                                    // Table com Alunos Inscritos na UC
    vector<Error> report;                                                               // Vector de Erros / anomalias

public:
    Students(size_t _size);
    void readFromFile(const string& filename);                                          // Ler o ficheiro que cont�m os Inscritos na UC
    void readFromBody(istringstream& body);
    bool validateFileLine(const string& line, const char limiter, int index[]);	        // Validar toda linha de um fixheiro .csv que cont�m os alunos da UC (Numero;Nome;EE)
    void add(Student& st);                                                              // Adicionar um Aluno � UC
    bool remove(int number);                                                            // Remover um Aluno da UC
    bool contains(Student &st);                                                         // Testar se um Aluno pertence � lista de Inscritos
    bool hasEE(int& number);                                                            // Testar se um Aluno possuiu Estatuto Especial
    void saveToFile(const string& filename);                                            // Guardar os alunos inscritos na UC
    void reportStudents();                                                              // Reportar os erros / anomalias recebidas
    void reportStudentsHtml();                                                              // Reportar os erros / anomalias recebidas
    size_t size();                                                                      // N�mero de Alunos Inscritos na UC
    list<Student> elements();
    void clear();
};																	

#endif