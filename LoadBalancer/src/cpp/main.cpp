#include <iostream>
#include "../header/WebServer/TcpServer.h"
#include "../header/Zentrale/ZentralenController.h"


int main(int argc, char* args[]) {

    // Get all args
    unordered_map<string, string> argsMap;
    for (int i = 1; i < argc; i++) {
        string currentArg = args[i];
        int pos = currentArg.find('=');
        auto arg = make_pair(currentArg.substr(0, pos), currentArg.substr(pos + 1));
        argsMap.insert(arg);
    }

    //expected format zentrale1=102.234.123.121 zentrale2 = 192.168.178.1
    shared_ptr<ZentralenController> zentralenController = ZentralenController::getInstance();
    int count = 1;
    string name = "zentrale";
    while (argsMap.contains(name + to_string(count))) {
        auto it = argsMap.find(name + to_string(count));
        shared_ptr<Zentrale> zentrale(new Zentrale(it->second, it->first));
        zentralenController->addZentrale(zentrale);
        ++count;
    }

    int sourcePort = 0;
    int targetPort = 0;
    auto it = argsMap.find("sourcePort");
    if (it != argsMap.end()) {
        sourcePort = stoi(it->second);
    } else {
        cerr << "Expected sourcePort" << endl;
        exit(1);
    }

    it = argsMap.find(("targetPort"));
    if (it != argsMap.end()) {
        targetPort = stoi(it->second);
    } else {
        cerr << "Expected targetPort" << endl;
        exit(1);
    }

    TcpServer tcpServer;
    tcpServer.init(sourcePort, targetPort);
    tcpServer();

    return 0;
}
