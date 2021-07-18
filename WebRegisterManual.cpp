#include "WebRegisterManual.h"
#include "Context.h"
#include "HtmlPage.h"

void WebRegisterManual::process()
{
	Context* context = Context::getInstance();
	
	cout << "        <div class=""file-wrapper"">\n"
                "            <form action=""http://localhost/projeto/ProjectoATC2.exe/RegisterManual""  method=""post"">\n"
                "                <label for=""number"">Number:</label>\n"
                "                <input type=""number"" name=""number"" id=""number"" min = ""0"" required = ""required""><br>\n"
                "                <label for=""name"">Name:  </label>\n"
                "                <input type=""text"" name=""name"" id=""name"" pattern=""[a-z A-Z]"" required = ""required""><br>\n"
                "                <label for=""EE"">Special Status:</label>\n"
                "                <select name=""EE"" id=""EE"" required = ""required"">\n"
                "                <option value="""">None</option>\n"
                "                <option value=""TE"">TE</option>\n"
                "                <option value=""AAC"">AAC</option>\n"
                "                <option value=""DAE"">DAE</option>\n"
                "                <option value=""PDEF"">PDEF</option>\n"
                "                <option value=""DLG"">DLG</option>\n"
                "                </select><br><br>\n"
                "                <input type=""reset"">\n"
                "                <input type=""submit"" value=""Submit"">\n"
                "            </form>\n"
                "        </div> \n"
                "    </div>\n"
                "</body>\n"
        "</html>\n";

	if (context->getMethod() == "POST" && context->getBody()) {
		cout << HtmlPage::HtmlPageStart("Report");
		vector<string> vec;
		Parsing::bodyParameter(context->getBody().str(), vec, false);
		if (vec.size() == 2)
			vec.push_back("");
		Student st(stoi(vec[0]), vec[1], Student::statusInt(vec[2]));
		context->getStudents().add(st);
		context->getStudents().reportStudentsHtml();
		cout << HtmlPage::HtmlPageEnd();
	}
	context->getStudents().saveToFile("ficheiros\\my\\UC_Students.csv");						            // Guardar no ficheiro os casos bem sucedidos
	context->getShifts().setInfo();
}
