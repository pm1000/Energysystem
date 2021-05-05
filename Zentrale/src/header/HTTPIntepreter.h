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

#include <sys/socket.h>
#include <unistd.h>

#include "HTTPCallback.h"

using namespace std;


/**
 * A HTTPIntepreter for every socket.
 */
class HTTPIntepreter {

private:
    HTTPCallback* callback = nullptr;
    int sock_id {-1};

    void run();

public:
    HTTPIntepreter(HTTPCallback *callback, int sockId);
    virtual ~HTTPIntepreter();
    void operator()();
};


#endif //ZENTRALE_HTTPINTEPRETER_H
