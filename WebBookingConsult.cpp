#include "WebBookingConsult.h"
#include "Context.h"

void WebBookingConsult::process()
{
    Context* context = Context::getInstance();
    string str = "<h3>---------------BOOKING INFORMATION------------------</h3><br><br>"
        "<h6>Total booked students : " + to_string(context->getBooking().size()) + "</h6><br>"
        "<h6>Students already placed (with priority) :" + to_string(context->getShifts().size()) + "</h6><br>"
        "<h6>Total number of shifts places : " + to_string(context->getShiftsInfo().totalPlaces()) + "</h6><br>"
        "<h6>Number of places available (without appointments) : " + to_string(context->getShiftsInfo().totalPlaces() - context->getShifts().size()) + "</h6><br>";
    cout << "<div class = ""info-titles"">" + str + "</div>\n"
        "    </div>\n"
        "</body>\n"
        "</html>\n";
}
