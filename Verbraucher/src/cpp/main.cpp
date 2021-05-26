#include <iostream>
#include <csignal>
#include <unordered_map>
#include "../header/Komponente/Verbraucher.h"
#include "../header/Komponente/Unternehmen.h"
#include "../header/Simulator.h"
#include "../header/Komponente/Haushalt.h"
#include "../header/Kommunikation/UDPServer.h"

/**
 * Global variable
 */
Simulator* sim;
UDPServer* server;

/**
 * Signal handler for SIGTERM
 */
void sigTermHandler (int sigNr) {
    sim->stop();
    server->stop();
}


using namespace std;

/**
 *
 */
int main(int argc, char* args[]) {

    // Get all args
    unordered_map<string, string> argsMap;
    for (int i = 1; i < argc; i++) {
        string currentArg = args[i];
        int pos = currentArg.find('=');
        auto arg = make_pair(currentArg.substr(0, pos), currentArg.substr(pos + 1));
        argsMap.insert(arg);
    }

    // Check for ip and port
    if (!argsMap.contains("ip") || !argsMap.contains("port")) {
        cout << "Ziel-Ip (ip=...) und Ziel-Port (port=...) muss gegeben sein." << endl;
        return -1;
    }

    // check for id
    int id;
    auto iter = argsMap.find("id");
    if (iter == argsMap.end()) {
        cout << "ID fehlt!" << endl;
        return -1;
    } else
        id = stoi(iter->second);

    //check for name
    string name;
    iter = argsMap.find("name");
    if (iter == argsMap.end()) {
        cout << "Name fehlt!" << endl;
        return -1;
    } else
        name = iter->second;

    //check for communication type
    string comType;
    iter = argsMap.find("communication");
    if (iter == argsMap.end()) {
        cout << "Kommunikationstyp fehlt!" << endl;
        return -1;
    } else
        comType = iter->second;

    // Verbraucher erstellen
    long t = (std::chrono::system_clock::now().time_since_epoch().count());
    srand(t);
    Verbraucher* verbraucher = nullptr;
    auto it = argsMap.find("type");
    if (it != argsMap.end()){
        if (it->second == "Haushalt")
            verbraucher = new Haushalt(id, name);
        else if (it->second == "Unternehmen")
            verbraucher = new Unternehmen(id, name);
        else {
            cout << "Fehlerhafter Verbrauchertyp: " << it->second << endl;
            return -1;
        }
    } else {
        cout << "Verbraucher Typ muss gegeben sein" << endl;
        return -1;
    }
    sim = new Simulator(verbraucher, comType, stoi(argsMap.at("port")), argsMap.at("ip"));

    // Signal handler mit SIGTERM
    signal(SIGTERM, sigTermHandler);
    server = new UDPServer();
    server->init(5001);
    server->setCallback(sim);
    thread udpServerThread(*server);
    // Start in endless loop
    sim->start();
    udpServerThread.join();

    std::cout << "Complete Consumption: " << verbraucher->getCompleteConsumption() << std::endl;

    delete server;
    delete sim;
    return 0;
}
