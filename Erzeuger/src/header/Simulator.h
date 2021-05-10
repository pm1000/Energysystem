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

using namespace std;

/**
 *
 */
class Simulator {
private:
    Erzeuger* erzeuger;
    UDPKommunikation* interface;
    string messageToJSON(string type, string name, int id, double value, unsigned long long t);
    void simulate();
    bool stopped = false;

public:
    Simulator(Erzeuger *erzeuger, string communicationType, int port, string address);
    virtual ~Simulator();

    void start();
    void stop();
};


#endif //ERZEUGER_SIMULATOR_H
