#include <iostream>
#include "../header/Client.h"

int main(int argc, char* args[]) {

    string ip;

    // Get all args
    unordered_map<string, string> argsMap;
    for (int i = 1; i < argc; i++) {
        string currentArg = args[i];
        int pos = currentArg.find('=');
        auto arg = make_pair(currentArg.substr(0, pos), currentArg.substr(pos + 1));
        argsMap.insert(arg);
    }

    // Check for ip and port
    if (!argsMap.contains("ip")) {
        cout << "Ziel-Ip (ip=...) muss gegeben sein." << endl;
        return 1;
    }

    // check for ip
    auto iter = argsMap.find("ip");
    if (iter == argsMap.end()) {
        cout << "IP fehlt!" << endl;
        return -1;
    } else
        ip = iter->second;

    Client c(ip);
    c.printKomponenten();

    return 0;
}
