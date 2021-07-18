#include "WebRegisterShiftsManual1.h"
#include "Context.h"

void WebRegisterShiftsManual1::process()
{
	Context* context = Context::getInstance();
	if (context->getMethod() == "POST" && context->getBody())
	{
		vector<string>vec;
		string shiftsName, str;
		int max_elements = 0;
		context->getShiftsInfo().clear();
		Parsing::bodyParameter(context->getBody().str(), vec, false);
		shiftsName = vec[0];
		shiftsName.erase(remove_if(shiftsName.begin(), shiftsName.end(), isspace), shiftsName.end());
		max_elements = stoi(vec[1]);
		for (int i = 1; i <= max_elements; i++)
		{
			str += "<label for = ""name"">" + shiftsName + to_string(i) + "</label>\n";
			str += "<input type=""number"" name=""" + shiftsName + to_string(i) + """ id=""" + shiftsName + to_string(i) + """ min=""1"" required = ""required""><br>\n";
		}
		str += " <input type=""reset"">\n <input type=""submit"" value=""Submit"">\n";
		
		cout << "        <div class=""file-wrapper"">\n"
        "            <div class = ""info-titles""><h4>Number of places:</h4></div>\n"
        "            <form action=""http://localhost/projeto/ProjectoATC2.exe/RegisterShiftsManual2""  method=""POST"">\n"
		+ str +
		"            </form>\n"
		"        </div> \n"
		"    </div>\n"
		"</body>\n"
		"</html>\n";
	}
}
