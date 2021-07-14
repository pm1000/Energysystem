//
// Created by philipp on 30.04.21.
//

#ifndef ZENTRALE_ZENTRALE_H
#define ZENTRALE_ZENTRALE_H

#include <vector>
#include <thread>
#include <iostream>

#include "WebServer/Webserver.h"
#include "Komponenten/Komponente.h"
#include "UDPServer/UDPCallback.h"
#include "UDPServer/UDPServer.h"
#include "Komponenten/KomponentenController.h"
#include "../header/WebServer/HTMLGenerator.h"
#include "Rpc/RpcServer.h"
#include "Rpc/MqttInterfaceZentrale.h"
#include "Rpc/ZentralenSyncRpcServer.h"

#include "mqtt/client.h"
#include "mqtt/connect_options.h"
#include "mqtt/properties.h"

using namespace std;


/**
 * Class Zentrale is used to manage all components for udp and the webserver for http/tcp.
 */
class Zentrale : public MqttInterfaceZentrale {
private:
    // Server for incoming connections.
    UDPServer udpServer = UDPServer();
    Webserver webserver = Webserver();
    RpcServer rpcServer = RpcServer();
    ZentralenSyncRpcServer zentralenSync = ZentralenSyncRpcServer();
    KomponentenController* komponentenController;
    mqtt::client* mqttServer;

    string mqttServerAddress;
    string mqttClientId;

    unordered_map<string, string> otherZentralen;


    void connectToMqttBroker(int waitTime);

    //Sync functions with other zentralen
    void syncCallWithRpc();



public:
    Zentrale();
    virtual ~Zentrale();
    void start();
    void stop();

    void enableTestmode(bool packetLoss, bool enableOutputData, bool enableMissingmessages);

    void setMqttProperties(string &server, string &id);
    void addOtherZentrale(string name, string ip);
    void sendWithMqtt(string channel, string message) override;

    void sendToOtherZentralen(string message) override;
};


#endif //ZENTRALE_ZENTRALE_H
