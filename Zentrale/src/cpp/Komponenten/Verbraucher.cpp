//
// Created by philipp on 30.04.21.
//

#include "../../header/Komponenten/Verbraucher.h"

Verbraucher::Verbraucher() {}

Verbraucher::Verbraucher(int id, std::string name, std::string type) {
    this->id = id;
    this->name = name;
    this->type = type;
}


Verbraucher::~Verbraucher() {

}

std::string Verbraucher::getType() {
    return type;
}
