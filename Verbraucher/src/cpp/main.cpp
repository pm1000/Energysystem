#include <iostream>
#include "../header/Verbraucher.h"
#include "../header/Haushalt.h"
#include "../header/Unternehmen.h"
#include "../header/Simulator.h"

int main() {
    srand(time(NULL));
    Verbraucher* haushalt = new Unternehmen(123, "FLEISCHER");

    /*for (int i = 0; i < 365; ++i){
        for (int j = 0; j < 24; ++j){
            double cons = haushalt->getLastHourConsumption();
            std::cout << cons << " kW/h" << std::endl;
        }
    }*/
    Simulator* sim = new Simulator(haushalt,"UDP",5000,"127.0.0.1");
    sim->start();

    std::cout << "Complete Consumption: " << haushalt->getCompleteConsumption() <<std::endl;

    delete sim;
    return 0;
}
