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
    Erzeuger* erzeuger = new Solar(123, "aaa", 1);

    for (int i = 0; i < 365; ++i){
        for (int j = 0; j < 24; ++j){
            double cons = erzeuger->getLastHourGeneration();
            std::cout << cons << " kW/h" << std::endl;
        }
    }
    Simulator* sim = new Simulator(erzeuger,"UDP",5000,"127.0.0.1");
    sim->start();

    std::cout << "Complete: " << erzeuger->getCompleteGeneration();

    delete erzeuger;
    return 0;
}
