//
// Created by philipp on 05.05.21.
//

#ifndef ZENTRALE_HTMLGENERATOR_H
#define ZENTRALE_HTMLGENERATOR_H


#include "../Komponenten/KomponentenController.h"
#include "string"
#include "algorithm"

using std::string;

class HTMLGenerator {
private:
    KomponentenController* komponentenController;

    string generateHeader();
    string openBody();
    string closeBody();
    string generateMainTab();
    string generateTableHead(string type);
    string closeTable();
    string generateTableRow(string type, string name, int id, double value, unsigned long long time);
    string generateSubTabs(string type);
public:

    HTMLGenerator();
    virtual ~HTMLGenerator();

    string generateMainPage();

};


#endif //ZENTRALE_HTMLGENERATOR_H
