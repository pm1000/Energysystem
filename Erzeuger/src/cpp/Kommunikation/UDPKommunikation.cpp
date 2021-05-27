//
// Created by philipp on 04.05.21.
//

#include "../../header/Kommunikation//UDPKommunikation.h"


/**
 *
 */
UDPKommunikation::UDPKommunikation(int port, std::string address) {
    this->port = port;
    this->address = address;
    initSocket();
}



/**
 *
 */
UDPKommunikation::~UDPKommunikation() = default;



/**
 *
 */
void UDPKommunikation::initSocket() {
    //create socket
    try {
        this->socketFD = socket(AF_INET, SOCK_DGRAM, 0);
        client.sin_family = AF_INET;
        inet_pton(AF_INET, address.c_str(), &client.sin_addr.s_addr);
        client.sin_port = htons(port);
    } catch (exception &e) {
        cerr << "Failed to initiate the socket." << endl << e.what() << endl;
    }
}



/**
 *
 */
void UDPKommunikation::sendData(string message) {
    try {
        sendto(socketFD,message.c_str(),message.size(),0,(struct sockaddr*) &client, sizeof (struct sockaddr));
    } catch (exception &e) {
        cout << "Failed to send data." << endl << e.what() << endl;
    }
}
