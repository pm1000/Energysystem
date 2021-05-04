//
// Created by philipp on 04.05.21.
//

#include "../header/Atom.h"

Atom::Atom(int id, std::string name, double maxGeneration) {
    this->id = id;
    this->name = name;
    this->maximumGeneration = maxGeneration;
    this->completeGeneration = 0;
    this->turnOffPossible = true;
    this->status = true;
    this->type = "Atom";
}

Atom::~Atom() {

}

double Atom::getLastHourGeneration() {
    if (!status) //turned off
        return 0;
    else{
        completeGeneration += maximumGeneration;
        return maximumGeneration;
    }
}