//
// Created by philipp on 04.05.21.
//

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
    try {
        this->socketFD = socket(AF_INET, SOCK_DGRAM, 0);

        client.sin_family = AF_INET;
        inet_pton(AF_INET, address.c_str(), &client.sin_addr.s_addr);
        client.sin_port = htons(port);
    }catch (std::exception &e){
        std::cerr << "Failed to initiate the socket." << std::endl << e.what() << std::endl;
    }
}

void UDPKommunikation::sendData(std::string message) {
    try {
        sendto(socketFD,message.c_str(),message.size(),0,(struct sockaddr*) &client, sizeof (struct sockaddr));
    }catch (std::exception &e){
        std::cout << "Failed to send data." << std::endl << e.what() << std::endl;
    }
}
