//
// Created by yabr on 05.05.21.
//

#include "../../header/WebServer/TcpServerSocket.h"

/**
 * Constructor.
 *
 * @param callback
 * @param sockId
 */
TcpServerSocket::TcpServerSocket(int sockId, int port) {
    this->sock_id = sockId;
    this->port = port;
}





/**
 * Destructor.
 */
TcpServerSocket::~TcpServerSocket() = default;


/**
 * Method to start in a thread.
 */
void TcpServerSocket::run() {

    // Save the message
    char buffer[MESSAGE_SIZE];
    bool conOpen = true;
    int sendSocket = openNewSocket();

    while (conOpen) {
        int readResult = recv(this->sock_id, &buffer, MESSAGE_SIZE, 0);
        if (readResult < 0) {
            int errorNr = errno;
            if (errorNr != 11) {
                cerr << "[UDPServer] Socket receive failed with err no: " << errorNr << endl;
            }
            close(this->sock_id);
            return;
        } else if (readResult == 0)
            conOpen = !conOpen;

        send(sendSocket,buffer,readResult,0);

    }


    // Close the socket and exit this thread
    int closeResult = close(sendSocket);
    if (closeResult < 0) {
        int errorNr = errno;
        cerr << "Socket call failed with err no: " << errorNr << endl;
        exit(1);
    }
}



/**
 *
 *
 * @return
 */
void TcpServerSocket::operator()() {

    // Forward to the run function.
    this->run();
}

int TcpServerSocket::openNewSocket() {
    // Create the socket.
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        int errorNr = errno;
        cerr << "[Webserver] Socket call failed with err no: " << errorNr << endl;
        exit(1);
    }

    // Set socket timeout
    struct timeval timeout{1,0};
    int timeoutResult = setsockopt(socket_fd, SOL_SOCKET, SO_RCVTIMEO, (char*) &timeout, sizeof(timeout));
    if (timeoutResult < 0) {
        int errorNr = errno;
        cerr << "[Webserver] Socket set timeout failed with err no: " << errorNr << endl;
        exit(1);
    }

    // Bind socket_type, ip and port to the socket.
    struct sockaddr_in server_addr {};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(this->port);
    int result = bind(socket_fd, (struct sockaddr*) &server_addr, sizeof(struct sockaddr_in));
    if (result < 0) {
        int errorNr = errno;
        cerr << "[Webserver] Socket bind failed with err no: " << errorNr << endl;
        exit(1);
    }

    return socket_fd;
}
