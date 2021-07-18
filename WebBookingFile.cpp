#include "WebBookingFile.h"
#include "Context.h"
#include "HtmlPage.h"

void WebBookingFile::process()
{
    Context* context = Context::getInstance();
    
    cout <<  "        <div class=""file-wrapper"">\n"
                "            <form action=""http://localhost/projeto/ProjectoATC2.exe/BookingFile""  method=""post"" enctype=""multipart/form-data"">\n"
                "                <label>Select file with books:</label><br><br><br>\n"
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
            context->getBooking().readFromBody(context->getBody());
        }
        catch (invalid_argument& e) {
            cout << "<div class = ""info-titles""><h6>" << e.what() << "</h6></div>\n";
            return;
        }
        catch (runtime_error& e) {
            cout << "<div class = ""info-titles""><h6>" << e.what() << "</h6></div>\n";
        }
        context->getBooking().ReportBookHtml();
        cout << HtmlPage::HtmlPageEnd();
        context->getBooking().saveToFile("ficheiros\\my\\Booking.csv");
        context->getShifts().saveToFile("ficheiros\\my\\placed\\");
    }
}
