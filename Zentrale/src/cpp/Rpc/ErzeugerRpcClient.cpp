//
// Created by philipp on 15.06.21.
//

#include "../../header/Rpc/ErzeugerRpcClient.h"

ErzeugerRpcClient::ErzeugerRpcClient() {}

ErzeugerRpcClient::~ErzeugerRpcClient() {

}

void ErzeugerRpcClient::changeStatus(int id) {
    std::cout << "i am here" << std::endl;
    grpc::ClientContext context;
    ErzeugerRpc::KomponentenID kompId;
    kompId.set_id(id);
    ErzeugerRpc::Empty result;
    auto status = this->stub->SetStatus(&context, kompId, &result);

    if (!status.ok())
        std::cerr << status.error_message() << std::endl;

}

void ErzeugerRpcClient::initRpc(string ipAddress, int port) {
    try {
        string address = ipAddress + ":" + std::to_string(port);
        auto channel = grpc::CreateChannel(address, grpc::InsecureChannelCredentials());
        stub = ErzeugerRpc::ErzeugerStatus::NewStub(channel);
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
}