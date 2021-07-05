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
TcpServerSocket::TcpServerSocket(int sourceSocket, int targetSocket) {
    this->sourceSocket = sourceSocket;
    this->targetSocket = targetSocket;
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

    while (conOpen) {
        int readResult = recv(this->sourceSocket, &buffer, MESSAGE_SIZE, 0);
        if (readResult < 0) {
            int errorNr = errno;
            if (errorNr != 11) {
                cerr << "[UDPServer] Socket receive failed with err no: " << errorNr << endl;
            }
            close(this->sourceSocket);
            return;
        } else if (readResult == 0)
            conOpen = !conOpen;

        send(targetSocket, buffer, readResult, 0);

    }


    // Close the socket and exit this thread
    int closeResult = close(sourceSocket);
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
