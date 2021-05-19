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
UDPSender::~UDPSender() {

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
 *
 */
void UDPSender::send(string ip, int port, string message) {

    struct sockaddr_in client {};
    client.sin_family = AF_INET;
    client.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &client.sin_addr.s_addr);

    int sendResult = sendto(this->socket_fd, message.c_str(), message.size(),0,(struct sockaddr*) &client, sizeof (struct sockaddr));
    if (sendResult < 0) {
        int errorNr = errno;
        cerr << "[UDPServer] Socket sendto failed with err no: " << errorNr << endl;
    }
}
