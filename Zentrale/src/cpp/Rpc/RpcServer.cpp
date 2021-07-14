//
// Created by yabr on 09.06.21.
//

#include "../../header/Rpc/RpcServer.h"


/**
 *
 */
RpcServer::RpcServer() = default;



/**
 *
 */
RpcServer::~RpcServer() = default;



/**
 *
 */
grpc::Status RpcServer::GetKomponentenIDs(::grpc::ServerContext *context, const ::Energieversorger::Empty *request,
                                          ::grpc::ServerWriter<::Energieversorger::KomponentenID> *writer) {

    // Return a list of ids for all components
    for (auto &komponente : this->komponentenController->getKomponenten()) {
        Energieversorger::KomponentenID komponentenId;
        komponentenId.set_id(komponente.first);
        writer->Write(komponentenId);
    }

    return grpc::Status::OK;
}



/**
 *
 */
grpc::Status RpcServer::GetKomponente(::grpc::ServerContext *context, const ::Energieversorger::KomponentenID *request,
                                      ::Energieversorger::Komponente *response) {

    // Return specific data for a component
    Komponente* current = this->komponentenController->getKomponenteById(request->id());
    if (!current) return grpc::Status::CANCELLED;

    // Get all data
    response->set_id(current->getId());
    response->set_name(current->getName());
    response->set_type(current->getType());
    response->set_status(true); // TODO: wie sollen wir das hier feststellen?

    return grpc::Status::OK;
}



/**
 *
 */
grpc::Status
RpcServer::GetKomponentenWerte(::grpc::ServerContext *context, const ::Energieversorger::KomponentenID *request,
                               ::grpc::ServerWriter<::Energieversorger::KomponentenWert> *writer) {

    // Return a list of all values for a specific component
    Komponente* current = this->komponentenController->getKomponenteById(request->id());
    if (!current) return grpc::Status::CANCELLED;

    // Write all data
    for (auto &valuePair : current->getValues()) {
        Energieversorger::KomponentenWert wert;
        wert.set_time(valuePair.first);
        wert.set_value(valuePair.second);
        writer->Write(wert);
    }

    return grpc::Status::OK;
}



/**
 *
 */
void RpcServer::init(KomponentenController *k, int port) {
    this->komponentenController = k;
    this->port = port;
}



/**
 *
 */
void RpcServer::run() {
    string address = "0.0.0.0:" + to_string(this->port);

    // Create the instance of the server
    grpc::ServerBuilder builder;
    builder.AddListeningPort(address, grpc::InsecureServerCredentials());
    builder.RegisterService(this);
    this->server = builder.BuildAndStart();
    server->Wait();
}



/**
 *
 */
void RpcServer::stop() {
    this->server->Shutdown();
}



/**
 *
 */
void RpcServer::operator()() {
    this->run();
}
