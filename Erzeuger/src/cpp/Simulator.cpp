//
// Created by philipp on 04.05.21.
//

#include "../header/Simulator.h"


/**
 *
 */
Simulator::Simulator(Erzeuger *erzeuger, std::string communicationType, int port, std::string address) {
    this->erzeuger = erzeuger;
    if (communicationType == "UDP") {
        this->interface = new UDPKommunikation(port, address);
    }
}



/**
 *
 */
Simulator::~Simulator() {
    delete erzeuger;
}



/**
 *
 */
void Simulator::start() {
    try {
        while(!stopped) {
            this->simulate();
            sleep(2);
        }

    } catch (exception &e) {
        cout << e.what() << endl;
    }
}



/**
 *
 */
void Simulator::simulate() {
    double cons = erzeuger->getLastHourGeneration();
    unsigned long long t = chrono::system_clock::now().time_since_epoch().count();
    string message = messageToJSON(erzeuger->getType(), erzeuger->getName(), erzeuger->getID(), cons, t);
    interface->sendData(message);
    cout << cons << " kW/h" << endl;
}



/**
 *
 */
string Simulator::messageToJSON(string type, string name, int id, double value, unsigned long long time) {
    std::string message = "{";
    message += "\"type\": ";
    message += "\"" + type + "\", ";
    message += "\"name\": ";
    message += "\"" + name + "\", ";
    message += "\"id\": ";
    message += to_string(id) + ", ";
    message += "\"value\": ";
    message += to_string(value) + ", ";
    message += "\"time\": ";
    message += to_string(time);
    message += "}";
    return message;
}



/**
 *
 */
void Simulator::stop() {
    this->stopped = true;
}
