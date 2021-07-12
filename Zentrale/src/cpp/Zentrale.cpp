//
// Created by philipp on 30.04.21.
//

#include <onlyZentrale.grpc.pb.h>
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

    // Sync
    class SyncCall : public HttpContextHandler {
    private:
        Zentrale* z;
    public:
        SyncCall(Zentrale* z) : z(z) {}
        string getContent(string &args) override {
            thread t(&Zentrale::syncCallWithRpc, z);
            t.detach();
            return "Started sync in new thread.";
        }
    };


    // Init all services
    this->zentralenSync.init(this, this->komponentenController, 6001);

    this->komponentenController->setZentraleInterface(this);

    this->udpServer.setPacketLoss(false);
    this->udpServer.setCallback(this->komponentenController);
    this->udpServer.init(5000);

    this->webserver.setContextNotFoundErrorPage(new ErrorHandler());
    this->webserver.addContext("/", new MainPage());
    this->webserver.addContext("/Detail", new SubPage());
    this->webserver.addContext("/SetStatus", new SetStatus());
    this->webserver.addContext("/Sync", new SyncCall(this));
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

        // MQTT connection
        connectToMqttBroker(3);

        thread syncThread(ref(this->zentralenSync));

        // First time start try to sync with all other known zentralen.
        this->syncCallWithRpc();

        // Then start all services
        thread webServerThread(ref(this->webserver));
        thread udpServerThread(ref(this->udpServer));
        thread rpcServerThread(ref(this->rpcServer));

        // Subscribe to topics
        // Use mqttClientId as the topic to subscribe
        this->mqttServer->subscribe(this->mqttClientId + "/#");

        // Sync to other Zentralen

        // wait for all threads to join
        webServerThread.join();
        udpServerThread.join();
        rpcServerThread.join();
        syncThread.join();
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
    this->zentralenSync.stop();
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



/**
 *
 */
void Zentrale::connectToMqttBroker(int waitTime) {

    // mqtt stuff
    try {
        sleep(waitTime);
        this->mqttServer = new mqtt::client(this->mqttServerAddress, this->mqttClientId);
        auto connOpts = mqtt::connect_options_builder()
                .automatic_reconnect(true)
                .clean_session(true)
                .finalize();
        this->mqttServer->set_callback(*this->komponentenController);

        // Try the connection
        this->mqttServer->connect(connOpts);

    } catch (exception &e) {
        cerr << "[MQTT] Connection not possible." << endl << e.what();
        if (waitTime > 30)
            exit(-1);
        waitTime *= 2;
        cout << "Retry connection in " << waitTime << " seconds." << endl;
        connectToMqttBroker(waitTime);
    }
}



/**
 *
 */
void Zentrale::addOtherZentrale(string name, string ip) {
    this->otherZentralen.insert({name, ip});
}



/**
 *
 */
void Zentrale::syncCallWithRpc() {

    for (const auto &ip : this->otherZentralen) {

        // Create the stub
        std::unique_ptr<ZentraleRpc::ZentraleKoordination::Stub> stub;
        try {
            string address = ip.second + ":6001";
            auto channel = grpc::CreateChannel(address, grpc::InsecureChannelCredentials());
            stub = std::move(ZentraleRpc::ZentraleKoordination::NewStub(channel));
        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
            continue;
        }



        // Get all Komponenten IDs
        grpc::ClientContext context;
        ZentraleRpc::Source request;
        request.set_targetchannel(this->mqttClientId + "/zentrale/");
        ZentraleRpc::Empty response;
        auto result = stub->RequestSync(&context, request, &response);

        // Get result
        if (!result.ok()) {
            std::cerr << result.error_message() << std::endl;
            continue;
        }
    }
}



/**
 *
 */
void Zentrale::sendWithMqtt(string channel, string message) {

    try {
        mqtt::message msg(channel, message);
        msg.set_qos(2);

        this->mqttServer->publish(msg);
    } catch (exception &e) {
        cerr << e.what() << endl;
    }
}



/**
 *
 */
void Zentrale::sendToOtherZentralen(string message) {

    for (const auto &zentraleIT : this->otherZentralen) {

        this->sendWithMqtt(zentraleIT.first + "/zentrale/sync", message);
    }
}