//
// Created by philipp on 30.04.21.
//

#ifndef ZENTRALE_WEBSERVER_H
#define ZENTRALE_WEBSERVER_H

#include <string>
#include <iostream>
#include <thread>


using namespace std;

/**
 * Webserver implementation for incoming http/tcp connections.
 */
class Webserver {
private:
    void run();

    // TODO: tcp socket object here

    // Thread state
    bool interrupted;


public:
    Webserver();
    virtual ~Webserver();

    void init(int port);

    // Thread functions
    void operator()();
    void interrupt();

};


#endif //ZENTRALE_WEBSERVER_H
