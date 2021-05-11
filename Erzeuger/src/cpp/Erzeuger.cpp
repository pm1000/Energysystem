//
// Created by philipp on 04.05.21.
//

#include "../header/Erzeuger.h"


/**
 *
 */
Erzeuger::~Erzeuger() {

}



/**
 *
 */
double Erzeuger::getCompleteGeneration() const {
    return this->completeGeneration;
}



/**
 *
 */
int Erzeuger::getID() const {
    return this->id;
}



/**
 *
 */
string Erzeuger::getName() const {
    return this->name;
}



/**
 *
 */
bool Erzeuger::isTurnOffPossible() const {
    return turnOffPossible;
}



/**
 *
 */
bool Erzeuger::isStatus() const {
    return status;
}



/**
 *
 */
void Erzeuger::switchStatus() {
    if (this->turnOffPossible)
        this->status = !this->status;
}



/**
 *
 */
string Erzeuger::getType() {
    return type;
}
