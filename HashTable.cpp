#include "HashTable.h"
#include <stdexcept>

HashTable::HashTable(size_t _size)
    : _size(_size)
{
    table = new list<Student>[_size];
}

HashTable::~HashTable()
{
    delete[] table;
}

size_t HashTable::hashing(int number) const
{
    return number % _size;
}

bool HashTable::add(Student& a)
{
    if (contains(a))                                                                                     // Elemento repetido
        return false;
    size_t index = hashing(a.number);
    table[index].push_back(a);
    return true;
}

bool HashTable::contains(Student &st) 
{
    size_t index = hashing(st.number);
    for (Student stt : table[index])
    {
        if (stt.number == st.number) {
            st = stt;
            return true;
        }
    }
    return false;
}

bool HashTable::hasEE(int number)
{
    size_t index = hashing(number);
    for (Student st : table[index])
    {
        if (st.number == number) {
            if (st.EE == SpecialStatus::NORMAL)
                return false;
        }
    }
    return true;
}


bool HashTable::remove(int number)
{
    size_t index = hashing(number);
    for (list<Student>::iterator it = table[index].begin(); it != table[index].end(); it++)
    {
        if (it->number == number)
        {
            table[index].erase(it);
            return true;
        }
    }
    return false;
}

size_t HashTable::size() const
{
    size_t count = 0;
    for (size_t i = 0; i < _size; i++)
        count += table[i].size();
    return count;
}

list<Student> HashTable::elements()
{
    list<Student>elements;
    for (size_t index = 0; index < _size; index++)
    {
        for (list<Student>::iterator it = table[index].begin(); it != table[index].end(); it++)
            elements.push_back(*it);
    }
    return elements;
}

void HashTable::clearTable()
{
    for (size_t index = 0; index < _size; index++)
        table[index].clear();
}