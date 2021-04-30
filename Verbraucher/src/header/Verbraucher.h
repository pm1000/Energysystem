//
// Created by philipp on 30.04.21.
//

#ifndef VERBRAUCHER_VERBRAUCHER_H
#define VERBRAUCHER_VERBRAUCHER_H

#include "string"
#include "random"

enum Weekday{Monday = 0, Tuesday = 1, Wednesday = 2, Thursday = 3, Friday = 4, Saturday = 5, Sunday = 6};

class Verbraucher {
protected:
    std::string type;
    int id;
public:
    int getId() const;

protected:
    double completeConsumption;
    Weekday weekday;
    short time;


public:
    virtual ~Verbraucher();

    virtual double getLastHourConsumption() = 0;
    virtual double getCompleteConsumption() const;
    virtual std::string getType() = 0;


};


#endif //VERBRAUCHER_VERBRAUCHER_H
