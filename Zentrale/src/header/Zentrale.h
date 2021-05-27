//
// Created by philipp on 30.04.21.
//

#ifndef ZENTRALE_ZENTRALE_H
#define ZENTRALE_ZENTRALE_H

#include <vector>
#include <thread>
#include <iostream>

#include "WebServer/Webserver.h"
#include "Komponenten/Komponente.h"
#include "UDPServer/UDPCallback.h"
#include "UDPServer/UDPServer.h"
#include "Komponenten/KomponentenController.h"
#include "../header/WebServer/HTMLGenerator.h"

using namespace std;


/**
 * Class Zentrale is used to manage all components for udp and the webserver for http/tcp.
 */
class Zentrale {
private:
    // Server for incoming connections.
    UDPServer udpServer = UDPServer();
    Webserver webserver = Webserver();
    KomponentenController* komponentenController;


public:
    Zentrale();
    virtual ~Zentrale();
    void start();
    void stop();

    void enableTestmode();
};


#endif //ZENTRALE_ZENTRALE_H
