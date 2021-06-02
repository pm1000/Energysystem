//
// Created by philipp on 02.06.21.
//

#ifndef ENERGIEVERSORGER_CLIENT_H
#define ENERGIEVERSORGER_CLIENT_H

#include "Komponenten/KomponentenController.h"
#include "iostream"
#include "ctime"

using std::cout;
using std::endl;

class Client {
private:
    KomponentenController* komponentenController;


public:
    Client();
    virtual ~Client();

    void printKomponenten();


};


#endif //ENERGIEVERSORGER_CLIENT_H
