//
// Created by philipp on 30.04.21.
//

#ifndef VERBRAUCHER_HAUSHALT_H
#define VERBRAUCHER_HAUSHALT_H

#include "Verbraucher.h"

class Haushalt : public Verbraucher{

public:
    Haushalt(int id);

    ~Haushalt() override;

    double getLastHourConsumption() override;

    double getCompleteConsumption() const override;

    std::string getType() override;
};


#endif //VERBRAUCHER_HAUSHALT_H
