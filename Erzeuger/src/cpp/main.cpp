#include <iostream>
#include <csignal>
#include <unordered_map>
#include "../header/Komponente/Erzeuger.h"
#include "../header/Komponente/Solar.h"
#include "../header/Komponente/Atom.h"
#include "../header/Komponente/Kohle.h"
#include "../header/Komponente/Wind.h"
#include "../header/Simulator.h"
#include "../header/Kommunikation/UDPServer.h"

/**
 * Global variables
 */
Simulator* sim;
UDPServer* server;

/**
 * SIGTERM Handler
 */
void sigTermHandler (int sigNum) {
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
        return 1;
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

    // Creation phase
    long t = (std::chrono::system_clock::now().time_since_epoch().count());
    srand(t);
    Erzeuger* erzeuger = nullptr;
    auto it = argsMap.find("type");
    if (it != argsMap.end()){
        if (it->second == "Solar"){
            // check for id
            int size;
            iter = argsMap.find("size");
            if (iter == argsMap.end()) {
                cout << "Size fehlt!" << endl;
                return -1;
            } else
                size = stoi(iter->second);

            erzeuger = new Solar(id, name, size);
        } else if (it->second == "Atom"){
            // check for id
            double size;
            iter = argsMap.find("size");
            if (iter == argsMap.end()) {
                cout << "Size fehlt!" << endl;
                return -1;
            } else
                size = stod(iter->second);

            erzeuger = new Atom(id, name, size);
        } else if (it->second == "Kohle") {
            // check for id
            double size;
            iter = argsMap.find("size");
            if (iter == argsMap.end()) {
                cout << "Size fehlt!" << endl;
                return -1;
            } else
                size = stod(iter->second);

            erzeuger = new Kohle(id, name, size);
        } else if (it->second == "Wind"){
            // check for id
            int size;
            iter = argsMap.find("size");
            if (iter == argsMap.end()) {
                cout << "Size fehlt!" << endl;
                return -1;
            } else
                size = stoi(iter->second);

            erzeuger = new Wind(id, name, size);
        } else {
            cout << "Ungültiger Erzeugertyp: " << it->second << endl;
            return -1;
        }

    } else {
        cout << "Type fehlt!" << endl;
        return -1;
    }

    sim = new Simulator(erzeuger,comType, stoi(argsMap.at("port")),argsMap.at("ip"));

    // Register the handler
    signal(SIGTERM, sigTermHandler);
    server = new UDPServer();
    server->init(5001);
    server->setCallback(sim);

    // Start threads
    thread udpServerThread(ref(*server));
    if (!argsMap.contains("test")) {
        thread simThread(&Simulator::start, sim);

        // Wait for threads
        udpServerThread.join();
        simThread.join();
    }
    else {
        if (argsMap.find("test")->second == "MISSING_MSG")
            sim->startMissingMsgTest(10000);
        else if (argsMap.find("test")->second == "PERF_TEST")
            sim->startPerformanceTest(1000000);


        sigTermHandler(SIGTERM);
        // Wait for threads
        udpServerThread.join();
    }

    return 0;
}
