//
// Created by philipp on 05.07.21.
//

#ifndef LOADBALANCER_ZENTRALE_H
#define LOADBALANCER_ZENTRALE_H

#include "string"
#include "vector"

using std::vector;
using std::string;

class Zentrale {
private:

    string ip;
    int udpPort;
    int tcpPort;
    vector<string> mqttAddresses;
    string mqttClientId;
    int id;

public:
    Zentrale(const string &ip, const vector<string> &mqttAddresses, const string &mqttClientId, int id);
    virtual ~Zentrale();


};


#endif //LOADBALANCER_ZENTRALE_H
