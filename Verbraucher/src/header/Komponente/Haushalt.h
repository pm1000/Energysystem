//
// Created by philipp on 30.04.21.
//

#ifndef VERBRAUCHER_HAUSHALT_H
#define VERBRAUCHER_HAUSHALT_H

#include "Verbraucher.h"

using namespace std;

/**
 *
 */
class Haushalt : public Verbraucher {
private:

public:
    Haushalt(int id, string name);
    ~Haushalt() override;

    double getLastHourConsumption() override;
    double getCompleteConsumption() const override;
    string getType() override;
};


#endif //VERBRAUCHER_HAUSHALT_H
