//
// Created by philipp on 30.04.21.
//

#include "../header/Zentrale.h"

/**
 * Constructor
 */
Zentrale::Zentrale() = default;



/**
 * Destructor.
 */
Zentrale::~Zentrale() = default;



/**
 * Entrypoint for the code.
 */
void Zentrale::start() {

    // TODO: try-catch clauses

    cout << "[Zentrale] Start function called. Starting threads." << endl << endl;

    // Call initialization
    this->udpServer.init(8000);
    this->udpServer.setCallback(this);
    this->webserver.init(9000);

    // Start threads
    thread webServerThread(ref(this->webserver));
    thread udpServerThread(ref(this->udpServer));

    // Wait for all threads
    this_thread::sleep_for(chrono::seconds(2));

    // User input
    string input;
    do {
        cout << "Commands: quit" << endl;
        cout << " > ";
        getline(cin, input);

    } while (input != "quit");


    // Stop everything here
    cout << "[Zentrale] Stopping all services." << endl;
    this->webserver.interrupt();
    this->udpServer.interrupt();
    webServerThread.join();
    udpServerThread.join();


    // Clear all fields
    cout << "[Zentrale] Clearing all fields." << endl;
    this->komponentenListe.clear();
}



/**
 * Process incoming messages here.
 *
 * @param message The message in JSON format.
 */
void Zentrale::processMessage(string message) {

    // TODO: Match the message to all components
    cout << "[Zentrale] Received Message from UDP Server." << endl;
}
