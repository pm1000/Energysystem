//
// Created by philipp on 04.05.21.
//

#ifndef ERZEUGER_ZENTRALENKOMMUNIKATION_H
#define ERZEUGER_ZENTRALENKOMMUNIKATION_H


#include "string"

using namespace std;

/**
 *
 */
class ZentralenKommunikation {
protected:
    string address;
    int port{};

public:
    ZentralenKommunikation();
    virtual ~ZentralenKommunikation();

    virtual void sendData(string message) = 0;
};


#endif //ERZEUGER_ZENTRALENKOMMUNIKATION_H
