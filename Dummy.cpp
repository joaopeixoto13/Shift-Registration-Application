#include "Dummy.h"
#include "HtmlPage.h"

void Dummy::process()
{
	cout << HtmlPage::HtmlError("Error: Unknown Order!");
}
