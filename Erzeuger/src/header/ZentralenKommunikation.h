//
// Created by philipp on 04.05.21.
//

#ifndef ERZEUGER_ZENTRALENKOMMUNIKATION_H
#define ERZEUGER_ZENTRALENKOMMUNIKATION_H


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



#endif //ERZEUGER_ZENTRALENKOMMUNIKATION_H
