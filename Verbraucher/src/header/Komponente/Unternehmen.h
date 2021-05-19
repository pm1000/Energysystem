//
// Created by philipp on 30.04.21.
//

#ifndef VERBRAUCHER_UNTERNEHMEN_H
#define VERBRAUCHER_UNTERNEHMEN_H

#include "Verbraucher.h"

using namespace std;

/**
 *
 */
class Unternehmen : public Verbraucher {
private:
    int consumptionSeed;

public:
    Unternehmen(int id, string name);
    ~Unternehmen() override;

    double getLastHourConsumption() override;
    double getCompleteConsumption() const override;
    string getType() override;
};


#endif //VERBRAUCHER_UNTERNEHMEN_H
