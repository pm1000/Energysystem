//
// Created by philipp on 30.04.21.
//

#include "../header/Verbraucher.h"

Verbraucher::~Verbraucher() = default;

int Verbraucher::getId() const {
    return id;
}

double Verbraucher::getCompleteConsumption() const{
    return this->completeConsumption;
}

