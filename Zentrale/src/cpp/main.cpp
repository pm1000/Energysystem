#include <iostream>
#include "../header/Zentrale.h"
#include "../header/WebServer/HTMLGenerator.h"


int main() {

    // Create the Zentrale and start the execution of code.
    HTMLGenerator html;
    string s = html.generateMainPage();
    Zentrale zentrale;
    zentrale.start();
    return 0;
}
