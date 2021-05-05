//
// Created by philipp on 05.05.21.
//

#include "../header/KomponentenController.h"

KomponentenController::KomponentenController() {

}

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

    // TODO: Implement function -> Philipp, this is your task :D
    return nullptr;
}
