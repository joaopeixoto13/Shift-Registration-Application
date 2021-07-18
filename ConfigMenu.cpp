#include "ConfigMenu.h"
#include "StringUtils.h"

void ConfigMenu::print()
{
	system("pause");
	system("cls");
	cout << "Insert one file with the the UC students           -> 1\n";
	cout << "Insert one student manually                        -> 2\n";
	cout << "Insert one file with the shifts information        -> 3\n";
	cout << "Insert the shifts information manually             -> 4\n";
	cout << "Remove one Student                                 -> 5\n";
	cout << "Find one Student                                   -> 6\n";
	cout << "Consult Data                                       -> 7\n";
	cout << "Exit                                               -> 8\n";
	cout << "\n\nNote: If you choose the 3 or 4 option, all previously information about the shifts will be lost and replaced ... \n\n";
}

void ConfigMenu::read_option()
{
	do {
		option = Console::readNumber("Insert your option: ");
	} while (option < 1 || option > 8);
}

int ConfigMenu::process_option()
{
	Context* context = Context::getInstance();
	string filename;
	
	switch (option)
	{
		// ---------------------------------------------------------------------------------------------------------------------------------
	case(1):																										// Case 1 -> Inserir ficheiro para leitura
	{
		filename = Console::readString("Insert filename: ");
		try {
			context->getStudents().readFromFile(filename);																// Ler o ficheiro recebido e processar a informação
		}
		catch (invalid_argument& e) {
			cout << e.what() << endl;
			break;
		}
		catch (runtime_error& e) {
			cout << e.what() << endl;
			system("pause");																						// Guardar o relatório de eventuais anomalias
		}
		context->getStudents().reportStudents();
		break;
	}
	// ---------------------------------------------------------------------------------------------------------------------------------				
	case(2):																										// Case 2 -> Inserir Aluno manualmente 
	{
		string EE;
		int number = Console::readNumber("Insert number: ");
		string name = Console::readName("Insert name: ");
		string op_EE = Console::readString("The student have Special Status?[y/n]: ");
		if (op_EE == "y" || op_EE == "Y")
		{
			cout << "Possible Special Status options: TE / AAC / DAE / PDEF / DLG" << endl;
			do {
				EE = Console::readString("Insert the EE: ");
				StringUtils::toUpper(EE);
			} while (EE != "TE" && EE != "AAC" && EE != "DAE" && EE != "PDEF" && EE != "DLG");
		}
		Student st(number,name, Student::statusInt(EE));
		context->getStudents().add(st);																				// Adicionar o aluno inscrito
		context->getStudents().reportStudents();																	// Reportar eventuais erros									
		break;
	}
	// ---------------------------------------------------------------------------------------------------------------------------------				
	case(3):
	{
		cout << "File Example: Name;Elements (Name is optional) -> PL1;20 or ;20" << endl;
		filename = Console::readString("Insert filename: ");
		context->getShiftsInfo().clear();
		context->getShiftsInfo().readFromFile(filename);
		context->getShiftsInfo().saveToFile("ficheiros\\my\\ShiftsInformation.csv");
		cout << "Shifts loaded with success!" << endl;
		break;
	}
	// ---------------------------------------------------------------------------------------------------------------------------------
	case(4):
	{
		int n_shifts = Console::readNumber("Insert the number of shifts: ");
		string name = Console::readName("Insert the name for shifts: ");
		context->getShiftsInfo().clear();
		for (int i = 1; i <= n_shifts; i++)
		{
			int n_elements = Console::readNumber("Insert the maximum number of students for " + name + to_string(i) + ": ");
			context->getShiftsInfo().add(name + to_string(i), n_elements);
		}
		context->getShiftsInfo().saveToFile("ficheiros\\my\\ShiftsInformation.csv");
		break;
	}
	// ---------------------------------------------------------------------------------------------------------------------------------
	case(5):
	{
		int number = Console::readNumber("Insert the number of student to remove: ");
		context->getStudents().remove(number);
		cout << "Student removed successful!" << endl;
		break;
	}
	// ---------------------------------------------------------------------------------------------------------------------------------
	case(6):
	{
		int number = Console::readNumber("Insert the number of student to find: ");
		Student a(number, "", SpecialStatus::NORMAL);
		if (context->getStudents().contains(a)) {
			cout << endl << "Number;Name;SpecialStatus" << endl;
			cout << a << endl;
		}
		else
			cout << "Student does not exist!" << endl;
		break;
	}
	// ---------------------------------------------------------------------------------------------------------------------------------
	case(7):
	{
		system("cls");
		cout << "----------------- SUMMARY ------------------" << endl << endl;
		cout << "Total Number of Students: " << context->getStudents().size() << endl;
		cout << context->getShiftsInfo().info() << endl;
		break;
	}
	// ---------------------------------------------------------------------------------------------------------------------------------
	case(8):
	{
		return HOME_MENU;
		break;
	}
	// ---------------------------------------------------------------------------------------------------------------------------------
	}																							// Verifica se é compatível o número de alunos com o número de vagas
	context->getStudents().saveToFile("ficheiros\\my\\UC_Students.csv");						// Guardar no ficheiro os casos bem sucedidos
	context->getShifts().setInfo();
	return CONFIG_MENU;
}