//
// Created by philipp on 30.04.21.
//

#include "../header/Erzeuger.h"

Erzeuger::Erzeuger(std::string type, std::string name, int id) {
    this->name = name;
    this->type = type;
    this->id = id;
}

Erzeuger::~Erzeuger() {

}

std::string Erzeuger::getType() {
    return type;
}
