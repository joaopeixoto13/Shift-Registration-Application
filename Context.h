#include "Students.h"
#include "ShiftsInfo.h"
#include "Shifts.h"
#include "Booking.h"
#ifndef CONTEXT_H
#define CONTEXT_H

class Context
{
	static Context* instance;
	Students students;
	ShiftsInfo shiftsinfo;
	Shifts shifts;
	Booking booking;
	bool blocked;
	string method;
	istringstream body;
	Context();
public:
	static Context* getInstance();
	static void reset();

	Students& getStudents() { return students; }
	ShiftsInfo& getShiftsInfo() { return shiftsinfo; }
	Shifts& getShifts() { return shifts; }
	Booking& getBooking() { return booking; }
	bool& getBlocked() { return blocked; }
	string& getMethod() { return method; }
	istringstream& getBody() { return body; }
};

#endif
