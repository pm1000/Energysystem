//
// Created by philipp on 04.05.21.
//

#ifndef ERZEUGER_ERZEUGER_H
#define ERZEUGER_ERZEUGER_H

#include "string"
#include "random"
#include "iostream"

using namespace std;

/**
 *
 */
class Erzeuger {
protected:
    string type;
    int id;
    double completeGeneration;
    string name;
    bool status;

public:
    virtual ~Erzeuger();

    virtual double getLastHourGeneration() = 0;
    virtual double getCompleteGeneration() const;
    string getType();
    int getID() const;
    string getName() const;
    bool isStatus() const;
    void switchStatus();
};


#endif //ERZEUGER_ERZEUGER_H
