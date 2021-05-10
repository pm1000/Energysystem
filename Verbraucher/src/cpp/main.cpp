#include <iostream>
#include <csignal>
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


int main() {

    // Verbraucher erstellen
    srand(time(NULL));
    Verbraucher* verbraucher = new Unternehmen(123, "FLEISCHER");
    sim = new Simulator(verbraucher, "UDP", 5000, "127.0.0.1");

    // Signal handler mit SIGTERM
    signal(SIGTERM, sigTermHandler);

    // Start in endless loop
    sim->start();

    std::cout << "Complete Consumption: " << verbraucher->getCompleteConsumption() << std::endl;

    delete sim;
    return 0;
}
