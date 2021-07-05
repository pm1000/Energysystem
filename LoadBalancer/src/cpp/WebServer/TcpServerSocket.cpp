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

    //cout << "[Socket] Von " << to_string(sourceSocket) << " nach " << to_string(targetSocket) << " wurde geöffnet." << endl;
}





/**
 * Destructor.
 */
TcpServerSocket::~TcpServerSocket() {
    //cout << "[Socket] Von " << to_string(sourceSocket) << " nach " << to_string(targetSocket) << " wurde geschlossen." << endl;
}


/**
 * Method to start in a thread.
 */
void TcpServerSocket::run() {

    // Save the message
    char buffer[MESSAGE_SIZE];
    bool connOpen = true;

    while (connOpen) {
        int readResult = recv(this->sourceSocket, &buffer, MESSAGE_SIZE, 0);
        if (readResult < 0) {
            int errorNr = errno;
            if (errorNr != 11) {
                cerr << "[TCPSocket] Socket receive failed with err no: " << errorNr << endl;
            } else {
                connOpen = false;
            }

        } else if (readResult == 0) {
            connOpen = false;
        }

        send(targetSocket, buffer, readResult, 0);
    }

    // Close the socket and exit this thread
    int closeResult = close(sourceSocket);
    //cout << "[Socket] Close Result von " << to_string(sourceSocket) << " ist " << to_string(closeResult) << endl;
    if (closeResult < 0) {
        int errorNr = errno;
        cerr << "Socket call failed with err no: " << errorNr << endl;
        exit(1);
    }

    // Socket is finished, delete this element
    delete this;
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
