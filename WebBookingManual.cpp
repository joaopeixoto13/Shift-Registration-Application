#include "WebBookingManual.h"
#include "Context.h"
#include "HtmlPage.h"

void WebBookingManual::process()
{
    Context* context = Context::getInstance();
    string str;
    string line = context->getShiftsInfo().info();
    string token;
    int index = 0;

    for (int i = 0; i < line.size(); i++)
    {
        if (line[i] == '\n')
            line[i] = ' ';
    }
    stringstream ss(line);
    string optionnames;
    while (getline(ss, token, ' '))
    {
        index &= 3;
        if (index == 0)
            optionnames += "<option value=""" + token + """>" + token + "</option>\n";
        index++;
    }
    for (int i = 0; i < context->getShiftsInfo().size(); i++) {
        str += "                <label for="""">Insert your " + to_string(i + 1) + "º preference : </label>\n"
            "                <select name=""S"" id=""S"" required = ""required"">\n"
            + optionnames +
            "                </select><br><br>\n";
    }

    cout <<  "        <div class=""file-wrapper"">\n"
            "            <form action=""http://localhost/projeto/ProjectoATC2.exe/BookingManual""  method=""post"">\n"
            "                <label for=""number"">Number:</label>\n"
            "                <input type=""number"" name=""number"" id=""number"" min = ""0"" required = ""required""><br>\n"
        + str +
        "                <input type=""reset"">\n"
        "                <input type=""submit"" value=""Submit"">\n"
        "            </form>\n"
        "        </div> \n"
        "    </div>\n"
        "</body>\n"
        "</html>\n";

    if (context->getMethod() == "POST" && context->getBody()) {
        string date = "";
        list<int> preferences;
        cout << HtmlPage::HtmlPageStart("Report");
        vector<string> vec;
        Parsing::bodyParameter(context->getBody().str(), vec, false);
        for (int i = 1; i < vec.size(); i++)
            preferences.push_back(context->getShiftsInfo().index(vec[i]));
        int x;
        Book a(date, stoi(vec[0]), preferences);
        int y = context->getBooking().add(a, x);
        if (y >= 0)
            cout << "<div class = ""info-titles""><h6>Student " + vec[0] + " not exist!</h6></div>\n";
        else if (y == -1)
            cout << "<div class = ""info-titles""><h6>Student " + vec[0] + " not placed!</h6></div>\n";
        else if (y == -2)
            cout << "<div class = ""info-titles""><h6>Student " + vec[0] + " was placed in shift " + to_string(x + 1) + "!</h6></div>\n";
        else if (y == -3)
            cout << "<div class = ""info-titles""><h6>Student " + vec[0] + " was booked!</h6></div>\n";
        cout << HtmlPage::HtmlPageEnd();
        context->getBooking().saveToFile("ficheiros\\my\\Booking.csv");
        context->getShifts().saveToFile("ficheiros\\my\\placed\\");
    }
}
