#ifndef STUDENT_H
#define STUDENT_H
#include <string>
#include <iostream>

using namespace std;

enum class SpecialStatus
{
    NORMAL,
    TE,
    AAC,
    DAE,
    PDEF,
    DLG,   
};

class Student
{
    int number;
    string name;
    SpecialStatus EE;

public:
    friend class HashTable;
    Student(const int& number, const string& name, SpecialStatus EE = SpecialStatus::NORMAL);
    Student(const Student& student);
    int _number();
    static SpecialStatus statusInt(string ee);
    static string statusStr(SpecialStatus ee);
    string _name() { return name; }
    string _EE() { return statusStr(EE); }
    friend ostream& operator<<(ostream& os, const Student& st);
};

#endif