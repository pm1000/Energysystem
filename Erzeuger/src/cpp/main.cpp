#include <iostream>
#include <csignal>
#include <unordered_map>
#include "../header/Erzeuger.h"
#include "../header/Solar.h"
#include "../header/Simulator.h"

/**
 * Global variables
 */
Simulator* sim;

/**
 * SIGTERM Handler
 */
void sigTermHandler (int sigNum) {
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
    }

    // Creation phase
    srand(time(NULL));
    Erzeuger* erzeuger = new Solar(111, "aaa", 1000);
    sim = new Simulator(erzeuger,"UDP", stoi(argsMap.at("port")),argsMap.at("ip"));

    // Register the handler
    signal(SIGTERM, sigTermHandler);

    // Start the loop
    sim->start();

    delete erzeuger;
    return 0;
}
