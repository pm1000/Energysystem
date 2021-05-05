//
// Created by philipp on 30.04.21.
//

#include "../header/Simulator.h"

Simulator::Simulator(Verbraucher *verbraucher, std::string communicationType, int port, std::string address){
    this->verbraucher = verbraucher;
    if (communicationType == "UDP"){
        this->interface = new UDPKommunikation(port, address);
    }
}

Simulator::~Simulator() {
    delete verbraucher;
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
    double cons = verbraucher->getLastHourConsumption();
    unsigned long long t = std::chrono::system_clock::now().time_since_epoch().count();
    std::string message = messageToJSON(verbraucher->getType(), verbraucher->getName(), verbraucher->getId(), cons, t);
    interface->sendData(message);
    std::cout << cons << " kW/h" << std::endl;
}

std::string Simulator::messageToJSON(std::string type, std::string name, int id, double value, unsigned long long time) {
    std::string message = "{";
    message += "\"type\": ";
    message += "\"" + type + "\", ";
    message += "\"name\": ";
    message += "\"" + name + "\", ";
    message += "\"id\": ";
    message += std::to_string(id) + ", ";
    message += "\"value\": ";
    message += std::to_string(value) + ", ";
    message += "\"time\": ";
    message += std::to_string(time);
    message += "}";
    return message;
}
