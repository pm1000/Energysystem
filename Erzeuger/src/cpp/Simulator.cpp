//
// Created by philipp on 04.05.21.
//

#include "../header/Simulator.h"

int Simulator::msgID = 0;


/**
 *
 */
Simulator::Simulator(Erzeuger *erzeuger, const std::string& communicationType, int port, std::string address) {
    this->erzeuger = erzeuger;
    rpcController.initRpc(erzeuger, 7000);
    if (communicationType == "UDP") {
        this->interface = new UDPKommunikation(port, address);
    }
}



/**
 *
 */
Simulator::~Simulator() {
    delete erzeuger;
    delete interface;
}



/**
 *
 */
void Simulator::start() {
    try {
        thread rpcThread(ref(this->rpcController));
        while(!stopped) {
            this->simulate();
            sleep(2);
        }
        rpcThread.join();
    } catch (exception &e) {
        cout << e.what() << endl;
    }
}



/**
 *
 */
void Simulator::simulate() {
    double cons = erzeuger->getLastHourGeneration();
    time_t t = time(nullptr);

    string message = messageToJSON(erzeuger->getType(), erzeuger->getName(), erzeuger->getID(), cons, t);

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
    this->rpcController.stop();
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
        cout << "Message Nr " << msgID << "\tresend" << endl;
    } else {
        mtx.unlock();
        cerr << "Message Nr " << id << " is not in the buffer." << endl;
    }

}

void Simulator::startMissingMsgTest(int msgCount) {

    for (int i = 0; i < msgCount; ++i){
        this->simulate();
        sleep(2);
        cout << "send Message Nr " << i << endl;
    }

    cout << msgCount << " Nachrichten an die Zentrale gesendet." << endl;
}



/**
 *
 */
void Simulator::startPerformanceTest(int msgCount) {

    cout << "Start testing. Timestamp: " << to_string(time(nullptr)) << endl;
    for (int i = 0; i < msgCount; i++) {
        this->simulate();
        usleep(1);
    }
    cout << "End testing. Timestamp: " << to_string(time(nullptr)) << endl;
}
