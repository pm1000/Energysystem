//
// Created by philipp on 08.06.21.
//

#ifndef ENERGIEVERSORGER_RPCCONTROLLER_H
#define ENERGIEVERSORGER_RPCCONTROLLER_H

#include "string"
#include "vector"
#include "map"

#include "Komponenten/Komponente.h"
#include "Komponenten/Verbraucher.h"
#include "Komponenten/Erzeuger.h"

#include <grpcpp/create_channel.h>
#include <energieversorger.grpc.pb.h>
#include "energieversorger.pb.h"
#include "Komponenten/KomponentenController.h"

using std::string;
using std::vector;
using std::map;

class RpcController {
    std::unique_ptr<Energieversorger::KomponentenData::Stub> stub;

    vector<int> requestKomponentenIDs();
    Komponente* requestKomponentenData(int id);

public:
    RpcController();
    virtual ~RpcController();

    void initRpc(string ipAddress, int port);
    vector<Komponente*> initKomponenten();
    void requestKomponentenWerte(Komponente* komponente);
};


#endif //ENERGIEVERSORGER_RPCCONTROLLER_H
