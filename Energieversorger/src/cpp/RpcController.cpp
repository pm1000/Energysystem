//
// Created by philipp on 08.06.21.
//

#include "../header/RpcController.h"

RpcController::RpcController() = default;

RpcController::~RpcController() = default;

void RpcController::init(string ipAddress, int port) {
    try {
        string address = ipAddress + ":" + std::to_string(port);
        auto channel = grpc::CreateChannel(address, grpc::InsecureChannelCredentials());
        stub = Energieversorger::KomponentenData::NewStub(channel);
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}


vector<Komponente *> RpcController::getKomponenten() {
    return vector<Komponente *>();
}

Komponente *RpcController::getKomponentenData(int id) {
    return nullptr;
}

vector<int> RpcController::getKomponentenIDs(const Energieversorger::KomponentenIDs &komponentenIDs) {
    

    return vector<int>();
}
