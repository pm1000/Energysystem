//
// Created by philipp on 04.05.21.
//

#ifndef ERZEUGER_WIND_H
#define ERZEUGER_WIND_H


#include "Erzeuger.h"

class Wind : public Erzeuger{
private:
    int size;

public:
    Wind(int id, std::string name, int size);

    virtual ~Wind();

    double getLastHourGeneration() override;
};


#endif //ERZEUGER_WIND_H
