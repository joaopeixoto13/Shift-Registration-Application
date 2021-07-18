#include "Students.h"
#include <iostream>
#include "Validator.h"
#include "StringUtils.h"

Students::Students(size_t _size)
	:table(_size)
{ }

void Students::readFromFile(const string& filename)
{
	string line;
	vector<string> save;
	char limiter = 0;
	int index[3];																												//Number,Name,EE

	ifstream fin(filename);																										// abrir ficheiro em modo escrita
	if (!fin.is_open())																											// se deu erro a abrir o ficheiro
		throw invalid_argument("Error: Cannot open the " + filename + " file!");

	if (!getline(fin, line)) {
		fin.close();
		return;
	}
	if (!Parsing::findLimiter(line, limiter) || !Parsing::getPositions(line, limiter, index[0], index[1], index[2]))			// achar o delimitador/separador dos conteúdos dos ficheiros
	{
		fin.close();
		throw invalid_argument("Error: Invalid " + filename + " file syntax!");
	}

	size_t ln_count = 1;
	bool error = false;																											// error flag

	while (getline(fin, line))
	{
		ln_count++;
		if (!validateFileLine(line, limiter, index)) {
			error = true;
			report.push_back({ ln_count,"Invalid parameters!" });
		}
	}
	if (error)																													// Caso houver alguma anomalia no ficheiro os dados não sao guardados
	{																															// e são reportados todos os erros para futura correção
		fin.close();
		throw runtime_error("Error: Corrupted file!");
	}																															// Caso nao haja nenhuma anomalia no ficheiro os dados são gravados
	fin.clear();																												// Limpar flag de final de ficheiro
	fin.seekg(0);																												// Posicionar o ficheiro no inicio					
	getline(fin, line);
	ln_count = 1;
	while (getline(fin, line))
	{
		ln_count++;
		Parsing::getParameters(line, limiter, save);
		if (save.size() == 2)
			save.push_back("");
		Student a(stoi(save[index[0]]), save[index[1]], Student::statusInt(save[2]));
		if (!table.add(a))
			report.push_back({ ln_count, "Student " + to_string(a._number()) + " already exist!" });
	}
	fin.close();																												// fechar o ficheiro
}

void Students::readFromBody(istringstream& body)
{
	istringstream verifiedbody(body.str());
	string line;
	vector<string> save;
	char limiter = 0;
	int index[3];																												//Number,Name,EE
	for (int i = 0; i < 4; i++)
		getline(body, line);

	if (!getline(body, line))
		return;

	if (!Parsing::findLimiter(line, limiter) || !Parsing::getPositions(line, limiter, index[0], index[1], index[2]))			// achar o delimitador/separador dos conteúdos dos ficheiros
		throw invalid_argument("Error: Invalid file syntax!");

	size_t ln_count = 1;
	bool error = false;																											// error flag

	while (getline(body, line) && line.size() > 1 && line[0] != '-')
	{
		ln_count++;
		if (!validateFileLine(line, limiter, index)) {
			error = true;
			report.push_back({ ln_count,"Invalid parameters!" });
		}
	}
	if (error)																													// Caso houver alguma anomalia no ficheiro os dados não sao guardados																															// e são reportados todos os erros para futura correção
		throw runtime_error("Error: Corrupted file!");																			// Caso nao haja nenhuma anomalia no ficheiro os dados são gravados
																																// Posicionar o ficheiro no inicio					
	getline(verifiedbody, line);
	getline(verifiedbody, line);
	getline(verifiedbody, line);
	getline(verifiedbody, line);
	getline(verifiedbody, line);
	ln_count = 1;
	while (getline(verifiedbody, line) && line.size() > 1 && line[0] != '-')
	{
		ln_count++;
		Parsing::getParameters(line, limiter, save);
		if (save.size() == 2)
			save.push_back("");
		Student a(stoi(save[index[0]]), save[index[1]], Student::statusInt(save[2]));
		if (!table.add(a))
			report.push_back({ ln_count, "Student " + to_string(a._number()) + " already exist!" });
	}
}

bool Students::validateFileLine(const string& line, const char limiter, int index[])
{
	stringstream ss(line);
	string token;
	int actual_position = 0;
	while (getline(ss, token, limiter))
	{
		if (actual_position == index[0])
		{
			int aux;
			if (token == "" || !Validator::validateInteger(token, aux))
				return false;
		}
		else if (actual_position == index[1])
		{
			if (token == "" || !Validator::validateName(token))
				return false;
		}
		else if (actual_position == index[2])
		{
			StringUtils::toUpper(token);
			if ((token != "TE" && token != "AAC" && token != "DAE" && token != "PDEF" && token != "DLG" && token != ""))
				return false;
		}
		actual_position++;
	}
	if (actual_position > 3 || (token == "" && actual_position != index[2]))
		return false;
	return true;
}

void Students::add(Student& st)
{
	if (!table.add(st))
		report.push_back({ 0, "Student " + to_string(st._number()) + " already exist!" });
}


bool Students::remove(int number)
{
	if(!table.remove(number))
		throw runtime_error("Impossible to remove, student " + to_string(number) + " does not exist!");
	return true;
}

bool Students::contains(Student &st)
{
	return table.contains(st);
}

bool Students::hasEE(int& number)
{
	return table.hasEE(number);
}


void Students::saveToFile(const string& filename)
{
	ofstream fou(filename, ios::out);
	if (!fou.is_open())
		throw runtime_error("Error: Cannot create file!");

	list<Student>students = table.elements();
	fou << "Numero;Nome;Estatuto Especial" << endl;
	for (auto i = students.begin(); i != students.end(); i++)
		fou << *i << endl;
	fou.close();
}


void Students::reportStudents()
{
	system("cls");
	cout << "------------------UC ENROLLMENT REPORT-------------------" << endl << endl;
	if (!report.size())																										// Se não tiver erros																									
	{
		cout << "Sucesseful!" << endl;
		cout << "Number of students received: " << table.size() << endl;
		return;
	}
	cout << "Failed!" << endl << endl;
	cout << "Errors:" << endl;
	for (auto i = report.begin(); i != report.end(); i++)
		cout << *i << endl;																									// linha que ocorreu o erro + motivo do erro
	cout << "---------------------------------------------------------" << endl << endl;
	report.clear();
}

void Students::reportStudentsHtml()
{
	cout << "<div class = ""info-titles""><h5>-------------------------UC ENROLLMENT REPORT-------------------------</h5></div>\n";
	if (!report.size())																										// Se não tiver erros																									
	{
		cout << "<div class = ""info-titles""><h6>Sucesseful!</h6></div>\n";
		cout << "<div class = ""info-titles""><h6>Number of students received: "+ to_string(table.size())+ "</h6></div>\n";
		return;
	}
	cout << "<div class = ""info-titles""><h6>Failed!</h6></div>\n";
	cout << "<div class = ""info-titles""><h6>Errors:</h6></div>\n";
	cout << "<div class = ""info-wrapper"">\n"
		<< "   <table>\n"
		<< "   <thead>"
		<< "   <tr>\n"
		<< "   <th>Line</th>\n"
		<< "   <th>Reason</th>\n"
		<< "   </tr>\n"
		<< "   </thead>\n"
		<< "   <tbody>\n";

	for (auto i = report.begin(); i != report.end(); i++)
		cout << "<tr>\n<td>" + to_string(i->line) + "</td>\n<td>" + i->fail + "</td>\n</tr>\n";

	cout << "   </tbody>\n"
		<< " </table>\n"
		<< "</div>\n";
	report.clear();
}


size_t Students::size()
{
	return table.size();
}

list<Student> Students::elements()
{
	return table.elements();
}

void Students::clear()
{
	table.clearTable();
}


