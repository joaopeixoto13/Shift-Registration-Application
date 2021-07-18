#include "Context.h"

Context* Context::instance = nullptr;

Context::Context()
	: students(99), blocked(false)
{ }

Context* Context::getInstance()
{
	if (instance == nullptr)
		instance = new Context();
	return instance;
}

void Context::reset()
{
	Context* context = Context::getInstance();
	context->getStudents().clear();
	context->getShiftsInfo().clear();
	context->getShifts().clear();
	context->getBooking().clear();
	context->getBlocked() = false;
}