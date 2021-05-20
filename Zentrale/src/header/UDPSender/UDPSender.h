//
// Created by yabr on 19.05.21.
//

#ifndef ZENTRALE_UDPSENDER_H
#define ZENTRALE_UDPSENDER_H

#include <string>
#include <iostream>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

/**
 *
 */
class UDPSender {
private:
    int socket_fd = -1;

public:
    UDPSender();
    virtual ~UDPSender();

    virtual void send(string ip, int port, string message);
};


#endif //ZENTRALE_UDPSENDER_H
