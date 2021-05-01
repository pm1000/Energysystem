//
// Created by philipp on 30.04.21.
//

#include "../header/Unternehmen.h"

Unternehmen::Unternehmen(int id, std::string name) {
    this->id = id;
    this->type = "Unternehmen";
    this->completeConsumption = 0.0;
    this->weekday = Weekday::Monday;
    this->time = 0;
    this->consumptionSeed = rand() % 20000 + 100;
    this->name = name;
}


Unternehmen::~Unternehmen() {

}

double Unternehmen::getLastHourConsumption() {
    int randomNum = rand() % 100 + 1;
    double consumption = 0.0;
    if (this->weekday == Weekday::Saturday || this->weekday == Weekday::Sunday){
        if (time >= 9 || time <= 1){
            consumption = (consumptionSeed * 0.5) / 100 * randomNum;
        }else{
            consumption = (consumptionSeed * 0.5) / 100 * randomNum;
        }
    }else{
        if (time >= 20 || time < 8){
            consumption = (consumptionSeed * 0.5) / 100 * randomNum;
        }else {
            consumption = consumptionSeed / 100 * randomNum;
        }
    }

    //next hour
    if (time < 24)
        ++time;
    else{
        //next day
        time = 0;
        switch (weekday) {
            case Weekday::Monday:
                weekday = Weekday::Tuesday;
                break;
            case Weekday::Tuesday:
                weekday = Weekday::Wednesday;
                break;
            case Weekday::Wednesday:
                weekday = Weekday::Thursday;
                break;
            case Weekday::Thursday:
                weekday = Weekday::Friday;
                break;
            case Weekday::Friday:
                weekday = Weekday::Saturday;
                break;
            case Weekday::Saturday:
                weekday = Weekday::Sunday;
                break;
            case Weekday::Sunday:
                weekday = Weekday::Monday;
                break;
        }
    }

    completeConsumption += consumption;
    return consumption;
}

double Unternehmen::getCompleteConsumption() const {
    return Verbraucher::getCompleteConsumption();
}

std::string Unternehmen::getType() {
    return type;
}
