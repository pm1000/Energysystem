//
// Created by philipp on 04.05.21.
//

#ifndef ERZEUGER_SOLAR_H
#define ERZEUGER_SOLAR_H


#include "Erzeuger.h"
#include "time.h"

class Solar : public Erzeuger{
private:
    int hour;
    int hourCount;
    int size;

public:
    Solar(int id, std::string name, int size);
    virtual ~Solar();

    double getLastHourGeneration() override;
};


#endif //ERZEUGER_SOLAR_H
