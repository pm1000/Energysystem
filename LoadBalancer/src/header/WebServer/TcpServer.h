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
#include <arpa/inet.h>
#include "../../header/WebServer/TcpServerSocket.h"


using namespace std;

/**
 * TcpServer implementation for incoming http/tcp connections.
 */
class TcpServer {
private:
    int openNewTargetSocket(const string &ip, const int port);
    void setSocketTimeout(int socket_fd);
    int listenSocket {-1};
    int targetPort;

    void run();

    // Thread state
    bool stopped;


public:
    TcpServer();
    virtual ~TcpServer();

    void init(int sourcePort, int targetPort);

    // Thread functions
    void operator()();
    void stop();

};


#endif //ZENTRALE_WEBSERVER_H
