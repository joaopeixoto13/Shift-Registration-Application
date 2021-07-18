#include "WebBookingFind.h"
#include "Context.h"
#include "HtmlPage.h"

void WebBookingFind::process()
{
    Context* context = Context::getInstance();

   cout << "        <div class=""file-wrapper"">\n"
        "            <form action=""http://localhost/projeto/ProjectoATC2.exe/BookingFind""  method=""post"">\n"
        "                <label for=""number"">Number of student to consult:</label>\n"
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
        cout << "<div class = ""info-titles""><h6>" + context->getBooking().find(stoi(vec[0])) + "</h6></div>\n";
        cout << HtmlPage::HtmlPageEnd();
    }
}
