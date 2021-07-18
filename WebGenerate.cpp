#include "WebGenerate.h"
#include "Context.h"
#include "HtmlPage.h"

void WebGenerate::process()
{
	Context* context = Context::getInstance();
	if (!context->getBooking().size() && !context->getShifts().size()) {
		cout << HtmlPage::HtmlError("Error: Cannot generate shitfs!");
		return;
	}
	else if (context->getMethod() == "POST" && context->getBody()) {
		vector<string> vec;
		Parsing::bodyParameter(context->getBody().str(), vec, false);
		if (vec[0] == "Yes") {
			context->getBooking().generateShifts("shifts");
			system("tar.exe -a -c -f shifts.zip shifts");
			system("move /Y shifts.zip ficheiros\\my\\placed");
			string str = "<a href=""/projeto/ficheiros/my/placed/shifts.zip"" download><h2>Click to Download</h2></a><br>";
			cout << str + HtmlPage::HtmlSuccess("");
		}

	}
	else {
		string str;
		if ((context->getBooking().size() + context->getShifts().size()) < context->getStudents().size())
			str = "Warming: Not all students are booked!<br>Do you want to continue?";
		else
			str = "Do you want to continue?";

			cout << "<div class=""file-wrapper"">\n"
			"			<form action=""http://localhost/projeto/ProjectoATC2.exe/generate""  method=""post"">\n"
			"				<label> " + str + " </label><br><br><br>\n"
			"                <div><input name=""submit"" type=""submit"" value=""Yes"">\n</div>\n"
			"            </form>\n"
			"			<form action=""http://localhost/projeto/ProjectoATC2.exe/home"" method=""post"">\n"
			"                <div><input name=""submit"" type=""submit"" value=""No"">\n</div>\n"
			"            </form>\n"
			"        </div>\n"
			"    </div>\n"
			"</body>\n"
			"</html>\n";
	}
}
