//
// Created by philipp on 30.04.21.
//

#ifndef VERBRAUCHER_VERBRAUCHER_H
#define VERBRAUCHER_VERBRAUCHER_H

#include "string"
#include "random"

using namespace std;


/**
 *
 */
enum Weekday{Monday = 0, Tuesday = 1, Wednesday = 2, Thursday = 3, Friday = 4, Saturday = 5, Sunday = 6};



/**
 *
 */
class Verbraucher {
protected:
    string type;
    int id{};
    double completeConsumption{};
    Weekday weekday;
    short time{};
    string name;

public:
    Verbraucher();
    virtual ~Verbraucher();

    virtual double getLastHourConsumption() = 0;
    virtual double getCompleteConsumption() const;
    virtual string getType() = 0;
    int getId() const;
    const string &getName() const;
};


#endif //VERBRAUCHER_VERBRAUCHER_H
