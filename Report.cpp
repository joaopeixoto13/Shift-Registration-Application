#include "Report.h"

ostream& operator<<(ostream& os, const Error& error)
{
	os << "Line: " << std::setw(3) << error.line << " -> Reason: " << error.fail;
	return os;
}

ostream& operator<<(ostream& os, const feedBack& feedback)
{
	os << "Line: " << std::setw(3) << feedback.line << " -> Reason: " << feedback.info;
	return os;
}
