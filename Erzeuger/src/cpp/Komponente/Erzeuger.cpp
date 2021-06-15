//
// Created by philipp on 04.05.21.
//

#include "../../header/Komponente/Erzeuger.h"


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
bool Erzeuger::isStatus() const {
    return status;
}



/**
 *
 */
void Erzeuger::switchStatus() {
    this->status = !this->status;

    if (this->status)
        cout << "Kraftwerk wurde angeschaltet." << endl;
    else
        cout << "Kraftwerk wurde ausgeschaltet." << endl;
}


/**
 *
 */
string Erzeuger::getType() {
    return type;
}
