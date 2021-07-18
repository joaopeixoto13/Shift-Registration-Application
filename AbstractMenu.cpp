#include "AbstractMenu.h"

void AbstractMenu::method()
{
    cout << "Content-type: text/html\r\n\r\n"
            "<html>\n"
            "<head>\n"
            "    <meta charset=""utf-8""/>\n"
            "    <title>ATC2</title>\n"
            "    <link rel=""preconnect"" href=""https://fonts.gstatic.com"">\n"
            "    <link href=""https://fonts.googleapis.com/css2?family=Lato:wght@300&display=swap"" rel=""stylesheet"">\n"
            "    <link rel =""stylesheet"" href=""/projeto/styles.css"">\n"
            "</head>\n"
            "<body>\n"
            "    <div class=""container"">\n"
            "        <div class=""nav-wrapper"">\n"
            "            <div class=""left-side"">\n"
            "                <div class=""nav-link-wrapper active-nav-link"">\n"
            "                    <a href=""http://localhost/projeto/ProjectoATC2.exe/home"">Home</a>\n"
            "                </div>\n"
            "                <div class=""nav-link-wrapper"">\n"
            "                    <a href=""http://localhost/projeto/ProjectoATC2.exe/about"">About</a>\n"
            "                </div>\n"
            "            </div>\n"
            "           <div class=""right-side"">\n"
            "               <div class=""brand"">\n"
            "                    <div>ATC2 PROJECT</div>\n"
            "               </div>\n"
            "           </div>\n"
            "        </div>\n";
    process();
}
