//
// Created by philipp on 21.06.21.
//

#ifndef ERZEUGER_MQTTKOMMUNIKATION_H
#define ERZEUGER_MQTTKOMMUNIKATION_H

#include "ZentralenKommunikation.h"
#include <iostream>
#include <cstring>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "mqtt/client.h"
#include "mqtt/connect_options.h"
#include "mqtt/properties.h"


class MqttKommunikation : public ZentralenKommunikation {
private:
    string ip;
    mqtt::client* mqttClient;
    string name;
    void findOutLocalIp();

public:
    MqttKommunikation(string zentralenIP, string name);
    virtual ~MqttKommunikation();

    const string &getIp() const;
    void sendData(string message) override;
};


#endif //ERZEUGER_MQTTKOMMUNIKATION_H
