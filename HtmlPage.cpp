#include "HtmlPage.h"
#include "Context.h"

string HtmlPage::Home()
{
    return
        "Content-type: text/html\r\n\r\n"
        "<html>\n"
        "<head>\n"
        "    <meta charset=""utf-8""/>\n"
        "    <title>Home</title>\n"
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
        "        </div>\n"
        "        <div class=""container-wrapper"">\n"
        "            <div class=""portfolio-items-wrapper"">\n"
        "                <div class=""portfolio-item-wrapper"">\n"
        "                    <div class=""portfolio-img-background"" style=""background-image:url(/projeto/images/registration.jpg)""></div>\n"
        "                    <div class=""img-text-wrapper"">\n"
        "                        <div class=""logo-wrapper"">\n"
        "                            <img src=""/projeto/images/logos/regist.png"">\n"
        "                        </div>\n"
        "                        <div class=""subtitle""><a href=""http://localhost/projeto/ProjectoATC2.exe/register"">Click to Register</a></div>\n"
        "                    </div>\n"
        "                </div>\n"
        "                <div class=""portfolio-item-wrapper"">\n"
        "                    <div class=""portfolio-img-background"" style=""background-image:url(/projeto/images/book.jpg)""></div>\n"
        "                   \n"
        "                    <div class=""img-text-wrapper"">\n"
        "                        <div class=""logo-wrapper"">\n"
        "                            <img src=""/projeto/images/logos/booking.png"">\n"
        "                        </div>\n"
        "                        <div class=""subtitle""><a href=""http://localhost/projeto/ProjectoATC2.exe/booking"">Click to Booking</a></div>\n"
        "                    </div>\n"
        "                </div>\n"
        "                <div class=""portfolio-item-wrapper"">\n"
        "                    <div class=""portfolio-img-background"" style=""background-image:url(/projeto/images/genetate2.jpg)""></div>\n"
        "                    <div class=""img-text-wrapper"">\n"
        "                        <div class=""logo-wrapper"">\n"
        "                            <img src=""/projeto/images/logos/generate.png"">\n"
        "                        </div>\n"
        "                        <div class=""subtitle""><a href=""http://localhost/projeto/ProjectoATC2.exe/generate"">Click to Generate</a></div>\n"
        "                    </div>\n"
        "                </div> \n"
        "                \n"
        "                <div class=""portfolio-item-wrapper"">\n"
        "                    <div class=""portfolio-img-background"" style=""background-image:url(/projeto/images/delete2.jpg)""></div>\n"
        "                   \n"
        "                    <div class=""img-text-wrapper"">\n"
        "                        <div class=""logo-wrapper"">\n"
        "                            <img src=""/projeto/images/logos/delete.png"">\n"
        "                        </div>\n"
        "                        <div class=""subtitle""><a href=""http://localhost/projeto/ProjectoATC2.exe/delete"">Click to Delete</a></div>\n"
        "                    </div>\n"
        "                </div>\n"
        "            </div>\n"
        "        </div>\n"
        "    </div>\n"
        "</body>\n"
        "<script>\n"
        "    const portfolioItems = document.querySelectorAll('.portfolio-item-wrapper')\n"
        "    portfolioItems.forEach(portfolioItem => {\n"
        "        portfolioItem.addEventListener('mouseover', () => {\n"
        "           portfolioItem.childNodes[1].classList.add('img-darken');\n"
        "        })\n"
        "        portfolioItem.addEventListener('mouseout', () => {\n"
        "            portfolioItem.childNodes[1].classList.remove('img-darken');\n"
        "        })\n"
        "    })\n"
        "</script>\n"
        "</html>\n";
}

string HtmlPage::HtmlPageStart(const string& title) {
    return
        "<html>\n"
        "<head>\n"
        "    <meta charset=""utf-8""/>\n"
        "    <title>" + title + "</title>\n"
        "    <link rel=""preconnect"" href=""https://fonts.gstatic.com"">\n"
        "    <link href=""https://fonts.googleapis.com/css2?family=Lato:wght@300&display=swap"" rel=""stylesheet"">\n"
        "    <link rel =""stylesheet"" href=""/projeto/styles.css"">  \n"
        "</head>\n"
        "<body>";
}

string HtmlPage::HtmlPageEnd() {
    return
        "</body>"
        "</html>\n";
}

string HtmlPage::HtmlSuccess(string title)
{
    return"<h1>"+ title +"</h1>"
        "<img src=""/projeto/images/success2.png"" style=""width:1920px"" height=""800px"">\n"
        "</div>\n"
        "</body>\n"
        "</html>\n";
}

string HtmlPage::HtmlError(string title)
{
    return"<h1>" + title + "</h1>"
        "<img src=""/projeto/images/error2.jpg"" style=""width:1920px"" height=""800px"">\n"
        "</div>\n"
        "</body>\n"
        "</html>\n";
}
