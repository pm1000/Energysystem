//
// Created by philipp on 05.07.21.
//

#include "../../header/Zentrale/Zentrale.h"

Zentrale::Zentrale(const string &ip, const vector<string> &mqttAddresses, const string &mqttClientId, int id) {
    this->ip = ip;
    this->mqttAddresses = mqttAddresses;
    this->mqttClientId = mqttClientId;
    this->id = id;
    this->udpPort = 5000;
    this->tcpPort = 9000;
}

Zentrale::~Zentrale() {

}
