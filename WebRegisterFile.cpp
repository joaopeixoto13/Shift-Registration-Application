#include "WebRegisterFile.h"
#include "Context.h"
#include "HtmlPage.h"

void WebRegisterFile::process()
{
	Context* context = Context::getInstance();
	
	cout << "        <div class=""file-wrapper"">\n"
        "            <form action=""http://localhost/projeto/ProjectoATC2.exe/RegisterFile""  method=""post"" enctype=""multipart/form-data"">\n"
        "                <label>Select file with UC students:</label><br><br><br>\n"
        "                <input type=""file"" name=""StudentsFile"" id=""StudentsFile"" required = ""required""><br>\n"
        "                <input type=""reset"">\n"
        "                <input type=""submit"" value=""Submit"">\n"
        "            </form>\n"
        "        </div> \n"
        "    </div>\n"
        "</body>\n"
		"</html>\n";

	if (context->getMethod() == "POST" && context->getBody()) {
		cout << HtmlPage::HtmlPageStart("Report");
		try {
			context->getStudents().readFromBody(context->getBody());
		}
		catch (invalid_argument& e) {
			cout << "<div class = ""info-titles""><h6>" << e.what() << "</h6></div>\n";
			return;
		}
		catch (runtime_error& e) {
			cout << "<div class = ""info-titles""><h6>" << e.what() << "</h6></div>\n";
		}
		context->getStudents().reportStudentsHtml();
		cout << HtmlPage::HtmlPageEnd();
	}
	context->getStudents().saveToFile("ficheiros\\my\\UC_Students.csv");
	context->getShifts().setInfo();
}
