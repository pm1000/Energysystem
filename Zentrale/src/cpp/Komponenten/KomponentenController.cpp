//
// Created by philipp on 05.05.21.
//

#include "../../header/Komponenten/KomponentenController.h"

KomponentenController* KomponentenController::instance = nullptr;

KomponentenController::~KomponentenController() {

}

void KomponentenController::processMessage(std::string message) {
    //format {"type": "Unternehmen", "name": "FLEISCHER", "id": 123,"value": 2006.550000}
    std::string type;
    std::string name;
    int id;
    double value;
    unsigned long long time;
    try{
        //get type
        std::size_t pos = message.find("\"type\"");
        pos += 9;
        type = message.substr(pos, message.substr(pos,message.length() - pos).find_first_of('"'));

        //get name
        pos = message.find("\"name\"");
        pos += 9;
        name = message.substr(pos, message.substr(pos,message.length() - pos).find_first_of('"'));

        //get id
        pos = message.find("\"id\"");
        pos += 6;
        std::string tmp;
        int i = pos;
        while (i < message.size() && message[i] >= '0' && message[i] <= '9'){
            tmp += message[i];
            ++i;
        }
        id = std::stoi(tmp);

        //get value
        pos = message.find("\"value\"");
        pos += 9;
        i = pos;
        tmp = "";

        while (i < message.size() && ((message[i] >= '0' && message[i] <= '9') || message[i] == '.')){
            tmp += message[i];
            ++i;
        }
        value = std::stod(tmp);

        //get time
        pos = message.find("\"time\"");
        pos += 8;
        i = pos;
        tmp = "";

        while (i < message.size() && message[i] >= '0' && message[i] <= '9'){
            tmp += message[i];
            ++i;
        }
        time = std::stoull(tmp);

        mtx.lock();
        auto it = komponenten.find(id);
        if (it == komponenten.end()){
            Komponente* k;
            if (type == "Unternehmen" || type == "Haushalt") {
                k = new Verbraucher(id, name, type);
            } else {
                k = new Erzeuger(type, name, id);
            }
            nameMapping.insert({name,id});
            komponenten.insert({id,k});
            k->addNewValue(time, value);

        } else{
            it->second->addNewValue(time, value);
        }
        mtx.unlock();

        std::cout << "Type: " << type << "\tID: " << id << "\tName: " << name << "\tValue: " << value
                    << "\tTime: " << time << std::endl;
    }catch (std::exception &e){
        std::cerr <<"Failed to process the message: " << message << std::endl << e.what() << std::endl;
    }
}



Komponente *KomponentenController::getKomponenteById(int id) {
    auto it = komponenten.find(id);
    if (it == komponenten.end())
        return nullptr;
    return it->second;
}



Komponente *KomponentenController::getKomponenteByName(string name) {

    auto it = nameMapping.find(name);
    if (it == nameMapping.end())
        return nullptr;
    else{
        auto it2 = komponenten.find(it->second);
        if (it2 == komponenten.end())
            return nullptr;
        return it2->second;
    }
}

std::vector<std::string> KomponentenController::getKomponentenNamen() {
    std::vector<std::string> names;
    for (auto it = nameMapping.begin(); it != nameMapping.end(); ++it)
        names.push_back(it->first);
    return names;
}

std::vector<int> KomponentenController::getKomponentenIDs() {
    std::vector<int> ids;
    for (auto it = nameMapping.begin(); it != nameMapping.end(); ++it)
        ids.push_back(it->second);
    return ids;
}

std::vector<Komponente *> KomponentenController::getErzeuger() {
    std::vector<Komponente*> list;
    for (auto it = komponenten.begin(); it != komponenten.end(); ++it){
        if (it->second->getType() != "Haushalt" && it->second->getType() != "Unternehmen")
            list.push_back(it->second);
    }
    return list;
}

std::vector<Komponente *> KomponentenController::getVerbraucher() {
    std::vector<Komponente*> list;
    for (auto it = komponenten.begin(); it != komponenten.end(); ++it){
        if (it->second->getType() == "Haushalt" || it->second->getType() == "Unternehmen")
            list.push_back(it->second);
    }
    return list;
}

KomponentenController* KomponentenController::getInstance() {
    if (KomponentenController::instance == nullptr)
        KomponentenController::instance = new KomponentenController();
    return KomponentenController::instance ;
}
