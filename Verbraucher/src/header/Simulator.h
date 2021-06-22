//
// Created by philipp on 30.04.21.
//

#ifndef VERBRAUCHER_SIMULATOR_H
#define VERBRAUCHER_SIMULATOR_H

#include "Komponente/Verbraucher.h"
#include "iostream"
#include "unistd.h"
#include "thread"
#include "Kommunikation//UDPKommunikation.h"
#include "Kommunikation/ZentralenKommunikation.h"
#include <chrono>
#include "unordered_map"
#include "Kommunikation/UDPCallback.h"
#include "Kommunikation/MqttKommunikation.h"
#include "mutex"

using namespace std;


/**
 *
 */
class Simulator : public UDPCallback {

private:
    unordered_map<int,string> msgBuffer;
    Verbraucher* verbraucher;
    ZentralenKommunikation* interface;
    static int msgID;
    bool stopped = false;
    mutex mtx;

    //helper methods
    string messageToJSON(string type, string name, int id, double value, time_t time);
    void simulate();

public:
    Simulator(Verbraucher *verbraucher, string communicationType, int port, string address, string brokerIp);
    virtual ~Simulator();

    void processMessage(string ip, std::string string1) override;

    void start();
    void stop();
};


#endif //VERBRAUCHER_SIMULATOR_H
