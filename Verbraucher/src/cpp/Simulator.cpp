//
// Created by philipp on 30.04.21.
//

#include "../header/Simulator.h"

Simulator::Simulator(Verbraucher *verbraucher) : verbraucher(verbraucher) {}

Simulator::~Simulator() {
    delete verbraucher;
}

void Simulator::start() {
    try {
        while(true) {
            std::thread t1(&Simulator::simulate, this);
            sleep(2);
            t1.join();
        }

    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void Simulator::simulate() {
    double cons = verbraucher->getLastHourConsumption();
    std::cout << cons << " kW/h" << std::endl;
}
