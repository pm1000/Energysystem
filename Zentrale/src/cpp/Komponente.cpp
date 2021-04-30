//
// Created by philipp on 30.04.21.
//

#include "../header/Komponente.h"

Komponente::Komponente() {}

Komponente::~Komponente() {

}

const std::map<std::string, double> &Komponente::getValues() const {
    return values;
}

void Komponente::addNewValue(std::string date, double value) {
    if (this->values.find(date) == this->values.end())
        this->values.insert({date,value});
}

double Komponente::getLatestValue() const {
    //todo
    return this->values.begin()->second;
}

const std::string &Komponente::getName() const {
    return name;
}

