#include "WebRegisterShiftsManual2.h"
#include "Context.h"
#include "HtmlPage.h"

void WebRegisterShiftsManual2::process()
{
	Context* context = Context::getInstance();
	if (context->getMethod() == "POST" && context->getBody())
	{
		cout << HtmlPage::HtmlSuccess("Successful!");
		vector<string>vec;
		Parsing::bodyParameter(context->getBody().str(), vec, true);
		string aux;
		for (int i = 0; i < vec.size(); i++)
		{
			if (i % 2 == 0)
				aux = vec[i];
			else
				context->getShiftsInfo().add(aux, stoi(vec[i]));
		}
		context->getStudents().saveToFile("ficheiros\\my\\UC_Students.csv");						            // Guardar no ficheiro os casos bem sucedidos
		context->getShifts().setInfo();
	}
}
