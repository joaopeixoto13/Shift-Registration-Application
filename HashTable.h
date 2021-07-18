#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include <list>
#include "Student.h"

using namespace std;

class HashTable
{
    list<Student>* table;
    size_t _size;
    size_t hashing(int number) const;

public:
    HashTable(size_t _size);
    ~HashTable();   
    bool add(Student& a);                                                                                           // Adicionar um Aluno 
    bool contains(Student &st);                                                                                     // Verificar se um Aluno existe 
    bool hasEE(int number);
    bool remove(int number);                                                                                        // Remover um Aluno                                                                                     // Calcular o loadFactor da tabela
    size_t size() const;                                                                                            // Calcular o tamanho / número de Alunos
    list<Student> elements();                                                                                       // Dispor os Alunos
    void clearTable();                                                                                              // Limpar 
};

#endif