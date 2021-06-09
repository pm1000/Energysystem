//
// Created by yabr on 09.06.21.
//

#ifndef ZENTRALE_RPCSERVER_H
#define ZENTRALE_RPCSERVER_H


#include <rpcServer.grpc.pb.h>
#include <rpcServer.pb.h>

#include <grpcpp/server_builder.h>
#include <grpcpp/security/server_credentials.h>

#include "../Komponenten/KomponentenController.h"

class RpcServer : public Energieversorger::KomponentenData::Service {
private:
    std::unique_ptr<grpc::Server> server;
    KomponentenController* komponentenController;

    int port;

    void run();

public:
    RpcServer();
    virtual ~RpcServer();

    // Implemented functions
    grpc::Status GetKomponentenIDs(::grpc::ServerContext *context, const ::Energieversorger::Empty *request,
                                   ::grpc::ServerWriter<::Energieversorger::KomponentenID> *writer) override;
    grpc::Status GetKomponente(::grpc::ServerContext *context, const ::Energieversorger::KomponentenID *request,
                               ::Energieversorger::Komponente *response) override;
    grpc::Status GetKomponentenWerte(::grpc::ServerContext *context, const ::Energieversorger::KomponentenID *request,
                                     ::grpc::ServerWriter<::Energieversorger::KomponentenWert> *writer) override;

    // Normal functions
    void init(KomponentenController* k, int port);
    void operator()();
    void stop();
};


#endif //ZENTRALE_RPCSERVER_H
