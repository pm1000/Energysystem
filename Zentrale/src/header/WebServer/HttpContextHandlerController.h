//
// Created by yabr on 05.05.21.
//

#ifndef ZENTRALE_HTTPCONTEXTHANDLERCONTROLLER_H
#define ZENTRALE_HTTPCONTEXTHANDLERCONTROLLER_H


#include <string>
#include <unordered_map>

#include "HttpContextHandler.h"

using namespace std;


/**
 * Controls the spaces for the webspace.
 */
class HttpContextHandlerController {
private:
    unordered_map<string, HttpContextHandler*> context;
    HttpContextHandler* contextNotFoundErrorPage = nullptr;

public:
    HttpContextHandlerController();
    virtual ~HttpContextHandlerController();

    void addContext(string path, HttpContextHandler* handler);
    string getContent(string &path, string &args);
    void setContextNotFoundErrorPage(HttpContextHandler* handler);

};


#endif //ZENTRALE_HTTPCONTEXTHANDLERCONTROLLER_H
