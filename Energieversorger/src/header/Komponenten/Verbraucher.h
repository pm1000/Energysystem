//
// Created by philipp on 02.06.21.
//

#ifndef ENERGIEVERSORGER_VERBRAUCHER_H
#define ENERGIEVERSORGER_VERBRAUCHER_H


#include "Komponente.h"

class Verbraucher : public Komponente {
public:
    Verbraucher();
    Verbraucher(int id, std::string name, std::string type);

    virtual ~Verbraucher();

    std::string getType() override;
};


#endif //ENERGIEVERSORGER_VERBRAUCHER_H
