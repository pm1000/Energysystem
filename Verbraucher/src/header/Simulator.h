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

class Simulator {

private:
    Verbraucher* verbraucher;
    UDPKommunikation* interface;
    std::string messageToJSON(std::string type, std::string name, int id, double value, unsigned long long time);
    void simulate();
public:
    Simulator(Verbraucher *verbraucher, std::string communicationType, int port, std::string address);

    virtual ~Simulator();

    void start();

};


#endif //VERBRAUCHER_SIMULATOR_H
