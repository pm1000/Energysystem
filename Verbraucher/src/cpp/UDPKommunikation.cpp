//
// Created by philipp on 01.05.21.
//

#include <netinet/in.h>
#include "../header/UDPKommunikation.h"

UDPKommunikation::UDPKommunikation(int port, std::string address) {
    this->port = port;
    this->address = address;
    initSocket();
}

UDPKommunikation::~UDPKommunikation() {

}

void UDPKommunikation::initSocket() {
    //create socket
    this->socketFD = socket(AF_INET, SOCK_DGRAM, 0);

    client.sin_family = AF_INET;
    inet_pton(AF_INET, address.c_str(), &client.sin_addr.s_addr);
    client.sin_port = htons(port);
    /*int res = bind(this->socketFD, (struct sockaddr*) &client, sizeof(struct sockaddr_in));
    if (res < 0) {
        throw std::runtime_error("Socked bind not successful");
    }*/
}

void UDPKommunikation::sendData(std::string message) {
    try {
        sendto(socketFD,message.c_str(),message.size(),0,(struct sockaddr*) &client, sizeof (struct sockaddr));
    }catch (std::exception &e){
        std::cout << e.what() << std::endl;
    }
}
