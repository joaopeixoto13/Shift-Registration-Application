#pragma once
#include <string>
using namespace std;

class HtmlPage
{
public:
	static string Home();
	static string HtmlPageStart(const string& title);
	static string HtmlPageEnd();
	static string HtmlSuccess(string title);
	static string HtmlError(string title);
};

