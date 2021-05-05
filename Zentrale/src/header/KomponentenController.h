//
// Created by philipp on 05.05.21.
//

#ifndef ZENTRALE_KOMPONENTENCONTROLLER_H
#define ZENTRALE_KOMPONENTENCONTROLLER_H
#include "Komponente.h"
#include "unordered_map"
#include "iostream"
#include "Erzeuger.h"
#include "Verbraucher.h"
#include "mutex"

class KomponentenController {
private:
    std::unordered_map<int, Komponente*> komponenten;
    std::mutex mtx;


public:
    KomponentenController();
    virtual ~KomponentenController();

    void processMessage(std::string message);
    Komponente* getKomponenteByID(int id);

};


#endif //ZENTRALE_KOMPONENTENCONTROLLER_H
