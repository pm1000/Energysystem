//
// Created by yabr on 19.05.21.
//

#include "../../header/UDPSender/UDPSender.h"


/**
 *
 */
UDPSender::UDPSender() {

    // Create the socket.
    this->socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (this->socket_fd < 0) {
        int errorNr = errno;
        cerr << "[UDPServer] Socket call failed with err no: " << errorNr << endl;
        exit(1);
    }
}



/**
 *
 */
UDPSender::~UDPSender() = default;



/**
 *
 */
void UDPSender::send(string ip, int port, string message) {


}
