#include "HomeMenu.h"
#include "ConfigMenu.h"
#include "BookingMenu.h"
#include "Console.h"
#include <locale>
#include "Context.h"
#include "Clear.h"
#include "FastCGI.h"
#include "HtmlPage.h"
#include "StringUtils.h"
#include "Factory.h"
#define FAIL 1

using namespace std;

int main(int argc , char *argv[])
{
	system("chcp 1252 > nul");																								// Habilitar input ascii extendido
	setlocale(LC_ALL, "portuguese");																						// Habilitar output ascii extendido
	bool blocked = false;
	string mode;

	if (argc == 2)
		mode = argv[1];

	/////////////////////
	//	   Console     //
	/////////////////////
	if (mode == "-c") 
	{																								
		BaseMenu* menu = new HomeMenu();
		Context* context = Context::getInstance();
		string option;
		int state = 5, nextState = 2;

		cout << "Do you want to continue last session ? [y/n]" << endl;
		option = Console::readName("Your choice : ");
		if (option == "y" || option == "Y")
		{
			try { context->getStudents().readFromFile("ficheiros\\my\\UC_Students.csv"); }
			catch (exception& e) { cout << e.what() << endl; }																// Colocar ficheiro na Tabela de Hash
			try { context->getShiftsInfo().readFromFile("ficheiros\\my\\ShiftsInformation.csv"); }
			catch (exception& e) { cout << e.what() << endl; }																// Colocar no vector a informação dos Turnos
			context->getShifts().setInfo();
			try { context->getBooking().readFromFile("ficheiros\\my\\Booking.csv", false); }
			catch (exception& e) { cout << e.what() << endl; }																// Colocar no Booking as Marcações já efetuadas
			if (!Clear::empty("ficheiros\\my\\placed"))
			{
				try { context->getShifts().readFromFile("ficheiros\\my\\placed\\"); }
				catch (exception& e) { cout << e.what() << endl; }
			}
			if (context->getBooking().size() || context->getShifts().size())												// Se já efetuou alguma Marcação -> Não deixar efetuar novas alteracões no registo da UC (Turnos / Alunos da UC)
				blocked = true;
		}
		else
			Clear::removeLoadFiles();

		while (nextState != EXIT)
		{
			menu->print();																											// Print do menu
			menu->read_option();																									// Ler a op��o do menu
			try
			{
				nextState = menu->process_option();																					// Processar a op��o do menu
				if (nextState != state)
				{
					if (nextState == CONFIG_MENU)																					// Manusear UC (FASE 1)
					{
						if (!blocked)
						{
							state = nextState;
							menu = new ConfigMenu();
						}
						else
							throw runtime_error("Error: Booked was inicialized!");
					}
					else if (nextState == BOOKING_MENU)																				// Manusear Marca��es (FASE 2)
					{
						if (context->getStudents().size() > 0 && context->getShiftsInfo().totalPlaces() > 0 && context->getShiftsInfo().totalPlaces() >= context->getStudents().size())
						{
							state = nextState;
							blocked = true;
							menu = new BookingMenu();
						}
						else
							throw runtime_error("Error: Invalid configuration of Students/Shifts!");
					}
					else if (nextState == GENERATE)																					// Home Menu
					{
						if (!context->getBooking().size() && !context->getShifts().size())
							throw runtime_error("Error: Cannot generate shifts!");
						if ((context->getBooking().size() + context->getShifts().size()) < context->getStudents().size())			// Se existir alunos inscritos na UC que ainda n�o fizeram a sua marca��o 
						{
							cout << "Warming: Not all students are booked!" << endl;
							cout << "Do you want to continue ? [y/n]" << endl;
							option = Console::readName("Your choice : ");
							if (option != "y" && option != "Y")
								throw runtime_error("Aborted successfully!");
						}
						cout << "Warning:    Please choose one folder without shifts names" << endl;
						cout << "Suggestion: Create a empty folder!" << endl;
						string filename = Console::readString("Insert folder: ");
						context->getBooking().generateShifts(filename);
						cout << "Successful!" << endl << endl;
						cout << "All data files removed for new session!" << endl;
						Clear::removeLoadFiles();
						Context::reset();
						blocked = false;
					}
					else if (nextState == HOME_MENU)																					// Home Menu
					{
						state = nextState;
						menu = new HomeMenu();
					}
				}
			}
			catch (exception& ex) {
				cout << ex.what() << endl;
			}
		}
		system("cls");
		return 0;

	}	
	/////////////////////
	//	     Web       //
	///////////////////// 
	else 
	{
		Context* context = Context::getInstance();
		FCGX_Request request;
		FCGX_Init();
		FCGX_InitRequest(&request, 0, 0);

		try {
			context->getStudents().readFromFile("ficheiros\\my\\UC_Students.csv");											// Colocar ficheiro na Tabela de Hash
			context->getShiftsInfo().readFromFile("ficheiros\\my\\ShiftsInformation.csv");
			context->getShifts().setInfo();																					// Colocar no vector a informação dos Turnos
			context->getBooking().readFromFile("ficheiros\\my\\Booking.csv", false);										// Colocar no Booking as Marcações já efetuadas
			if (!Clear::empty("ficheiros\\my\\placed"))
				context->getShifts().readFromFile("ficheiros\\my\\placed\\");
		}
		catch (...) {
			Clear::removeLoadFiles();
		}
		if (context->getBooking().size() || context->getShifts().size())												    // Se já efetuou alguma Marcação -> Não deixar efetuar novas alteracões no registo da UC (Turnos / Alunos da UC)
			blocked = true;

		streambuf* cin_streambuf = cin.rdbuf();
		streambuf* cout_streambuf = cout.rdbuf();
		streambuf* cerr_streambuf = cerr.rdbuf();

		while (FCGX_Accept_r(&request) == 0)
		{
			fcgi_streambuf cin_fcgi_streambuf(request.in);
			fcgi_streambuf cout_fcgi_streambuf(request.out);
			fcgi_streambuf cerr_fcgi_streambuf(request.err);

			cin.rdbuf(&cin_fcgi_streambuf);
			cout.rdbuf(&cout_fcgi_streambuf);
			cerr.rdbuf(&cerr_fcgi_streambuf);

			istringstream bodyaux;
			unsigned long clen = FastCGI::readBody(request, bodyaux);
			context->getBody() = (StringUtils::formatBody(bodyaux));
			char* pMethod = FCGX_GetParam("REQUEST_METHOD", request.envp);
			context->getMethod() = pMethod;
			char* pUri = FCGX_GetParam("REQUEST_URI", request.envp);
			string uri(pUri);

			AbstractMenu* menu = Factory::create(uri);
			menu->method();

		}
		cin.rdbuf(cin_streambuf);
		cout.rdbuf(cout_streambuf);
		cerr.rdbuf(cerr_streambuf);

		return 0;
	}
}