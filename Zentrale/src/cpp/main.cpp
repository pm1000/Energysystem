#include <csignal>
#include "../header/Zentrale.h"

/*
 * Global variables
 */
Zentrale* zentrale;

/**
 * Function to execute when SIGTERM arrives
 */
void sigTerm (int sig) {
    zentrale->stop();
}



int main() {

    // Create the zentrale
    zentrale = new Zentrale();

    // Register a handler for programm termination
    signal(SIGTERM, sigTerm);

    // Start the application
    zentrale->start();

    return 0;
}
