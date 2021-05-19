#include <iostream>
#include <csignal>
#include <unordered_map>
#include "../header/Verbraucher.h"
#include "../header/Unternehmen.h"
#include "../header/Simulator.h"
#include "../header/Haushalt.h"

/**
 * Global variable
 */
Simulator* sim;

/**
 * Signal handler for SIGTERM
 */
void sigTermHandler (int sigNr) {
    sim->stop();
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
    srand(time(NULL));
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

    // Start in endless loop
    sim->start();

    std::cout << "Complete Consumption: " << verbraucher->getCompleteConsumption() << std::endl;

    delete sim;
    return 0;
}
