//
// Created by philipp on 15.06.21.
//

#ifndef ZENTRALE_ERZEUGERRPCCLIENT_H
#define ZENTRALE_ERZEUGERRPCCLIENT_H

#include "string"
#include "vector"
#include "map"

#include <grpcpp/create_channel.h>
#include "erzeuger.grpc.pb.h"
#include "erzeuger.pb.h"

using std::string;
using std::vector;
using std::map;



class ErzeugerRpcClient {
private:
    std::unique_ptr<ErzeugerRpc::ErzeugerStatus::Stub> stub;

public:
    ErzeugerRpcClient();
    virtual ~ErzeugerRpcClient();

    void changeStatus(int id);
    void initRpc(string ipAddress, int port);

};


#endif //ZENTRALE_ERZEUGERRPCCLIENT_H
