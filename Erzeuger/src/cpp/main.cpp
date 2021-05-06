#include <iostream>

#include "../header/Erzeuger.h"
#include "../header/Atom.h"
#include "../header/Wind.h"
#include "../header/Solar.h"
#include "../header/Kohle.h"
#include "../header/Simulator.h"
#include "random"

int main() {
    srand(time(NULL));
    Erzeuger* erzeuger = new Solar(111, "aaa", 1000);

    Simulator* sim = new Simulator(erzeuger,"UDP",5000,"127.0.0.1");
    sim->start();

    delete erzeuger;
    return 0;
}
