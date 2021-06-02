//
// Created by philipp on 02.06.21.
//

#ifndef ENERGIEVERSORGER_ERZEUGER_H
#define ENERGIEVERSORGER_ERZEUGER_H

#include "Komponente.h"

class Erzeuger : public Komponente{

    Erzeuger(std::string type, std::string name, int id);
    ~Erzeuger();

    virtual std::string getType() override;
};


#endif //ENERGIEVERSORGER_ERZEUGER_H
