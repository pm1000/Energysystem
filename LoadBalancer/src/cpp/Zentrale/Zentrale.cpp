//
// Created by philipp on 05.07.21.
//

#include "../../header/Zentrale/Zentrale.h"

int Zentrale::count = 0;

Zentrale::Zentrale(const string &ip, const string &name) {
    this->ip = ip;
    this->id = count;
    this->name = name;
    ++count;
}

Zentrale::~Zentrale() {

}
