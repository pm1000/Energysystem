//
// Created by yabr on 19.05.21.
//

#ifndef ZENTRALE_KOMPONENTENUDPSENDER_H
#define ZENTRALE_KOMPONENTENUDPSENDER_H

#include <string>
#include "UDPSender.h"
#include "../Komponenten/Komponente.h"


using namespace std;

/**
 *
 */
class KomponentenUdpSender : public UDPSender {
public:
    void send(string ip, int port, string message) override;
    void send(Komponente* komponente, string msg);

    std::thread komponentenThreadSend(Komponente* k, string msg);
};


#endif //ZENTRALE_KOMPONENTENUDPSENDER_H
