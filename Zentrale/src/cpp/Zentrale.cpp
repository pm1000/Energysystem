//
// Created by philipp on 30.04.21.
//

#include "../header/Zentrale.h"

/**
 * Constructor
 */
Zentrale::Zentrale() {

    // Create komponentenController
    komponentenController = new KomponentenController();

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
            return "Main-Page";
        }
    };

    // Init all services
    this->udpServer.setCallback(this->komponentenController);
    this->udpServer.init(5000);

    this->webserver.setContextNotFoundErrorPage(new ErrorHandler());
    this->webserver.addContext("/", new MainPage());
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
        webServerThread.detach();
        udpServerThread.detach();
    } catch (system_error &e) {
        cerr << e.what() << endl;
        exit(1);
    }


    // Wait for all threads to be started
    this_thread::sleep_for(chrono::milliseconds(500));


    // User input
    string input;
    do {
        cout << "Commands: quit" << endl;
        cout << " > ";
        getline(cin, input);

    } while (input != "quit");


    // Stop everything here
    cout << "[Zentrale] Stopping all services." << endl;
    this->webserver.stop();
    this->udpServer.stop();


    // Clear all fields
    //cout << "[Zentrale] Clearing all fields." << endl;
}
