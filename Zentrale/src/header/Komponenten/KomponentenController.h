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
#include "../WebServer/HTTPCallback.h"
#include "../UDPServer/UDPCallback.h"
#include "vector"

class KomponentenController : public UDPCallback, public HTTPCallback {
    //todo for yannick: mach das ding mal als singelton pattern
private:
    std::unordered_map<int, Komponente*> komponenten;
    std::mutex mtx;
    std::unordered_map<std::string, int> nameMapping;

public:
    KomponentenController();
    virtual ~KomponentenController();

    void processMessage(std::string message) override;
    Komponente* getKomponenteById(int id) override;
    Komponente* getKomponenteByName (string name) override;
    std::vector<std::string> getKomponentenNamen();
    std::vector<int> getKomponentenIDs();

};


#endif //ZENTRALE_KOMPONENTENCONTROLLER_H
