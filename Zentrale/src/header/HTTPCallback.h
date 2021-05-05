//
// Created by yabr on 05.05.21.
//

#ifndef ZENTRALE_HTTPCALLBACK_H
#define ZENTRALE_HTTPCALLBACK_H

#include <string>
#include "Komponente.h"

using namespace std;


/**
 * Method for http callbacks to collect data for incoming http/tcp connections
 */
class HTTPCallback {

public:
    virtual Komponente* getKomponenteById (int id) = 0;
    virtual Komponente* getKomponenteByName (string name) = 0;
};


#endif //ZENTRALE_HTTPCALLBACK_H
