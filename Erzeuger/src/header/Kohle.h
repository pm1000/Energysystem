//
// Created by philipp on 04.05.21.
//

#ifndef ERZEUGER_KOHLE_H
#define ERZEUGER_KOHLE_H


#include "Erzeuger.h"

class Kohle : public  Erzeuger{
private:
    double maximumGeneration;

public:
    Kohle(int id, std::string name, double maximumGeneration);
    virtual ~Kohle();

    double getLastHourGeneration() override;
};


#endif //ERZEUGER_KOHLE_H
