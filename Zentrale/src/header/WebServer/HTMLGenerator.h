//
// Created by philipp on 05.05.21.
//

#ifndef ZENTRALE_HTMLGENERATOR_H
#define ZENTRALE_HTMLGENERATOR_H


#include "../Komponenten/KomponentenController.h"

class HTMLGenerator {
private:
    KomponentenController* komponentenController;

public:

    HTMLGenerator(KomponentenController* komponentenController);
    virtual ~HTMLGenerator();

};


#endif //ZENTRALE_HTMLGENERATOR_H
