//
// Created by philipp on 04.05.21.
//

#ifndef ERZEUGER_ERZEUGER_H
#define ERZEUGER_ERZEUGER_H

#include "string"
#include "random"

class Erzeuger {
protected:
    std::string type;
    int id;
    double completeGeneration;
    std::string name;
    bool turnOffPossible;
    bool status;

public:
    virtual ~Erzeuger();

    virtual double getLastHourGeneration() = 0;
    virtual double getCompleteGeneration() const;
    std::string getType();
    int getID() const;
    std::string getName() const;
    bool isTurnOffPossible() const;
    bool isStatus() const;
    void switchStatus();
};


#endif //ERZEUGER_ERZEUGER_H
