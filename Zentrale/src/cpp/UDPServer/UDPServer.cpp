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
    cout << "[UDPServer] Thread started. Entering while loop." << endl;
    std::srand(std::time(NULL));

    // Endless loop until this thread becomes stopped.
    while (!this->stopped) {

        // Get client information.
        sockaddr_in client_addr {};
        int addr_len = sizeof(sockaddr_in);

        // Save the message.
        char buffer[MESSAGE_SIZE] {0};
        ssize_t bytesReceived = recvfrom(this->socket_fd, buffer, MESSAGE_SIZE, 0, (sockaddr*) &client_addr, (socklen_t*) &addr_len);

        // Error handling.
        if (bytesReceived < 0) {
            int errorNr = errno;
            if (errorNr != 11) {
                cerr << "[UDPServer] Socket receive failed with err no: " << errorNr << endl;
            }
        } else {

            // Forward incoming messages to the contextController function.
            if (bytesReceived > 0) {
                char ipBuffer[100];
                inet_ntop(AF_INET, &client_addr.sin_addr, ipBuffer, sizeof(ipBuffer));

                if (this->simulatePacketLoss) {
                    int r = rand() % 100;
                    if (r > 80) this->callback->processMessage(string(ipBuffer), string(buffer));
                } else {
                    this->callback->processMessage(string(ipBuffer), string(buffer));
                }
            }
        }
    }

    cout << "[UDPServer] Stopping UDPServer" << endl;

    // Close the socket.
    int closeResult = close(this->socket_fd);
    if (closeResult < 0) {
        int errorNr = errno;
        cerr << "[UDPServer] Socket close failed with err no: " << errorNr << endl;
        exit(1);
    }

    // Remove the file descriptor.
    this->socket_fd = -1;
}



/**
 * Set the stopped state for this thread.
 *
 * @param value
 */
void UDPServer::stop() {
    // Set flag.
    this->stopped = true;
}



/**
 * Set the contextController function.
 *
 * @param callback Provide a function pointer to the contextController function.
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
        cerr << "[UDPServer] Socket call failed with err no: " << errorNr << endl;
        exit(1);
    }

    // Set socket timeout
    struct timeval timeout{1,0};
    int timeoutResult = setsockopt(this->socket_fd, SOL_SOCKET, SO_RCVTIMEO, (char*) &timeout, sizeof(timeout));
    if (timeoutResult < 0) {
        int errorNr = errno;
        cerr << "[Webserver] Socket set timeout failed with err no: " << errorNr << endl;
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
        cerr << "[UDPServer] Socket bind failed with err no: " << errorNr << endl;
        exit(1);
    }
}



/**
 *
 */
void UDPServer::setPacketLoss(bool value) {
    this->simulatePacketLoss = value;
}

