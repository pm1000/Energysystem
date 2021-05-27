//
// Created by philipp on 04.05.21.
//

#ifndef ERZEUGER_SIMULATOR_H
#define ERZEUGER_SIMULATOR_H

#include "Komponente/Erzeuger.h"
#include "iostream"
#include "unistd.h"
#include "thread"
#include "Kommunikation/UDPKommunikation.h"
#include "Kommunikation/ZentralenKommunikation.h"
#include "unordered_map"
#include "Kommunikation/UDPCallback.h"
#include "mutex"

using namespace std;

/**
 *
 */
class Simulator : public UDPCallback {
private:
    unordered_map<int,string> msgBuffer;
    Erzeuger* erzeuger;
    ZentralenKommunikation* interface;
    mutex mtx;
    string messageToJSON(string type, string name, int id, double value, time_t t);
    static int msgID;

    //helper methods
    void simulate();
    bool stopped = false;

public:
    Simulator(Erzeuger *erzeuger, const string& communicationType, int port, string address);
    virtual ~Simulator();

    void processMessage(string ip, std::string string1) override;

    void start();
    void stop();
};


#endif //ERZEUGER_SIMULATOR_H
