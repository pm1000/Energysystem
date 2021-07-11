//
// Created by philipp on 30.04.21.
//

#include "../header/Simulator.h"

int Simulator::msgID = 0;

Simulator::Simulator(Verbraucher *verbraucher, string communicationType, int port, string address, string brokerIp, string brokerChannel) {
    this->verbraucher = verbraucher;
    if (communicationType == "UDP") {
        this->interface = new UDPKommunikation(port, address);
    } else if (communicationType == "MQTT") {
        this->interface = new MqttKommunikation(brokerIp, brokerChannel, verbraucher->getName());
    } else {
        cout << "Unknown communication type: \"" + communicationType +"\". Only UDP or MQTT are valid" << endl;
        exit(5);
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
    time_t t = time(nullptr);

    string message = messageToJSON(verbraucher->getType(), verbraucher->getName(), verbraucher->getId(),
                                   cons, t);
    mtx.lock();
    interface->sendData(message);

    if (msgBuffer.size() > 999)
        msgBuffer.erase(msgBuffer.find(msgID - 1000));
    msgBuffer.insert({msgID, message});
    mtx.unlock();

    ++msgID;
}



/**
 *
 */
string Simulator::messageToJSON(string type, string name, int id, double value, time_t time) {
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

    //if communication type is mqtt then the ip needs to be send as well (needed for rpc calls from the Zentrale)
    MqttKommunikation* mqtt = dynamic_cast<MqttKommunikation*>(this->interface);
    if (mqtt != nullptr) {
        message += ", \"ip\": ";
        message += mqtt->getIp();
    }

    message += "}";
    return message;
}



/**
 *
 */
void Simulator::stop() {
    this->stopped = true;
}

void Simulator::processMessage(string ip, std::string string1) {
    size_t pos = string1.find("\"msgID\":");
    pos += 9;
    string tmp;

    while (pos < string1.size() && string1[pos] >= '0' && string1[pos] <= '9'){
        tmp += string1[pos];
        ++pos;
    }

    int id = stoi(tmp);

    mtx.lock();
    auto it = msgBuffer.find(id);

    if (it != msgBuffer.end()){
        interface->sendData(it->second);
        mtx.unlock();

    } else {
        mtx.unlock();
        cerr << "Message Nr " << id << " is not in the buffer." << endl;
    }

}
