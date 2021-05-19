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
#include "../UDPServer/UDPCallback.h"
#include "vector"


class KomponentenController : public UDPCallback {
private:
    //id,Komponente
    std::unordered_map<int, Komponente*> komponenten;
    std::mutex mtx;
    //name, id
    std::unordered_map<std::string, int> nameMapping;
    KomponentenController() = default;
    static KomponentenController* instance;

public:
    static KomponentenController* getInstance();
    virtual ~KomponentenController();
    void processMessage(std::string message) override;
    Komponente* getKomponenteById(int id);
    Komponente* getKomponenteByName (string name);
    std::vector<std::string> getKomponentenNamen();
    std::vector<int> getKomponentenIDs();
    std::vector<Komponente*> getErzeuger();
    std::vector<Komponente*> getVerbraucher();
};


#endif //ZENTRALE_KOMPONENTENCONTROLLER_H
