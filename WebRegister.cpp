#include "WebRegister.h"
#include "Context.h"
#include "HtmlPage.h"

string StudentsTable()
{
    Context* context = Context::getInstance();
    list<Student>elements = context->getStudents().elements();
    string output;

    for (Student st : elements)
        output += "<tr>\n<td>" + to_string(st._number()) + "</td>\n<td>" + st._name() + "</td>\n<td>" + st._EE() + "</td>\n</tr>\n";

    return output;
}

string ShiftsTable()
{
    Context* context = Context::getInstance();
    string line = context->getShiftsInfo().info();
    string token, output, aux;
    int index = 0;

    for (int i = 0; i < line.size(); i++)
    {
        if (line[i] == '\n')
            line[i] = ' ';
    }

    stringstream ss(line);

    while (getline(ss, token, ' '))
    {
        index &= 3;
        if (index == 0)
            aux = token;
        if (index == 2)
        {
            output += "<tr>\n<td>" + aux + "</td>\n<td>" + token + "</td>\n</tr>\n";
            aux = "";
        }
        index++;
    }
    return output;
}

void WebRegister::process()
{
	Context* context = Context::getInstance();
	if (context->getBlocked() == true) {
        cout << HtmlPage::HtmlError("Error: Booking was inicialized!");
		return;
	}
	cout << "        <div class=""container-wrapper"">\n"
        "            <div class=""register-wrapper"">\n"
        "                <div class=""options-wrapper"">\n"
        "                    <div class=""option-wrapper""><a href=""http://localhost/projeto/ProjectoATC2.exe/RegisterFile"">Insert one file with UC Students</a></div>\n"
        "                    <div class=""option-wrapper""><a href=""http://localhost/projeto/ProjectoATC2.exe/RegisterManual"">Insert one student manually</a></div>\n"
        "                    <div class=""option-wrapper""><a href=""http://localhost/projeto/ProjectoATC2.exe/RegisterShiftsFile"">Insert one file with shifts information</a></div>\n"
        "                    <div class=""option-wrapper""><a href=""http://localhost/projeto/ProjectoATC2.exe/RegisterShiftsManual"">Insert shifts manually</a></div>\n"
        "                    <div class=""option-wrapper""><a href=""http://localhost/projeto/ProjectoATC2.exe/RegisterRemove"">Remove one student</a></div>\n"
        "                </div>\n"
        "                <div class=""info-tables-wrapper"">\n"
        "                    <div class=""info-titles""><h3>Shifts Information</h3></div>\n"
        "                    <div class=""info-wrapper"">\n"
        "                        <table>\n"
        "                            <thead>"
        "                            <tr>\n"
        "                            <th>Name</th>\n"
        "                            <th>Places</th>\n"
        "                            </tr>\n"
        "                            </thead>"
        "                            <tbody>"
        + ShiftsTable() +
        "                            </tbody>"
        "                        </table>\n"
        "                    </div>\n"
        "                    <div class=""info-titles""><h3>Students Information</h3></div>\n"
        "                    <div class=""info-wrapper"">\n"
        "                        <table>\n"
        "                            <thead>"
        "                            <tr>\n"
        "                            <th>Number</th>\n"
        "                            <th>Name</th>\n"
        "                            <th>SpecialStatus</th>\n"
        "                            </tr>\n"
        "                            </thead>"
        "                            <tbody>"
        + StudentsTable() +
        "                            </tbody>"
        "                        </table>\n"
        "                    </div>\n"
        "                </div>\n"
        "            </div>\n"
        "        </div> \n"
        "    </div>\n"
        "</body>\n"
        "</html>\n";

}
