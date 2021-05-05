//
// Created by philipp on 30.04.21.
//

#include "../../header/UDPServer/UDPServer.h"


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
    while (!this->stopped) {

        // Get client information.
        sockaddr_in client_addr {};
        int addr_len = sizeof(sockaddr_in);

        // Save the message.
        char buffer[MESSAGE_SIZE];
        ssize_t bytesReceived = recvfrom(this->socket_fd, buffer, MESSAGE_SIZE, 0, (sockaddr*) &client_addr, (socklen_t*) &addr_len);

        // Error handling.
        if (bytesReceived < 0) {
            int errorNr = errno;
            cerr << "Socket receive failed with err no: " << errorNr << endl;
        }

        // Forward incoming messages to the callback function.
        if (bytesReceived > 0) {
            this->callback->processMessage(string(buffer));
        }
    }

    cout << "[UDP Server] Exited while loop." << endl;
}



/**
 * Set the stopped state for this thread.
 *
 * @param value
 */
void UDPServer::stop() {

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

    // Create the socket.
    this->socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
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
}

