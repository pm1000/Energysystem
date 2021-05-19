//
// Created by philipp on 04.05.21.
//

#ifndef ERZEUGER_UDPKOMMUNIKATION_H
#define ERZEUGER_UDPKOMMUNIKATION_H

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


#endif //ERZEUGER_UDPKOMMUNIKATION_H
