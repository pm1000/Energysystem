//
// Created by philipp on 30.04.21.
//

#include "../header/Zentrale.h"

/**
 * Constructor
 */
Zentrale::Zentrale() {

    // Create komponentenController
    komponentenController = KomponentenController::getInstance();

    // Create default context
    class ErrorHandler: public HttpContextHandler {
    public:
        string getContent(string &args) override {
            return "Error 404: Page not found.";
        }
    };

    // Main Page
    class MainPage : public HttpContextHandler {
    public:
        string getContent(string &args) override {
            HTMLGenerator html;
            return html.generateMainPage();
        }
    };

    //Set Status
    class SetStatus : public HttpContextHandler {
    public:
        string getContent(string &args) override {
            HTMLGenerator htmlGenerator;
            int id;
            size_t pos = args.find("=");
            if (pos != std::string::npos) {
                pos++;
                string tmp;
                while (pos < args.length()){
                    tmp += args[pos];
                    ++pos;
                }
                id = stoi(tmp);
            } else
                return "";
            return htmlGenerator.handleStatusChange(id);
        }
    };

    class SubPage : public HttpContextHandler {
    public:
        string getContent(string &args) override {
            HTMLGenerator html;

            //format: name=FLEISCHER&history=true
            //keywords: name, history
            string name;
            bool history = true;

            size_t pos = args.find("name");
            if (pos != std::string::npos) {
                pos += 5;
                while (pos < args.length() && args[pos] != '&') {
                    name += args[pos];
                    ++pos;
                }
            }

            string tmp;
            pos = args.find("history");
            if (pos != std::string::npos){
                pos += 9;
                while (pos < args.length() && args[pos] != '&'){
                    tmp += args[pos];
                    ++pos;
                }
            }

            return html.generateSubPage(name, history);
        }
    };


    // Init all services
    this->udpServer.setPacketLoss(false);
    this->udpServer.setCallback(this->komponentenController);
    this->udpServer.init(5000);

    this->webserver.setContextNotFoundErrorPage(new ErrorHandler());
    this->webserver.addContext("/", new MainPage());
    this->webserver.addContext("/Detail", new SubPage());
    this->webserver.addContext("/SetStatus", new SetStatus());
    this->webserver.init(9000);

    this->rpcServer.init(this->komponentenController, 6000);
};



/**
 * Destructor.
 */
Zentrale::~Zentrale(){
    delete komponentenController;
};



/**
 * Entrypoint for the code.
 */
void Zentrale::start() {

    // Console log
    cout << "[Zentrale] Start function called. Starting threads." << endl << endl;


    // Start threads
    try {
        thread webServerThread(ref(this->webserver));
        thread udpServerThread(ref(this->udpServer));
        thread rpcServerThread(ref(this->rpcServer));

        // mqtt stuff
        try {
            this->mqttServer = new mqtt::client(this->mqttServerAddress, this->mqttClientId);
            auto connOpts = mqtt::connect_options_builder()
                    .automatic_reconnect(true)
                    .clean_session(false)
                    .finalize();
            this->mqttServer->set_callback(*this->komponentenController);

            // Try the connection
            this->mqttServer->connect(connOpts);

            // Subscribe to topics
            this->mqttServer->subscribe("komponente/#");

        } catch (exception &e) {
            cerr << "[MQTT] Connection not possible." << endl << e.what();
            exit(1);
        }

        // wait for all threads to join
        webServerThread.join();
        udpServerThread.join();
        rpcServerThread.join();
    } catch (system_error &e) {
        cerr << e.what() << endl;
        exit(1);
    }

    cout << "Insgesamt wurden " << komponentenController->getMsgCount() << " Nachrichten verarbeitet" << endl;

    for (auto it = komponentenController->getKomponenten().begin(); it != komponentenController->getKomponenten().end(); ++it){
        cout << "Komponente: " << it->second->getName() << "\t gespeicherte Nachrichten: \t" << it->second->getMsgCount() << endl;
    }

}



/**
 * Stop the application
 */
void Zentrale::stop() {
    cout << "[Zentrale] Stopping all services." << endl;
    this->webserver.stop();
    this->udpServer.stop();
    this->rpcServer.stop();
    try {
        this->mqttServer->disconnect();
    } catch (exception &e) {
        cerr << e.what();
    }
}



/**
 *
 */
void Zentrale::enableTestmode(bool packetLoss, bool enableOutputData, bool enableMissingmessages) {
    this->udpServer.setPacketLoss(packetLoss);
    this->komponentenController->setTestMode(enableOutputData, enableMissingmessages);
}



/*
 *
 */
void Zentrale::setMqttProperties(string &server, string &id) {
    this->mqttServerAddress = server;
    this->mqttClientId = id;
}
