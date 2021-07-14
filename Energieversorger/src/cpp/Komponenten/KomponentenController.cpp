//
// Created by philipp on 02.06.21.
//

#include "../../header/Komponenten/KomponentenController.h"

KomponentenController* KomponentenController::instance = nullptr;

KomponentenController::KomponentenController() = default;

KomponentenController* KomponentenController::getInstance() {
    if (KomponentenController::instance == nullptr)
        KomponentenController::instance = new KomponentenController();
    return KomponentenController::instance ;
}

vector<Komponente *> KomponentenController::getErzeuger() {
    vector<Komponente*> list;
    for (auto it = komponenten.begin(); it != komponenten.end(); ++it){
        if (it->second->getType() != "Haushalt" && it->second->getType() != "Unternehmen")
            list.push_back(it->second);
    }
    return list;
}

vector<Komponente *> KomponentenController::getVerbraucher() {
    vector<Komponente*> list;
    for (auto it = komponenten.begin(); it != komponenten.end(); ++it){
        if (it->second->getType() == "Haushalt" || it->second->getType() == "Unternehmen")
            list.push_back(it->second);
    }
    return list;
}

std::vector<Komponente *> KomponentenController::getKomponenten() {
    vector<Komponente*> list;
    for (auto it = komponenten.begin(); it != komponenten.end(); ++it){
        list.push_back(it->second);
    }

    return list;
}

void KomponentenController::addKomponente(Komponente * komponente) {
    this->komponenten.insert({komponente->getId(), komponente});
    this->nameMapping.insert({komponente->getName(), komponente->getId()});
}
