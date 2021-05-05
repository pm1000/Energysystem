//
// Created by yabr on 05.05.21.
//

#ifndef ZENTRALE_HTTPDATACALLBACK_H
#define ZENTRALE_HTTPDATACALLBACK_H

#include <string>
#include "../Komponenten/Komponente.h"

using namespace std;


/**
 * Method for http callbacks to collect data for incoming http/tcp connections
 */
class HttpDataCallback {

public:
    virtual Komponente* getKomponenteById (int id) = 0;
    virtual Komponente* getKomponenteByName (string name) = 0;
};


#endif //ZENTRALE_HTTPDATACALLBACK_H
