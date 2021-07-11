#include <csignal>
#include "../header/Zentrale.h"

/*
 * Global variables
 */
Zentrale* zentrale;

/**
 * Function to execute when SIGTERM arrives
 */
void sigTerm (int sig) {
    zentrale->stop();
}



int main(int argc, char* args[]) {

    // Get all args
    unordered_map<string, string> argsMap;
    for (int i = 1; i < argc; i++) {
        string currentArg = args[i];
        int pos = currentArg.find('=');
        auto arg = make_pair(currentArg.substr(0, pos), currentArg.substr(pos + 1));
        argsMap.insert(arg);
    }

    // Check for mqttAddress and mqttId
    if (!argsMap.contains("mqttServerAddress") || !argsMap.contains("mqttClientId")) {
        cerr << "mqttAddress parameter and mqttClientId must be set as parameter.";
        exit(1);
    }


    // Create the zentrale
    zentrale = new Zentrale();
    zentrale->setMqttProperties(argsMap.at("mqttServerAddress"), argsMap.at("mqttClientId"));


    //expected format zentrale1=102.234.123.121 zentrale2=192.168.178.1
    for (const auto& it : argsMap) {
        if (it.first.find("zentrale") <= it.first.length()) {
            zentrale->addOtherZentrale(it.first, it.second);
        }
    }


    // Register a handler for programm termination
    signal(SIGTERM, sigTerm);

    // Uncomment to enable testmode
    zentrale->enableTestmode(false, true, true);

    // Start the application
    zentrale->start();


    return 0;
}
