//
// Created by philipp on 02.06.21.
//

#include "../header/Client.h"
#include "chrono"

Client::Client(string ip) {
    auto s = std::chrono::system_clock::now().time_since_epoch().count();
    cout << "start:\t" << s << endl;
    komponentenController = KomponentenController::getInstance();

    // Prepare rpc controller and get all components
    this->rpcController = new RpcController();
    this->rpcController->initRpc(ip, 6000);
    auto komponenten = this->rpcController->initKomponenten();

    // Receive all data for all komponents
    for (Komponente* tmp : komponenten) {
        this->komponentenController->addKomponente(tmp);
        this->rpcController->requestKomponentenWerte(tmp);
    }
    auto end = std::chrono::system_clock::now().time_since_epoch().count();
    cout << "end:\t" << end << endl;
    cout << "dauer:\t" << end - s << endl;
}

Client::~Client() {

}

void Client::printKomponenten() {

    vector<Komponente*> erzeuger = komponentenController->getErzeuger();
    vector<Komponente*> verbraucher = komponentenController->getVerbraucher();

    cout << "Erzeuger (Anzahl: " << erzeuger.size() << "): " << endl;
    for (int i = 0; i < erzeuger.size(); ++i){
        cout << "\t ID: " << erzeuger[i]->getId() << " Name: " << erzeuger[i]->getName() << " Type: " <<
            erzeuger[i]->getType() << endl << "\t\t Values: " << endl;
        map<time_t, double> values = erzeuger[i]->getValues();
        for (auto it = values.begin(); it != values.end(); ++it){
            char* timeString  = ctime(&it->first);
            cout << "\t\t\t Zeit: " << timeString << "\t Wert: " << it->second << endl;
        }
    }

    cout << endl << endl;
    cout << "Verbraucher (Anzahl: " << verbraucher.size() << "): " << endl;
    for (int i = 0; i < verbraucher.size(); ++i){
        cout << "\t ID: " << verbraucher[i]->getId() << " Name: " << verbraucher[i]->getName() << " Type: " <<
            verbraucher[i]->getType() << endl << "\t\t Values: " << endl;
        map<time_t, double> values = verbraucher[i]->getValues();
        for (auto it = values.begin(); it != values.end(); ++it){
            char* timeString  = ctime(&it->first);
            cout << "\t\t\t Zeit: " << timeString << "\t Wert: " << it->second << endl;
        }
    }
}
