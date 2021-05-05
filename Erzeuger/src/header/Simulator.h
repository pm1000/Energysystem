//
// Created by philipp on 04.05.21.
//

#ifndef ERZEUGER_SIMULATOR_H
#define ERZEUGER_SIMULATOR_H

#include "Erzeuger.h"
#include "iostream"
#include "unistd.h"
#include "thread"
#include "UDPKommunikation.h"
#include "ZentralenKommunikation.h"

class Simulator {

private:
    Erzeuger* erzeuger;
    UDPKommunikation* interface;
    std::string messageToJSON(std::string type, std::string name, int id, double value, unsigned long long t);
    void simulate();
public:
    Simulator(Erzeuger *erzeuger, std::string communicationType, int port, std::string address);

    virtual ~Simulator();

    void start();

};


#endif //ERZEUGER_SIMULATOR_H
