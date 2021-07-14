//
// Created by philipp on 30.04.21.
//

#ifndef ZENTRALE_VERBRAUCHER_H
#define ZENTRALE_VERBRAUCHER_H


#include "Komponente.h"

class Verbraucher : public Komponente{
public:
    Verbraucher();
    Verbraucher(int id, std::string name, std::string type);

    virtual ~Verbraucher();

    std::string getType() override;

};


#endif //ZENTRALE_VERBRAUCHER_H
