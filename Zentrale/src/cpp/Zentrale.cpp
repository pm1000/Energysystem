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
    this->webserver.init(9000);
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
        webServerThread.join();
        udpServerThread.join();
    } catch (system_error &e) {
        cerr << e.what() << endl;
        exit(1);
    }
}



/**
 * Stop the application
 */
void Zentrale::stop() {
    cout << "[Zentrale] Stopping all services." << endl;
    this->webserver.stop();
    this->udpServer.stop();
}



/**
 *
 */
void Zentrale::enableTestmode(bool packetLoss, bool enableOutputData, bool enableMissingmessages) {
    this->udpServer.setPacketLoss(packetLoss);
    this->komponentenController->setTestMode(enableOutputData, enableMissingmessages);
}
