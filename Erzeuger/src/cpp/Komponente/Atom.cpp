//
// Created by philipp on 04.05.21.
//

#include "../../header/Komponente/Atom.h"


/**
 *
 */
Atom::Atom(int id, string name, double maxGeneration) {
    this->id = id;
    this->name = name;
    this->maximumGeneration = maxGeneration;
    this->completeGeneration = 0;
    this->status = true;
    this->type = "Atom";
}



/**
 *
 */
Atom::~Atom() = default;



/**
 *
 */
double Atom::getLastHourGeneration() {
    if (!status) //turned off
        return 0;
    else {
        completeGeneration += maximumGeneration;
        return maximumGeneration;
    }
}

double Atom::getMaximumGeneration() const {
    return maximumGeneration;
}
