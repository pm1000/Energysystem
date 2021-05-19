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
#include "unordered_map"

using namespace std;


/**
 *
 */
class Simulator {

private:
    unordered_map<int,string> msgBuffer;
    Verbraucher* verbraucher;
    UDPKommunikation* interface;
    static int msgID;
    bool stopped = false;

    //helper methods
    string messageToJSON(string type, string name, int id, double value, unsigned long long time);
    void simulate();

public:
    Simulator(Verbraucher *verbraucher, string communicationType, int port, string address);
    virtual ~Simulator();

    void start();
    void stop();
};


#endif //VERBRAUCHER_SIMULATOR_H
