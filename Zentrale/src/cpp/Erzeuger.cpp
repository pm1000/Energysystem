//
// Created by philipp on 30.04.21.
//

#include "../header/Erzeuger.h"

Erzeuger::Erzeuger(std::string type, std::string name) {
    this->name = name;
    this->type = type;
}

Erzeuger::~Erzeuger() {

}

std::string Erzeuger::getType() {
    return "Erzeuger";
}

const std::map<std::string, double> &Erzeuger::getValues() const {
    return Komponente::getValues();
}

void Erzeuger::addNewValue(std::string date, double value) {
    Komponente::addNewValue(date, value);
}

double Erzeuger::getLatestValue() const {
    return Komponente::getLatestValue();
}