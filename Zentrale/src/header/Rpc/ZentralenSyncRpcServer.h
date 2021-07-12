//
// Created by yabr on 09.06.21.
//

#ifndef ZENTRALE_SYNCRPCSERVER_H
#define ZENTRALE_SYNCRPCSERVER_H


#include <rpcServer.grpc.pb.h>
#include <rpcServer.pb.h>

#include <onlyZentrale.grpc.pb.h>
#include <onlyZentrale.pb.h>

#include <grpcpp/server_builder.h>
#include <grpcpp/security/server_credentials.h>

#include "../Komponenten/KomponentenController.h"
#include "MqttInterfaceZentrale.h"

class ZentralenSyncRpcServer : public ZentraleRpc::ZentraleKoordination::Service {
private:
    std::unique_ptr<grpc::Server> server;
    KomponentenController* komponentenController;
    MqttInterfaceZentrale* zentrale;

    int port;

    void run();

    string messageToJSON(string type, string name, int id, double value, time_t time, bool status, string ip);

public:
    ZentralenSyncRpcServer();
    virtual ~ZentralenSyncRpcServer();

    // Implemented functions
    grpc::Status RequestSync(::grpc::ServerContext *context, const ::ZentraleRpc::Source *request,
                             ::ZentraleRpc::Empty *response) override;

    // Normal functions
    void init(MqttInterfaceZentrale* z, KomponentenController* k, int port);
    void operator()();
    void stop();

    // Class functions
    void startSync(string channel);

};


#endif //ZENTRALE_SYNCRPCSERVER_H
