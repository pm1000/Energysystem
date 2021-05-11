//
// Created by philipp on 30.04.21.
//

#ifndef VERBRAUCHER_SIMULATOR_H
#define VERBRAUCHER_SIMULATOR_H

#include "Verbraucher.h"
#include "iostream"
#include "unistd.h"
#include "thread"
#include "UDPKommunikation.h"
#include "ZentralenKommunikation.h"
#include <chrono>

using namespace std;


/**
 *
 */
class Simulator {

private:
    Verbraucher* verbraucher;
    UDPKommunikation* interface;
    string messageToJSON(string type, string name, int id, double value, unsigned long long time);
    void simulate();

    bool stopped = false;

public:
    Simulator(Verbraucher *verbraucher, string communicationType, int port, string address);
    virtual ~Simulator();

    void start();
    void stop();
};


#endif //VERBRAUCHER_SIMULATOR_H
