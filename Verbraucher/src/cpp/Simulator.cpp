//
// Created by philipp on 30.04.21.
//

#include "../header/Simulator.h"

int Simulator::msgID = 0;

Simulator::Simulator(Verbraucher *verbraucher, string communicationType, int port, string address) {
    this->verbraucher = verbraucher;
    if (communicationType == "UDP"){
        this->interface = new UDPKommunikation(port, address);
    }
}



/**
 *
 */
Simulator::~Simulator() {
    delete verbraucher;
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
    double cons = verbraucher->getLastHourConsumption();
    unsigned long long t = chrono::system_clock::now().time_since_epoch().count();

    string message = messageToJSON(verbraucher->getType(), verbraucher->getName(), verbraucher->getId(), cons, t);
    interface->sendData(message);

    if (msgBuffer.size() > 999)
        msgBuffer.erase(msgBuffer.find(msgID - 1000));
    msgBuffer.insert({msgID, message});

    ++msgID;
    cout << cons << " kW/h" << endl;
}



/**
 *
 */
string Simulator::messageToJSON(string type, string name, int id, double value, unsigned long long time) {
    string message = "{";
    message += "\"type\": ";
    message += "\"" + type + "\", ";
    message += "\"name\": ";
    message += "\"" + name + "\", ";
    message += "\"id\": ";
    message += to_string(id) + ", ";
    message += "\"value\": ";
    message += to_string(value) + ", ";
    message += "\"time\": ";
    message += to_string(time) + ", ";
    message += "\"msgID\": ";
    message += to_string(msgID);
    message += "}";
    return message;
}



/**
 *
 */
void Simulator::stop() {
    this->stopped = true;
}
