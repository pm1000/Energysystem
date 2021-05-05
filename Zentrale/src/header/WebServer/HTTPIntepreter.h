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

#include "HttpContextHandlerController.h"

using namespace std;


/**
 * A HTTPIntepreter for every socket.
 */
class HTTPIntepreter {

private:
    HttpContextHandlerController* controller = nullptr;
    int sock_id {-1};

    string processHTTP(unordered_map<string, string> &headers);

    void run();

public:
    HTTPIntepreter(HttpContextHandlerController *controller, int sockId);
    virtual ~HTTPIntepreter();
    void operator()();
};


#endif //ZENTRALE_HTTPINTEPRETER_H
