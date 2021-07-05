//
// Created by philipp on 14.06.21.
//

#include "../../header/Kommunikation/RpcController.h"

RpcController::RpcController() = default;



/**
 *
 */
RpcController::~RpcController() = default;



/**
 *
 */
void RpcController::initRpc(Erzeuger* erzeuger, int port) {
    try {
        this->erzeuger = erzeuger;
        this->port = port;
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
}

grpc::Status RpcController::SetStatus(::grpc::ServerContext *context, const ::ErzeugerRpc::KomponentenID *request,
                                      ::ErzeugerRpc::Empty *response) {

    int kompID = request->id();
    if (kompID == erzeuger->getID())
        erzeuger->switchStatus();

    if (erzeuger->isStatus())
        cout << "Wurde angeschaltet" << endl;
    else
        cout << "Wurde ausgeschaltet" << endl;

    return grpc::Status::OK;
}

void RpcController::start() {
    this->run();
}

void RpcController::stop() {
    this->server->Shutdown();
}

void RpcController::run() {
    string address = "0.0.0.0:" + to_string(this->port);

    cout << "Rpc Server started" << endl;
    // Create the instance of the server
    grpc::ServerBuilder builder;
    builder.AddListeningPort(address, grpc::InsecureServerCredentials());
    builder.RegisterService(this);
    this->server = builder.BuildAndStart();
    server->Wait();
}

void RpcController::operator()() {
    cout << "operator" << endl;
    run();
}
