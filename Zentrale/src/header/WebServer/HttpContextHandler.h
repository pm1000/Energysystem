//
// Created by yabr on 05.05.21.
//

#ifndef ZENTRALE_HTTPCONTEXTHANDLER_H
#define ZENTRALE_HTTPCONTEXTHANDLER_H

#include <string>

using namespace std;

/**
 * Interface for context handlers
 */
class HttpContextHandler {
private:


public:
    virtual string getContent(string &args) = 0;

};


#endif //ZENTRALE_HTTPCONTEXTHANDLER_H
