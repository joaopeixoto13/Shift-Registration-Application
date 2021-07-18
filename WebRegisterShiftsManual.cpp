#include "WebRegisterShiftsManual.h"

void WebRegisterShiftsManual::process()
{
    cout << "        <div class=""file-wrapper"">\n"
        "            <form action=""http://localhost/projeto/ProjectoATC2.exe/RegisterShiftsManual1""  method=""POST"">\n"
        "               <label for=""name"">Name for shifts</label>\n"
        "               <input type=""name"" name=""name"" id=""name"" pattern=""[a-z A-Z]"" required = ""required""><br>\n"
        "               <label for=""number"">Number of shifts</label>\n"
        "               <input type=""number"" name=""number"" id=""number"" min=""0"" required = ""required""><br>\n"
        "                <input type=""reset"">\n"
        "                <input type=""submit"" value=""Submit"">\n"
        "            </form>\n"
        "        </div> \n"
        "    </div>\n"
        "</body>\n"
        "</html>\n";
}
