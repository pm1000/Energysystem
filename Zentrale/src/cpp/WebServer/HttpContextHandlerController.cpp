//
// Created by yabr on 05.05.21.
//

#include "../../header/WebServer/HttpContextHandlerController.h"



/**
 * Constructor
 */
HttpContextHandlerController::HttpContextHandlerController() = default;



/**
 * Destructor
 */
HttpContextHandlerController::~HttpContextHandlerController() = default;



/**
 * Add a handler to the webserver
 *
 * @param path
 * @param handler
 */
void HttpContextHandlerController::addContext(string path, HttpContextHandler *handler) {

    if (this->context.contains(path)) {
        this->context.at(path) = handler;
    } else {
        this->context.insert(make_pair(path, handler));
    }
}



/**
 * Get content from the handler
 *
 * @param content
 */
string HttpContextHandlerController::getContent(string &path, string &args) {
    if (this->context.contains(path)) {
        return this->context.at(path)->getContent(args);
    } else {
        return this->contextNotFoundErrorPage->getContent(args);
    }
}



/**
 * Set the page for error 404
 *
 * @param handler
 */
void HttpContextHandlerController::setContextNotFoundErrorPage(HttpContextHandler *handler) {
    this->contextNotFoundErrorPage = handler;
}
