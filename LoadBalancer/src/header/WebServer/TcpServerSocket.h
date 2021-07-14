//
// Created by yabr on 05.05.21.
//

#ifndef ZENTRALE_HTTPINTEPRETER_H
#define ZENTRALE_HTTPINTEPRETER_H

#define MESSAGE_SIZE 1500

#include <iostream>
#include <string>
#include <unordered_map>
#include <sstream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>


using namespace std;


/**
 * A TcpServerSocket for every socket.
 */
class TcpServerSocket {

private:
    int sourceSocket {-1}, targetSocket {-1};

public:
    TcpServerSocket(int sourceSocket, int targetSocket);
    virtual ~TcpServerSocket();
    void run();
    void operator()();
};


#endif //ZENTRALE_HTTPINTEPRETER_H
