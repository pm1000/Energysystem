//
// Created by philipp on 04.05.21.
//

#ifndef ERZEUGER_ATOM_H
#define ERZEUGER_ATOM_H


#include "Erzeuger.h"

using namespace std;

/**
 *
 */
class Atom : public Erzeuger {
private:
    double maximumGeneration;

public:
    Atom(int id, string name, double maxGeneration);
    virtual ~Atom();

    double getLastHourGeneration() override;
    double getMaximumGeneration() const;
};


#endif //ERZEUGER_ATOM_H
