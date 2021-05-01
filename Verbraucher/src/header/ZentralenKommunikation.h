//
// Created by philipp on 01.05.21.
//

#ifndef VERBRAUCHER_ZENTRALENKOMMUNIKATION_H
#define VERBRAUCHER_ZENTRALENKOMMUNIKATION_H

#include "string"

class ZentralenKommunikation {
protected:
    std::string address;
    int port;

public:
    ZentralenKommunikation();

    virtual ~ZentralenKommunikation();
    virtual void sendData(std::string message) = 0;

};


#endif //VERBRAUCHER_ZENTRALENKOMMUNIKATION_H
