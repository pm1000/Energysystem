//
// Created by philipp on 08.06.21.
//

#ifndef ENERGIEVERSORGER_RPCCONTROLLER_H
#define ENERGIEVERSORGER_RPCCONTROLLER_H
#include "../../generated/server.pb.h"
#include "string"

using std::string;

class RpcController {
private:
    string ipAddress;
    int port;

};


#endif //ENERGIEVERSORGER_RPCCONTROLLER_H
