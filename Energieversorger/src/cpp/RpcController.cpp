//
// Created by philipp on 08.06.21.
//

#include "../header/RpcController.h"


/**
 *
 */
RpcController::RpcController() = default;



/**
 *
 */
RpcController::~RpcController() = default;



/**
 *
 */
void RpcController::initRpc(string ipAddress, int port) {
    try {
        string address = ipAddress + ":" + std::to_string(port);
        auto channel = grpc::CreateChannel(address, grpc::InsecureChannelCredentials());
        stub = Energieversorger::KomponentenData::NewStub(channel);
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
}



/**
 *
 */
Komponente *RpcController::requestKomponentenData(int id) {

    // Send rpc command
    grpc::ClientContext context;
    Energieversorger::KomponentenID komponentenId;
    komponentenId.set_id(id);
    Energieversorger::Komponente rpcResult;
    auto status = this->stub->GetKomponente(&context, komponentenId, &rpcResult);

    // Error handling
    if (!status.ok()) {
        std::cerr << status.error_message() << std::endl;
        exit(1);
    }

    Komponente* komponente;
    if (rpcResult.type() == "Unternehmen" || rpcResult.type() == "Haushalt") {
        komponente = new Verbraucher(rpcResult.id(), rpcResult.name(), rpcResult.type());
    } else {
        komponente = new Erzeuger(rpcResult.type(), rpcResult.name(), rpcResult.id());
    }

    return komponente;
}



/**
 *
 */
vector<int> RpcController::requestKomponentenIDs() {

    // Send rpc command
    grpc::ClientContext context;
    const::Energieversorger::Empty empty;
    auto result = this->stub->GetKomponentenIDs(&context, empty);

    // Get every message
    Energieversorger::KomponentenID msg;
    vector<int> komponentenIds;
    while (result->Read(&msg)) {
        komponentenIds.push_back(msg.id());
    }

    // Error handling
    auto status = result->Finish();
    if (!status.ok()) {
        std::cerr << status.error_message() << std::endl;
        exit(1);
    }

    return komponentenIds;
}



/**
 *
 */
void RpcController::requestKomponentenWerte(Komponente *komponente) {

    // Send rpc command
    grpc::ClientContext context;
    Energieversorger::KomponentenID komponentenId;
    komponentenId.set_id(komponente->getId());
    auto result = this->stub->GetKomponentenWerte(&context, komponentenId);

    // Get every message
    Energieversorger::KomponentenWert msg;
    while (result->Read(&msg)) {
        komponente->addNewValue(msg.time(), msg.value());
    }

    // Error handling
    auto status = result->Finish();
    if (!status.ok()) {
        std::cerr << status.error_message() << std::endl;
    }
}



/**
 *
 */
vector<Komponente*> RpcController::initKomponenten() {

    // Prepare all components
    auto komponentenIds = this->requestKomponentenIDs();
    vector<Komponente*> result;
    for (auto komponenteId : komponentenIds) {
        auto* komponente = this->requestKomponentenData(komponenteId);
        result.push_back(komponente);
    }

    return result;
}
