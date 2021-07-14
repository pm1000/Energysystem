//
// Created by philipp on 02.06.21.
//

#include "../../header/Komponenten/Erzeuger.h"

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