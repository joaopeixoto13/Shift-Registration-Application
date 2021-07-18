#include "Parsing.h"
#include "Validator.h"
#include "StringUtils.h"
#include "Time.h"
#include "Context.h"

#define NOT_REMOVED -2
void Booking::readFromFile(const string& filename , bool externfile)
{

	Context* context = Context::getInstance();
	string line;
	vector<string> save;
	char limiter = 0;																											

	ifstream fin(filename);																										
	if (!fin.is_open())																											// se deu erro a abrir o ficheiro
		throw invalid_argument("Error: Cannot open the " + filename + " file!");

	if (!getline(fin, line)) {
		fin.close();
		return;
	}
	if (!Parsing::findLimiter(line, limiter))																					// achar o delimitador/separador dos conteúdos dos ficheiros
	{
		fin.close();
		throw invalid_argument("Error:  " + filename + " Invalid file syntax!");
	}

	size_t ln_count = 1;
	bool error = false;																											// error flag

	while (getline(fin, line) && externfile)
	{
		ln_count++;
		if (!validateFileLine(line, limiter) || !context->getShiftsInfo().confirmPreferences(line))
		{
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
	int shift;
	while (getline(fin, line))
	{
		ln_count++;
		Parsing::getParameters(line, limiter, save);
		list<int> aux;
		for (int i = 3; i < context->getShiftsInfo().size() + 3; i++)
		{
			if(externfile)
				aux.push_back(context->getShiftsInfo().index(save[i]));
			else
				aux.push_back(stoi(save[i]));
		}
		Book a(save[0], stoi(save[2]) , aux);

		if (externfile)
			a.formatDate();

		int flag = add(a,shift);

		if (externfile) 
		{
			if (flag >= NOT_EXIST)
				report.push_back({ ln_count, "Student " + to_string(a.number) + " not exist!" });
			else if (flag == NOT_PLACED)
				report.push_back({ ln_count, "Student " + to_string(a.number) + " not placed!" });
			else if (flag == EE_PLACED)
				report.push_back({ ln_count, "Student " + to_string(a.number) + " was placed in shift " + to_string(shift + 1) + "!" });
			else if (flag == BOOKED)
				report.push_back({ ln_count, "Student " + to_string(a.number) + " was booked!" });
		}
	}
	fin.close();
}

void Booking::readFromBody(istringstream& body)
{
	istringstream verifiedbody(body.str());
	Context* context = Context::getInstance();
	string line;
	char limiter = 0;

	getline(body, line);
	getline(body, line);
	getline(body, line);
	getline(body, line);

	if (!getline(body, line))
		return;
	if (!Parsing::findLimiter(line, limiter))																					// achar o delimitador/separador dos conteúdos dos ficheiros
		throw invalid_argument("Error: Invalid file syntax!");

	size_t ln_count = 1;
	bool error = false;																											// error flag

	while (getline(body, line) && line.size() > 1 && line[0] != '-')
	{
		ln_count++;
		if (!validateFileLine(line, limiter) || !context->getShiftsInfo().confirmPreferences(line))
		{
			error = true;
			report.push_back({ ln_count,"Invalid parameters!" });
		}
	}
	if (error)																													// Caso houver alguma anomalia no ficheiro os dados não sao guardados
		throw runtime_error("Error: Corrupted file!");																			
																																// Caso nao haja nenhuma anomalia no ficheiro os dados são gravados
	getline(verifiedbody, line);
	getline(verifiedbody, line);
	getline(verifiedbody, line);
	getline(verifiedbody, line);
	getline(verifiedbody, line);
	ln_count = 1;
	int shift = 0;
	string* auxsave = new string[context->getShiftsInfo().size() + 4];
	vector<string> save;
	while (getline(verifiedbody, line) && line.size() > 1 && line[0] != '-')
	{
		ln_count++;
		Parsing::getParameters(line, limiter, save);
		list<int> aux;
		int j = 0;
		for (string i : save)
			auxsave[j++] = i;
		for (int i = 3; i < context->getShiftsInfo().size() + 3; i++)
			aux.push_back(context->getShiftsInfo().index(auxsave[i]));

		Book a(auxsave[0], stoi(auxsave[2]), aux);

		a.formatDate();

		int flag = add(a, shift);

		if (flag >= NOT_EXIST)
			report.push_back({ ln_count, "Student " + to_string(a.number) + " not exist!" });
		else if (flag == NOT_PLACED)
			report.push_back({ ln_count, "Student " + to_string(a.number) + " not placed!" });
		else if (flag == EE_PLACED)
			report.push_back({ ln_count, "Student " + to_string(a.number) + " was placed in shift " + to_string(shift + 1) + "!" });
		else if (flag == BOOKED)
			report.push_back({ ln_count, "Student " + to_string(a.number) + " was booked!" });
	}
}

bool Booking::validateFileLine(string& line, const char limiter)											
{
	Context* context = Context::getInstance();
	stringstream ss(line);
	line = "";																						// Obter linha das preferências
	string token;
	size_t actual_position = 0;

	while (getline(ss, token, limiter))
	{
		if (actual_position == 0)
		{
			if (token == "" || !Validator::validateDate(token))
				return false;
		}
		else if (actual_position == 1)
		{
			if (token == "" || !Validator::validateName(token))
				return false;
		}
		else if (actual_position == 2)
		{
			int aux;
			if (token == "" || !Validator::validateInteger(token, aux))
				return false;
		}
		else if (actual_position > 2)
		{
			line += token + limiter;
		}
		actual_position++;
	}
	if ((actual_position - 3) == context->getShiftsInfo().size())
		return true;
	return false;
}

int Booking::add(Book& st, int &shift)
{
	Context* context = Context::getInstance();
	Student temp(st.number, "", SpecialStatus::NORMAL);
	if (!context->getStudents().contains(temp))														// Validar se Aluno existe na lista de Inscritos
		return st.number;	

	if (context->getStudents().hasEE(st.number))													// Verificar se Aluno é prioritário
	{
		shift = context->getShifts().add(temp, st.preferences);										// Obter o turno 
		if(shift == NOT_PLACED)																		// Se o aluno não foi colocado (vagas inexistentes - preenchidas por outros alunos com EE)
			return NOT_PLACED;
		return EE_PLACED;																			// Aluno prioritário colocado
	}

	if (!st.date.size())																			// Se não possuir data
		st.date = Time::timeNow();																	// Obter a data atual 

	if (!booking.size()) 
	{
		booking.push_back(st);
		return BOOKED;
	}

	list<Book>::iterator aux;															
	for ( aux = booking.begin(); aux != booking.end() ; aux++)
	{
		if (st.number == aux->number) 
		{
			if (booking.back().number == st.number) 
			{
				booking.pop_back();
				break;
			}
			else
				aux = booking.erase(aux);
		}
		if (st.date.compare(aux->date) < 0) 
		{
			booking.insert(aux, st);
			return BOOKED;
		}
	}
	booking.push_back(st);
	return BOOKED;
}

void Booking::remove(int number)
{
	Context* context = Context::getInstance();
	if(context->getShifts().remove(number) != NOT_REMOVED)
		return;
	for (list<Book>::iterator it = booking.begin(); it != booking.end(); it++) 
	{
		if (it->number == number) 
		{
			booking.erase(it);
			return;
		}
	}
	throw runtime_error("Error: Student " + to_string(number) + " does not exist!");
}

void Booking::saveToFile(const string& filename)
{
	ofstream fou(filename, ios::out);
	if (!fou.is_open())
		throw runtime_error("Error: Cannot create " + filename + " file!");
	fou << "Date;Name;Number;Preferences\n";
	for (auto i = booking.begin(); i != booking.end(); i++) 
		fou << *i << endl;
	fou.close();
}

void Booking::ReportBook()
{
	system("cls");
	cout << "-------------BOOKING ENROLLMENT REPORT-------------" << endl << endl;
	for (auto i = report.begin(); i != report.end(); i++)
		cout << *i << endl;																				// linha que ocorreu o erro + motivo do erro
	cout << "---------------------------------------------------" << endl << endl;
	report.clear();
}

void Booking::ReportBookHtml()
{
	cout << "<div class = ""info-titles""><h5>----------------------BOOKING ENROLLMENT REPORT-------------------------</h5></div>\n";														
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
		cout << "<tr>\n<td>" + to_string(i->line) + "</td>\n<td>" + i->info + "</td>\n</tr>\n";

	cout << "   </tbody>\n"
		<< " </table>\n"
		<< "</div>\n";
	report.clear();
}

size_t Booking::size()
{
	return booking.size();
}

string Booking::find(int number)
{
	Context* context = Context::getInstance();
	string shiftName = context->getShifts().find(number);
	if (shiftName.size())
		return "Student " + to_string(number) + " is in " + shiftName;
	for (list<Book>::iterator it = booking.begin(); it != booking.end(); it++)
	{
		if (it->number == number)
		{
			return "Student " + to_string(it->number) + " is in booking list!";
		}
	}
	return "Student " + to_string(number) + " has yet to be booked!";
}

void Booking::generateShifts(const string& filename)
{

	ofstream report(filename + "\\Report.txt");
	if (!report.is_open())
		throw invalid_argument("Error: Cannot open the " + filename + " file!");

	Context* context = Context::getInstance();
	for (list<Book>::iterator it = booking.begin(); it != booking.end(); it++)
	{
		Student temp(it->number, "", SpecialStatus::NORMAL);
		context->getStudents().contains(temp);
		if (context->getShifts().add(temp, it->preferences) == NOT_PLACED)
			report << "Student " + to_string(temp._number()) + " was not placed: the chosen shift(s) is already full.\n";
	}
	context->getShifts().saveToFile(filename + "\\");
	report.close();
}

void Booking::clear()
{
	booking.clear();
}
