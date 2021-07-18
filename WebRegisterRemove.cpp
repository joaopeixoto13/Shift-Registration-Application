#include "WebRegisterRemove.h"
#include "Context.h"
#include "HtmlPage.h"

void WebRegisterRemove::process()
{
	Context* context = Context::getInstance();
	
	cout << "<div class=""file-wrapper"">\n"
        "            <form action=""http://localhost/projeto/ProjectoATC2.exe/RegisterRemove""  method=""post"">\n"
        "                <label for=""number"">Number of student to remove:</label>\n"
        "                <input type=""number"" name=""number"" id=""number"" min = ""0"" required = ""required""><br>\n"
        "                <input type=""reset"">\n"
        "                <input type=""submit"" value=""Submit"">\n"
        "            </form>\n"
        "        </div> \n"
        "    </div>\n"
        "</body>\n"
		"</html>\n";

	if (context->getMethod() == "POST" && context->getBody()) {
		vector<string> vec;
		Parsing::bodyParameter(context->getBody().str(), vec, false);
		cout << HtmlPage::HtmlPageStart("Report");
		try {
			context->getStudents().remove(stoi(vec[0]));
		}
		catch (exception& e) {
			cout << "<div class = ""info-titles""><h6>" << e.what() << "</h6></div>\n";
			return;
		}
		cout << "<div class = ""info-titles""><h6>Student removed successful!</h6></div>\n";
		cout << HtmlPage::HtmlPageEnd();
	}
	context->getStudents().saveToFile("ficheiros\\my\\UC_Students.csv");						            // Guardar no ficheiro os casos bem sucedidos
	context->getShifts().setInfo();
}
