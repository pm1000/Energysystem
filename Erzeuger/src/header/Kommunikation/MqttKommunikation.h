//
// Created by philipp on 21.06.21.
//

#ifndef ERZEUGER_MQTTKOMMUNIKATION_H
#define ERZEUGER_MQTTKOMMUNIKATION_H

#include "ZentralenKommunikation.h"

class MqttKommunikation : public ZentralenKommunikation {
public:
    MqttKommunikation();
    virtual ~MqttKommunikation();

    void init();
    void sendData(string message) override;
};


#endif //ERZEUGER_MQTTKOMMUNIKATION_H
