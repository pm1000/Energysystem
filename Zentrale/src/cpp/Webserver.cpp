//
// Created by philipp on 30.04.21.
//

#include "../header/Webserver.h"

/**
 * Constructor
 */
Webserver::Webserver() : interrupted(false) {

}



/**
 * Destructor
 */
Webserver::~Webserver() = default;



/**
 * Thread entrypoint.
 */
void Webserver::operator()() {
    this->run();
}


/**
 * Function to run in a separate thread.
 */
void Webserver::run() {

    // Console log.
    cout << "[Webserver] Thread started. Entering while loop." << endl;

    while (!this->interrupted) {

        // TODO: accept function for the tcp connection here
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}



/**
 * Set the interrupted state for this thread.
 *
 * @param value
 */
void Webserver::interrupt() {
    this->interrupted = true;
}



/**
 * Initialization for the webserver.
 *
 * @param port Provide a port for the webserver.
 */
void Webserver::init(int port) {

    // TODO: Initialize the tcp socket here
    // TODO: Initialize handler for http here
}
