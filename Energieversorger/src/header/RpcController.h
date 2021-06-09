//
// Created by philipp on 08.06.21.
//

#ifndef ENERGIEVERSORGER_RPCCONTROLLER_H
#define ENERGIEVERSORGER_RPCCONTROLLER_H
#include "../../generated/energieversorger.pb.h"
#include "string"
#include "vector"
#include "Komponenten/Komponente.h"
#include "map"
#include <grpcpp/create_channel.h>
#include <energieversorger.grpc.pb.h>

using std::string;
using std::vector;
using std::map;

class RpcController {
    std::unique_ptr<Energieversorger::KomponentenData::Stub> stub;

    vector<int> getKomponentenIDs(const Energieversorger::KomponentenIDs& komponentenIDs);
    Komponente* getKomponentenData(int id);

public:
    RpcController();
    virtual ~RpcController();

    void init(string ipAddress, int port);

    vector<Komponente*> getKomponenten();
};


#endif //ENERGIEVERSORGER_RPCCONTROLLER_H
