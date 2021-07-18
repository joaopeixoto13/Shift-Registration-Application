#include "Student.h"
#include "StringUtils.h"


Student::Student(const int& number, const string& name, SpecialStatus EE)
	: number(number), name(name), EE(EE)
{ }

Student::Student(const Student& student)
	: Student(student.number, student.name, student.EE)
{ }

int Student::_number()
{
	return number;
}

SpecialStatus Student::statusInt(string ee)
{	
	StringUtils::toUpper(ee);
	if (ee == "") return SpecialStatus::NORMAL;
	else if (ee == "TE") return SpecialStatus::TE;
	else if (ee == "AAC") return SpecialStatus::AAC;
	else if (ee == "DAE") return SpecialStatus::DAE;
	else if (ee == "DLG") return SpecialStatus::DLG;
	else if (ee == "PDEF") return SpecialStatus::PDEF;
	else return SpecialStatus::NORMAL;
}

string Student::statusStr(SpecialStatus ee)
{
	switch (ee)
	{
		case SpecialStatus::NORMAL: return ""; break;
		case SpecialStatus::TE: return "TE"; break;
		case SpecialStatus::AAC: return "AAC"; break;
		case SpecialStatus::DAE: return "DAE"; break;
		case SpecialStatus::DLG: return "DLG"; break;
		case SpecialStatus::PDEF: return "PDEF"; break;
	}
	return "dummy";
}

ostream& operator<<(ostream& os, const Student& st)
{
	os << st.number << ";" << st.name << ";" << Student::statusStr(st.EE);
	return os;
}