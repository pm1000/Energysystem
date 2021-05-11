//
// Created by philipp on 01.05.21.
//

#ifndef VERBRAUCHER_ZENTRALENKOMMUNIKATION_H
#define VERBRAUCHER_ZENTRALENKOMMUNIKATION_H

#include "string"

using namespace std;

/**
 *
 */
class ZentralenKommunikation {
protected:
    string address;
    int port;

public:
    ZentralenKommunikation();
    virtual ~ZentralenKommunikation();

    virtual void sendData(string message) = 0;
};


#endif //VERBRAUCHER_ZENTRALENKOMMUNIKATION_H
