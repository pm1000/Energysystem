//
// Created by philipp on 30.04.21.
//

#ifndef ZENTRALE_WEBSERVER_H
#define ZENTRALE_WEBSERVER_H

#include <string>
#include <iostream>
#include <thread>

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "HttpContextHandlerController.h"


using namespace std;

/**
 * Webserver implementation for incoming http/tcp connections.
 */
class Webserver : public HttpContextHandlerController {
private:
    void run();

    int socket_fd {-1};

    // Thread state
    bool stopped;


public:
    Webserver();
    virtual ~Webserver();

    void init(int port);

    // Thread functions
    void operator()();
    void stop();

};


#endif //ZENTRALE_WEBSERVER_H
