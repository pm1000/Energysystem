//
// Created by philipp on 05.07.21.
//

#ifndef LOADBALANCER_ZENTRALENCONTROLLER_H
#define LOADBALANCER_ZENTRALENCONTROLLER_H

#include "vector"
#include "Zentrale.h"
#include "memory"
#include "mutex"

using std::vector;
using std::shared_ptr;
using std::unique_ptr;
using std::mutex;

class ZentralenController {
private:
    int zentralenCount;
    vector<shared_ptr<Zentrale>> zentralen;
    vector<shared_ptr<Zentrale>> activeZentralen;
    ZentralenController();
    static shared_ptr<ZentralenController> instance;
    mutex m;

public:
    static shared_ptr<ZentralenController> getInstance();

    virtual ~ZentralenController();
    void addZentrale(shared_ptr<Zentrale> zentrale);
    void zentraleNotActive(shared_ptr<Zentrale> zentrale);

    shared_ptr<Zentrale> getActiveZentraleAt(int loc);
    int getZentralenCount();
};


#endif //LOADBALANCER_ZENTRALENCONTROLLER_H
