//
// Created by philipp on 30.04.21.
//

#ifndef ZENTRALE_UDPSERVER_H
#define ZENTRALE_UDPSERVER_H

#include <string>
#include <iostream>
#include <thread>
#include "UDPCallback.h"

using namespace std;

/**
 * UDPServer implementation for incoming udp connections.
 */
class UDPServer {
private:
    void run();
    UDPCallback* callback{};

    // TODO: udp socket object here

    // Thread state
    bool interrupted{};

public:
    UDPServer();
    virtual ~UDPServer();

    void setCallback(UDPCallback* callback);
    void init(int port);

    // Thread functions
    void operator()();
    void interrupt();
};


#endif //ZENTRALE_UDPSERVER_H
