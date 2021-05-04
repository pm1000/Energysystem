//
// Created by philipp on 04.05.21.
//

#include "../header/Simulator.h"

Simulator::Simulator(Erzeuger *erzeuger, std::string communicationType, int port, std::string address){
this->erzeuger = erzeuger;
if (communicationType == "UDP"){
this->interface = new UDPKommunikation(port, address);
}
}

Simulator::~Simulator() {
    delete erzeuger;
}

void Simulator::start() {
    try {
        while(true) {
            std::thread t1(&Simulator::simulate, this);
            sleep(2);
            t1.join();
        }

    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void Simulator::simulate() {
    double cons = erzeuger->getLastHourGeneration();
    std::string message = messageToJSON(erzeuger->getType(), erzeuger->getName(), erzeuger->getID(), cons);
    interface->sendData(message);
    std::cout << cons << " kW/h" << std::endl;
}

std::string Simulator::messageToJSON(std::string type, std::string name, int id, double value) {
    std::string message = "{";
    message += "\"type\": ";
    message += "\"" + type + "\", ";
    message += "\"name\": ";
    message += "\"" + name + "\", ";
    message += "\"id\": ";
    message += std::to_string(id) + ",";
    message += "\"value\": ";
    message += std::to_string(value);
    message += "}";
    return message;
}