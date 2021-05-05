//
// Created by yabr on 05.05.21.
//

#include "../header/HTTPIntepreter.h"

/**
 * Constructor.
 *
 * @param callback
 * @param sockId
 */
HTTPIntepreter::HTTPIntepreter(HTTPCallback *callback, int sockId) : callback(callback), sock_id(sockId) {

}



/**
 * Destructor.
 */
HTTPIntepreter::~HTTPIntepreter() = default;



/**
 * Method to start in a thread.
 */
void HTTPIntepreter::run() {

    // Save the message
    unordered_map<string, string> headers;
    char buffer[MESSAGE_SIZE];
    string messageReadSoFar, completeMessage;
    bool messageComplete= false;


    while (!messageComplete) {
        int readResult = recv(this->sock_id, &buffer, MESSAGE_SIZE, 0);
        if (readResult < 0) {
            int errorNr = errno;
            cerr << "Socket read failed with err no: " << errorNr << endl;
            close(this->sock_id);
            return;
        }

        messageReadSoFar.append(buffer, readResult);
        messageReadSoFar.erase(remove(messageReadSoFar.begin(), messageReadSoFar.end(), '\r'), messageReadSoFar.end());
        unsigned long endOfHttp = messageReadSoFar.find("\n\n");
        if (messageReadSoFar.find("\n\n") > 0) {
            completeMessage = messageReadSoFar.substr(0, endOfHttp);
            messageReadSoFar = messageReadSoFar.substr(endOfHttp);
            messageComplete = true;
        }
    }

    // Message read complete
    stringstream ss(completeMessage);
    string currentLine;
    while (getline(ss, currentLine, '\n')) {

        if (currentLine.empty()) {
            messageComplete = true;
        } else {

            unsigned long firstWhiteSpace = currentLine.find(' ', 0);
            string key = currentLine.substr(0, firstWhiteSpace);
            key.erase(remove(key.begin(), key.end(), ':'), key.end());
            string value = currentLine.substr(firstWhiteSpace + 1);

            pair<string, string> header(key, value);
            headers.insert(header);
        }
    }
}



/**
 *
 *
 * @return
 */
void HTTPIntepreter::operator()() {

    // Forward to the run function.
    this->run();
}


