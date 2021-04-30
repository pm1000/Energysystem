//
// Created by philipp on 30.04.21.
//

#ifndef VERBRAUCHER_SIMULATOR_H
#define VERBRAUCHER_SIMULATOR_H

#include "Verbraucher.h"
#include "iostream"
#include "unistd.h"
#include "thread"

class Simulator {

private:
    Verbraucher* verbraucher;
    void simulate();
public:
    Simulator(Verbraucher *verbraucher);

    virtual ~Simulator();

    void start();


};


#endif //VERBRAUCHER_SIMULATOR_H
