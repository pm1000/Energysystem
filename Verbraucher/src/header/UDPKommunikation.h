//
// Created by philipp on 01.05.21.
//

#ifndef VERBRAUCHER_UDPKOMMUNIKATION_H
#define VERBRAUCHER_UDPKOMMUNIKATION_H

#include "ZentralenKommunikation.h"
#include <sys/socket.h>
#include <stdexcept>
#include "iostream"
#include <arpa/inet.h>

class UDPKommunikation : public ZentralenKommunikation{
private:
    int socketFD;
    struct sockaddr_in client {};

    void initSocket();
public:

    UDPKommunikation(int port, std::string address);
    ~UDPKommunikation() override;

    void sendData(std::string message) override;

};


#endif //VERBRAUCHER_UDPKOMMUNIKATION_H
