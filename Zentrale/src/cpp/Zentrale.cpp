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

    // Call initialization
    cout << "[Zentrale] Start function called. Starting threads." << endl << endl;
    this->udpServer.init(8000);
    this->udpServer.setCallback(this);
    this->webserver.init(9000);


    // Start threads
    try {
        thread webServerThread(ref(this->webserver));
        thread udpServerThread(ref(this->udpServer));
        webServerThread.detach();
        udpServerThread.detach();
    } catch (system_error &e) {
        cerr << e.what() << endl;
        exit(1);
    }


    // Wait for all threads
    this_thread::sleep_for(chrono::milliseconds(500));


    // User input
    string input;
    do {
        cout << "Commands: quit" << endl;
        cout << " > ";
        getline(cin, input);

    } while (input != "quit");


    // Stop everything here
    cout << "[Zentrale] Stopping all services." << endl;
    this->webserver.stop();
    this->udpServer.stop();


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
