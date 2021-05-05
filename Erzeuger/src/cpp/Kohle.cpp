//
// Created by philipp on 04.05.21.
//

#include "../header/Kohle.h"

Kohle::Kohle(int id, std::string name, double maximumGeneration){
    this->id = id;
    this->name = name;
    this->maximumGeneration = maximumGeneration;
    this->turnOffPossible = true;
    this->status = true;
    this->completeGeneration = 0;
    this->type = "Kohle";
}

Kohle::~Kohle() {

}

double Kohle::getLastHourGeneration() {
    if (!status)
        return 0;
    else{
        completeGeneration += maximumGeneration;
        return maximumGeneration;
    }
}