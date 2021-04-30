//
// Created by philipp on 30.04.21.
//

#ifndef ZENTRALE_ZENTRALE_H
#define ZENTRALE_ZENTRALE_H

#include <vector>
#include <thread>
#include <iostream>

#include "Webserver.h"
#include "Komponente.h"
#include "UDPCallback.h"
#include "UDPServer.h"

using namespace std;


/**
 * Class Zentrale is used to manage all components for udp and the webserver for http/tcp.
 */
class Zentrale : public UDPCallback {
private:
    // Server for incoming connections.
    UDPServer udpServer = UDPServer();
    Webserver webserver = Webserver();

    // Save all component information and save the threads.
    vector<Komponente*> komponentenListe;


public:
    Zentrale();
    virtual ~Zentrale();
    void start();

    // Callback function for incoming udp messages.
    void processMessage(string message) override;
};


#endif //ZENTRALE_ZENTRALE_H
