//
// Created by philipp on 04.05.21.
//

#include "../header/Solar.h"


/**
 *
 */
Solar::Solar(int id, string name, int size) {
    this->id = id;
    this->name = name;
    this->size = size;
    this->hour = 0;
    this->hourCount = 0;
    this->completeGeneration = 0;
    this->turnOffPossible = false;
    this->status = true;
    this->type = "Solar";
}



/**
 *
 */
Solar::~Solar() = default;



/**
 *
 */
double Solar::getLastHourGeneration() {
    double production = 0;
    if (hourCount <= 2160) { //1st 3 month
        if (hour < 9 || hour > 17)
            production = 0;
        else{
            production = ((rand() % 3000) / 1000) * size;
        }
    }else if ((hourCount > 2160 && hourCount < 4320) || (hourCount > 6480 && hourCount <= 8640)){
        if (hour < 8 || hour > 19)
            production = 0;
        else{
            production = ((rand() % 4500) / 1000) * size;
        }
    }else{
        if (hour < 6 || hour > 21)
            production = 0;
        else{
            production = ((rand() % 8000) / 1000) * size;
        }
    }

    if (hourCount == 8640)
        hourCount = 0;
    else
        ++hourCount;
    if (hour == 23)
        hour = 0;
    else
        ++hour;

    completeGeneration += production;
    return production;
}
