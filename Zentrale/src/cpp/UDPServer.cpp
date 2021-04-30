//
// Created by philipp on 30.04.21.
//

#include "../header/UDPServer.h"


/**
 * Constructor.
 */
UDPServer::UDPServer() = default;

/**
 * Destructor.
 */
UDPServer::~UDPServer() = default;



/**
 * Callable to start a thread.
 */
void UDPServer::operator()() {
    this->run();
}



/**
 * Started with the thread.
 */
void UDPServer::run() {

    // Console log.
    cout << "[UDP Server] Thread started. Entering while loop." << endl;

    // Endless loop until this thread becomes stopped.
    while (!this->interrupted) {

        // TODO: implement udp accept here and forward the message to processMessage()
        this->callback->processMessage("Test");
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}



/**
 * Set the interrupted state for this thread.
 *
 * @param value
 */
void UDPServer::interrupt() {
    this->interrupted = true;
}



/**
 * Set the callback function.
 *
 * @param callback Provide a function pointer to the callback function.
 */
void UDPServer::setCallback(UDPCallback* callback) {
    this->callback = callback;
}



/**
 * Bind port.
 *
 * @param port
 */
void UDPServer::init(int port) {

    // TODO: bind udp socket here
}

