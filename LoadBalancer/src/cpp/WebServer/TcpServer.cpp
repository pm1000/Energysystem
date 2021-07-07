//
// Created by philipp on 30.04.21.
//

#include "../../header/WebServer/TcpServer.h"

/**
 * Constructor
 */
TcpServer::TcpServer() : stopped(false) {
    this->zController = ZentralenController::getInstance();
}



/**
 * Destructor
 */
TcpServer::~TcpServer() = default;



/**
 * Thread entrypoint.
 */
void TcpServer::operator()() {
    this->run();
}


/**
 * Function to run in a separate thread.
 */
void TcpServer::run() {

    // Console log.
    cout << "[TcpServer] Thread started. Entering while loop." << endl;

    while (!this->stopped) {

        // Get client information.
        sockaddr_in client_addr {};
        int addr_len = sizeof(sockaddr_in);

        // Accept incoming connections
        int acceptedSocket = accept(this->listenSocket, (sockaddr *) &client_addr, (socklen_t *) &addr_len);
        if (acceptedSocket < 0) {
            int errorNr = errno;
            if (errorNr != 11) { // ERR_SOCK_WOULD_BLOCK
                cerr << "[TcpServer] Socket accept failed with err no: " << errorNr << endl;
            }
        } else {

            // Get a valid ip address from the pool
            string senderIp = to_string(client_addr.sin_addr.s_addr);
            std::hash<string> hash_fn;
            if (this->zController->getZentralenCount() == 0) {
                cerr << "Keine Zentrale verfügbar" << endl;
            } else {
                int hashedIP = (int) hash_fn(senderIp) % this->zController->getZentralenCount();
                shared_ptr<Zentrale> zentrale = zController->getActiveZentraleAt(hashedIP);

                //cout << "[TcpServer] Accepted Socket " << to_string(acceptedSocket) << endl;
                int targetSocket = -1;
                // Open a target socket
                int attempts = 0;
                bool successful = false;

                while (attempts < 5 && !successful) {
                    try {
                        targetSocket = this->openNewTargetSocket(zentrale->getIp(), this->targetPort);
                        successful = true;
                    } catch (std::exception &e) {
                        this->zController->zentraleNotActive(zentrale);
                        if (this->zController->getZentralenCount() == 0) {
                            //cerr << "Keine aktive Zentrale verfügbar" << endl;
                            break;
                        } else {
                            hashedIP = (int) hash_fn(senderIp) % this->zController->getZentralenCount();
                            zentrale = this->zController->getActiveZentraleAt(hashedIP);
                        }
                    }
                }

                if (!successful) {
                    cerr << "Heute läuft es gar nicht, alles ist down" << endl;
                    exit(1);
                }

                // Create a bridge between those sockets in separate threads
                auto *inboundTraffic = new TcpServerSocket(acceptedSocket, targetSocket);
                auto *outboundTraffic = new TcpServerSocket(targetSocket, acceptedSocket);

                thread inboundTrafficThread(&TcpServerSocket::run, inboundTraffic);
                thread outboundTrafficThread(&TcpServerSocket::run, outboundTraffic);

                this->setSocketTimeout(acceptedSocket);
                this->setSocketTimeout(targetSocket);

                inboundTrafficThread.detach();
                outboundTrafficThread.detach();
            }
        }
    }

    cout << "[TcpServer] Stopping TcpServer" << endl;

    // Close the socket.
    int closeResult = close(this->listenSocket);
    if (closeResult < 0) {
        int errorNr = errno;
        cerr << "[TcpServer] Socket close failed with err no: " << errorNr << endl;
        exit(1);
    }

    // Remove the file descriptor.
    this->listenSocket = -1;
}



/**
 * Set the stopped state for this thread.
 *
 * @param value
 */
void TcpServer::stop() {
    // Set flag.
    this->stopped = true;
}



/**
 * Initialization for the webserver.
 *
 * @param sourcePort Provide a sourcePort for the webserver.
 */
void TcpServer::init(int sourcePort, int targetPort) {

    // Save the sourcePort number
    this->targetPort = targetPort;

    // Create the socket.
    this->listenSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (this->listenSocket < 0) {
        int errorNr = errno;
        cerr << "[TcpServer] Socket call failed with err no: " << errorNr << endl;
        exit(1);
    }

    // Set socket timeout
    this->setSocketTimeout(this->listenSocket);

    // Bind socket_type, ip and sourcePort to the socket.
    struct sockaddr_in server_addr {};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(sourcePort);
    int result = bind(this->listenSocket, (struct sockaddr*) &server_addr, sizeof(struct sockaddr_in));
    if (result < 0) {
        int errorNr = errno;
        cerr << "[TcpServer] Socket bind failed with err no: " << errorNr << endl;
        exit(1);
    }

    // Listen for incoming connections
    result = listen(this->listenSocket, 5);
    if (result < 0) {
        int errorNr = errno;
        cerr << "[TcpServer] Socket listen failed with err no: " << errorNr << endl;
        exit(1);
    }
}



/**
*
*/
int TcpServer::openNewTargetSocket(const string &ip, const int port) {

    // Create the socket.
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        int errorNr = errno;
        cerr << "[TcpServer] Socket call failed with err no: " << errorNr << endl;
        exit(1);
    }

    // Connect to the target
    struct sockaddr_in targetAddress {};
    inet_pton(AF_INET, ip.c_str(), &targetAddress.sin_addr.s_addr);
    targetAddress.sin_family = AF_INET;
    targetAddress.sin_port = htons(port);

    int connectResult = connect(socket_fd, (struct sockaddr*) &targetAddress, sizeof(struct sockaddr));
    if (connectResult < 0) {
        int errorNr = errno;

        if (errorNr == ECONNREFUSED) {
            throw std::runtime_error("Server prob down");
        }

        cerr << "[TcpServer] Socket connect failed with err no: " << errorNr << endl;
        exit(1);
    }

    //cout << "[TcpServer] Target Socket " << to_string(socket_fd) << " verbunden." << endl;

    return socket_fd;
}



/**
 *
 */
void TcpServer::setSocketTimeout(int socket_fd) {

    struct timeval timeout{1,0};
    int timeoutResult = setsockopt(socket_fd, SOL_SOCKET, SO_RCVTIMEO, (char*) &timeout, sizeof(timeout));
    if (timeoutResult < 0) {
        int errorNr = errno;
        cerr << "[TcpServer] Socket set timeout failed with err no: " << errorNr << endl;
        exit(1);
    }
}
