//
// Created by philipp on 30.04.21.
//

#include "../../header/Komponenten/Komponente.h"

Komponente::Komponente() {}

Komponente::~Komponente() {

}

const std::map<unsigned long long, double> &Komponente::getValues() const {
    return values;
}

void Komponente::addNewValue(unsigned long long timestamp, double value) {
    mtx.lock();
    if (this->values.find(timestamp) == this->values.end())
        this->values.insert({timestamp,value});
    mtx.unlock();
}


double Komponente::getLatestValue() const {
    //todo
    return this->values.begin()->second;
}

const std::string &Komponente::getName() const {
    return name;
}

int Komponente::getId() const {
    return id;
}



/**
 *
 */
std::string Komponente::getIp() const {
    return this->ip;
}

