#include "WebRegisterShiftsFile.h"
#include "Context.h"
#include "HtmlPage.h"

void WebRegisterShiftsFile::process()
{
	Context* context = Context::getInstance();

	cout << "        <div class=""file-wrapper"">\n"
        "            <form action=""http://localhost/projeto/ProjectoATC2.exe/RegisterShiftsFile""  method=""post"" enctype=""multipart/form-data"">\n"
        "                <label>Select file with shifts:</label><br><br><br>\n"
        "                <input type=""file"" name=""StudentsFile"" id=""StudentsFile"" required = ""required""><br>\n"
        "                <input type=""reset"">\n"
        "                <input type=""submit"" value=""Submit"">\n"
        "            </form>\n"
        "        </div> \n"
        "    </div>\n"
        "</body>\n"
		"</html>\n";

	if (context->getMethod() == "POST" && context->getBody()) {
		context->getShiftsInfo().clear();
		cout << HtmlPage::HtmlPageStart("Report");
		try {
			context->getShiftsInfo().readFromBody(context->getBody());
		}
		catch (invalid_argument& e) {
			cout << "<div class = ""info-titles""><h6>" << e.what() << "</h6></div>\n";
			return;
		}
		cout << "<div class = ""info-titles""><h5>Shifts loaded with success!</h5></div>\n";
		cout << HtmlPage::HtmlPageEnd();
		context->getShiftsInfo().saveToFile("ficheiros\\my\\ShiftsInformation.csv");
	}
	context->getStudents().saveToFile("ficheiros\\my\\UC_Students.csv");						            // Guardar no ficheiro os casos bem sucedidos
	context->getShifts().setInfo();
}
