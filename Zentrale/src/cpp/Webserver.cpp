//
// Created by philipp on 30.04.21.
//

#include "../header/Webserver.h"

/**
 * Constructor
 */
Webserver::Webserver() : stopped(false) {

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

    while (!this->stopped) {

        // Get client information.
        sockaddr_in client_addr {};
        int addr_len = sizeof(sockaddr_in);

        // Accept incoming connections
        int newSock_fd = accept(this->socket_fd, (sockaddr *) &client_addr, (socklen_t *) &addr_len);
        if (newSock_fd < 0) {
            int errorNr = errno;
            cerr << "Socket accept failed with err no: " << errorNr << endl;
        }

        thread httpThread;
        httpThread.detach();
    }
}



/**
 * Set the stopped state for this thread.
 *
 * @param value
 */
void Webserver::stop() {

    // Set flag.
    this->stopped = true;

    // Close the socket.
    int closeResult = close(this->socket_fd);
    if (closeResult < 0) {
        int errorNr = errno;
        cerr << "Socket call failed with err no: " << errorNr << endl;
        exit(1);
    }

    // Remove the file descriptor.
    this->socket_fd = -1;
}



/**
 * Initialization for the webserver.
 *
 * @param port Provide a port for the webserver.
 */
void Webserver::init(int port) {

    // Create the socket.
    this->socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->socket_fd < 0) {
        int errorNr = errno;
        cerr << "Socket call failed with err no: " << errorNr << endl;
        exit(1);
    }

    // Bind socket_type, ip and port to the socket.
    struct sockaddr_in server_addr {};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);
    int result = bind(this->socket_fd, (struct sockaddr*) &server_addr, sizeof(struct sockaddr_in));
    if (result < 0) {
        int errorNr = errno;
        cerr << "Socket bind failed with err no: " << errorNr << endl;
        exit(1);
    }

    // Listen for incoming connections
    result = listen(this->socket_fd, 5);
    if (result < 0) {
        int errorNr = errno;
        cerr << "Socket listen failed with err no: " << errorNr << endl;
        exit(1);
    }
}
