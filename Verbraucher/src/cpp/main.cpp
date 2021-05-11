#include <iostream>
#include <csignal>
#include <unordered_map>
#include "../header/Verbraucher.h"
#include "../header/Unternehmen.h"
#include "../header/Simulator.h"

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
        return 1;
    }

    // Verbraucher erstellen
    srand(time(NULL));
    Verbraucher* verbraucher = new Unternehmen(123, "FLEISCHER");
    sim = new Simulator(verbraucher, "UDP", stoi(argsMap.at("port")), argsMap.at("ip"));

    // Signal handler mit SIGTERM
    signal(SIGTERM, sigTermHandler);

    // Start in endless loop
    sim->start();

    std::cout << "Complete Consumption: " << verbraucher->getCompleteConsumption() << std::endl;

    delete sim;
    return 0;
}
