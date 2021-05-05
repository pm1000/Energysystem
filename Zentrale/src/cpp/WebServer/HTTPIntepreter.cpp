//
// Created by yabr on 05.05.21.
//

#include "../../header/WebServer/HTTPIntepreter.h"

/**
 * Constructor.
 *
 * @param callback
 * @param sockId
 */
HTTPIntepreter::HTTPIntepreter(HttpContextHandlerController *context, int sockId) : controller(context), sock_id(sockId) {

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
        long endOfHttp = messageReadSoFar.find(string("\n\n"));
        if (endOfHttp > 0) {
            completeMessage = messageReadSoFar.substr(0, endOfHttp);
            messageReadSoFar = messageReadSoFar.substr(endOfHttp + 2);
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

    // Check for GET
    string header, answer;
    if (headers.contains("GET")) {
        answer = processHTTP(headers);
        header = "HTTP/1.1 200 Ok\r\nContent-Type: text/plain\r\nContent-Length: " + to_string(answer.length()) + "\r\n\r\n";
    } else {
        answer = "";
        header = "HTTP/1.1 501 Not Implemented\r\n\r\n";
    }

    // Send the return message
    string message = header + answer;
    int sendResult = send(this->sock_id, message.c_str(), message.size(), 0);
    if (sendResult < 0) {
        int errorNr = errno;
        cerr << "Socket send failed with err no: " << errorNr << endl;
        exit(1);
    }


    // Close the socket and exit this thread
    int closeResult = close(this->sock_id);
    if (closeResult < 0) {
        int errorNr = errno;
        cerr << "Socket call failed with err no: " << errorNr << endl;
        exit(1);
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



/**
 * Process the http headers
 *
 * @param headers
 */
string HTTPIntepreter::processHTTP(unordered_map<string, string> &headers) {

    string path = headers.at("GET");
    path = path.substr(0, path.find(' '));

    long argStart = path.find('?');
    string args = (argStart == -1) ? "" : path.substr(argStart + 1);
    path = path.substr(0, argStart);

    return this->controller->getContent(path, args);
}


