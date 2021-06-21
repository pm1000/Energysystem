//
// Created by philipp on 30.04.21.
//

#include "../../header/Komponenten/Erzeuger.h"

Erzeuger::Erzeuger(std::string type, std::string name, int id, bool status) {
    this->name = name;
    this->type = type;
    this->id = id;
    this->status = status;
}

Erzeuger::~Erzeuger() {

}

std::string Erzeuger::getType() {
    return type;
}

bool Erzeuger::isStatus() const {
    return status;
}
