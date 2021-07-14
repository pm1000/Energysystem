//
// Created by philipp on 04.05.21.
//

#include "../../header/Komponente/Kohle.h"


/**
 *
 */
Kohle::Kohle(int id, string name, double maximumGeneration){
    this->id = id;
    this->name = name;
    this->maximumGeneration = maximumGeneration;
    this->status = true;
    this->completeGeneration = 0;
    this->type = "Kohle";
}



/**
 *
 */
Kohle::~Kohle() = default;



/**
 *
 */
double Kohle::getLastHourGeneration() {
    if (!status)
        return 0;
    else{
        completeGeneration += maximumGeneration;
        return maximumGeneration;
    }
}
