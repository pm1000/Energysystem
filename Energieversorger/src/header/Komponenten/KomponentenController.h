//
// Created by philipp on 02.06.21.
//

#ifndef ENERGIEVERSORGER_KOMPONENTENCONTROLLER_H
#define ENERGIEVERSORGER_KOMPONENTENCONTROLLER_H

#include "Komponente.h"
#include "unordered_map"
#include "vector"

using std::unordered_map;
using std::vector;

class KomponentenController {
private:
    unordered_map<int, Komponente*> komponenten;
    mutex mtx;
    //name, id
    std::unordered_map<std::string, int> nameMapping;
    unsigned long long msgCount = 0;
    KomponentenController();
    static KomponentenController* instance;

public:
    static KomponentenController* getInstance();

    void addKomponente(Komponente*);
    vector<Komponente*> getErzeuger();
    vector<Komponente*> getVerbraucher();
    vector<Komponente*> getKomponenten();
};


#endif //ENERGIEVERSORGER_KOMPONENTENCONTROLLER_H
