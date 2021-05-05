//
// Created by philipp on 30.04.21.
//
#ifndef ZENTRALE_ERZEUGER_H
#define ZENTRALE_ERZEUGER_H

#include "Komponente.h"

class Erzeuger : public Komponente{

public:

    Erzeuger(std::string type, std::string name, int id);
    ~Erzeuger();

    std::string getType() override;

};


#endif //ZENTRALE_ERZEUGER_H
