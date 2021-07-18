#include "WebDelete.h"
#include "Context.h"
#include "Clear.h"
#include "HtmlPage.h"

void WebDelete::process()
{
	Context* context = Context::getInstance();
	context->getBlocked() = false;
	Clear::removeLoadFiles();
	Context::reset();
	cout << HtmlPage::HtmlSuccess("Data deleted successful!");
}
