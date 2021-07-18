#include "Factory.h"
#include "Home.h"
#include "About.h"
#include "WebRegister.h"
#include "WebBooking.h"
#include "WebGenerate.h"
#include "WebDelete.h"
#include "WebRegisterFile.h"
#include "WebRegisterManual.h"
#include "WebRegisterRemove.h"
#include "WebRegisterShiftsFile.h"
#include "WebRegisterShiftsManual.h"
#include "WebRegisterShiftsManual1.h"
#include "WebRegisterShiftsManual2.h"
#include "WebBookingConsult.h"
#include "WebBookingFile.h"
#include "WebBookingFind.h"
#include "WebBookingManual.h"
#include "WebBookingRemove.h"
#include "Dummy.h"

AbstractMenu* Factory::create(string uri)
{
	AbstractMenu* menu = nullptr;

	if (uri == "/projeto/ProjectoATC2.exe/home" || uri == "/projeto/ProjectoATC2.exe")
		menu = new Home;
	else if (uri == "/projeto/ProjectoATC2.exe/about")
		menu = new About;
	else if (uri == "/projeto/ProjectoATC2.exe/register")
		menu = new WebRegister;
	else if (uri == "/projeto/ProjectoATC2.exe/booking")
		menu = new WebBooking;
	else if (uri == "/projeto/ProjectoATC2.exe/generate")
		menu = new WebGenerate;
	else if (uri == "/projeto/ProjectoATC2.exe/delete")
		menu = new WebDelete;
	else if (uri == "/projeto/ProjectoATC2.exe/RegisterFile")
		menu = new WebRegisterFile;
	else if (uri == "/projeto/ProjectoATC2.exe/RegisterShiftsFile")
		menu = new WebRegisterShiftsFile;
	else if (uri == "/projeto/ProjectoATC2.exe/RegisterManual")
		menu = new WebRegisterManual;
	else if (uri == "/projeto/ProjectoATC2.exe/RegisterShiftsManual")
		menu = new WebRegisterShiftsManual;
	else if (uri == "/projeto/ProjectoATC2.exe/RegisterShiftsManual1")
		menu = new WebRegisterShiftsManual1;
	else if (uri == "/projeto/ProjectoATC2.exe/RegisterShiftsManual2")
		menu = new WebRegisterShiftsManual2;
	else if (uri == "/projeto/ProjectoATC2.exe/RegisterRemove")
		menu = new WebRegisterRemove;
	else if (uri == "/projeto/ProjectoATC2.exe/BookingFile")
		menu = new WebBookingFile;
	else if (uri == "/projeto/ProjectoATC2.exe/BookingManual")
		menu = new WebBookingManual;
	else if (uri == "/projeto/ProjectoATC2.exe/BookingFind")
		menu = new WebBookingFind;
	else if (uri == "/projeto/ProjectoATC2.exe/BookingRemove")
		menu = new WebBookingRemove;
	else if (uri == "/projeto/ProjectoATC2.exe/BookingConsult")
		menu = new WebBookingConsult;
	else
		menu = new Dummy;
	return menu;
}
