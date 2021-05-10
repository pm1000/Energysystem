#include <iostream>
#include <csignal>
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

int main() {

    // Creation phase
    srand(time(NULL));
    Erzeuger* erzeuger = new Solar(111, "aaa", 1000);
    sim = new Simulator(erzeuger,"UDP",5000,"127.0.0.1");

    // Register the handler
    signal(SIGTERM, sigTermHandler);

    // Start the loop
    sim->start();

    delete erzeuger;
    return 0;
}
