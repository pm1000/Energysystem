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
    int port { 5001 };

public:
    KomponentenUdpSender();
    KomponentenUdpSender(int port);

    void send(Komponente* komponente, string &msg);
};


#endif //ZENTRALE_KOMPONENTENUDPSENDER_H
