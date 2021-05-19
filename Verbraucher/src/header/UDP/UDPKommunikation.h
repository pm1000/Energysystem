//
// Created by philipp on 01.05.21.
//

#ifndef VERBRAUCHER_UDPKOMMUNIKATION_H
#define VERBRAUCHER_UDPKOMMUNIKATION_H

#include "../ZentralenKommunikation.h"
#include <sys/socket.h>
#include <stdexcept>
#include "iostream"
#include <arpa/inet.h>

using namespace std;

/**
 *
 */
class UDPKommunikation : public ZentralenKommunikation {
private:
    int socketFD;
    struct sockaddr_in client {};
    void initSocket();

public:
    UDPKommunikation(int port, string address);
    ~UDPKommunikation() override;

    void sendData(string message) override;
};


#endif //VERBRAUCHER_UDPKOMMUNIKATION_H
