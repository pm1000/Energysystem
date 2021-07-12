//
// Created by yabr on 09.06.21.
//

#include "../../header/Rpc/ZentralenSyncRpcServer.h"


/**
 *
 */
ZentralenSyncRpcServer::ZentralenSyncRpcServer() = default;



/**
 *
 */
ZentralenSyncRpcServer::~ZentralenSyncRpcServer() = default;



/**
 *
 */
void ZentralenSyncRpcServer::init(MqttInterfaceZentrale* z, KomponentenController *k, int port) {
    this->komponentenController = k;
    this->zentrale = z;
    this->port = port;
}



/**
 *
 */
void ZentralenSyncRpcServer::run() {
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
void ZentralenSyncRpcServer::stop() {
    this->server->Shutdown();
}



/**
 *
 */
void ZentralenSyncRpcServer::operator()() {
    this->run();
}



/**
 *
 */
grpc::Status ZentralenSyncRpcServer::RequestSync(::grpc::ServerContext *context, const ::ZentraleRpc::Source *request,
                                                 ::ZentraleRpc::Empty *response) {

    // Start thread to execute this task.
    thread t(&ZentralenSyncRpcServer::startSync, this, request->targetchannel());
    t.detach();

    return grpc::Status::OK;
}



/**
 *
 */
void ZentralenSyncRpcServer::startSync(string channel) {

    // All Komponenten
    for (const auto &komponentenIt : komponentenController->getKomponenten()) {

        // Every data-value pair
        for (const auto &dataMap : komponentenIt.second->getValues()) {

            string payload = messageToJSON(komponentenIt.second->getType(), komponentenIt.second->getName(),
                                           komponentenIt.second->getId(), dataMap.first, dataMap.second, true,
                                           komponentenIt.second->getIp());
            this->zentrale->sendWithMqtt(channel + komponentenIt.second->getName(), payload);
        }
    }
}



/**
*
*/
string ZentralenSyncRpcServer::messageToJSON(string type, string name, int id, double value, time_t time, bool status,
                                             string ip) {
    std::string message = "{";
    message += "\"type\": ";
    message += "\"" + type + "\", ";
    message += "\"name\": ";
    message += "\"" + name + "\", ";
    message += "\"id\": ";
    message += to_string(id) + ", ";
    message += "\"value\": ";
    message += to_string(value) + ", ";
    message += "\"time\": ";
    message += to_string(time) + ", ";
    message += "\"status\": ";
    if (status)
        message += "1";
    else
        message += "0";

    message += ", \"ip\": ";
    message += ip;
    message += "}";

    return message;
}