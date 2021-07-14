//
// Created by philipp on 14.06.21.
//

#ifndef ERZEUGER_RPCCONTROLLER_H
#define ERZEUGER_RPCCONTROLLER_H

#include <grpcpp/create_channel.h>
#include <grpcpp/server_builder.h>
#include "erzeuger.pb.h"
#include "erzeuger.grpc.pb.h"
#include "string"
#include "../Komponente/Erzeuger.h"

using std::string;

class RpcController : public ErzeugerRpc::ErzeugerStatus::Service{
private:
    std::unique_ptr<grpc::Server> server;
    Erzeuger* erzeuger;
    int port;

    void run();
public:
    RpcController();
    virtual ~RpcController();

    grpc::Status SetStatus(::grpc::ServerContext *context, const ::ErzeugerRpc::KomponentenID *request,
                           ::ErzeugerRpc::Empty *response) override;

    void initRpc(Erzeuger* erzeuger, int port);
    void start();
    void stop();
    void operator()();

};


#endif //ERZEUGER_RPCCONTROLLER_H

