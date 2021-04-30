//
// Created by philipp on 30.04.21.
//
#ifndef ZENTRALE_ERZEUGER_H
#define ZENTRALE_ERZEUGER_H

#include "Komponente.h"

class Erzeuger : public Komponente{

public:

    Erzeuger(std::string type, std::string name);

    ~Erzeuger() override;

    std::string getType() override;

    const std::map<std::string, double> &getValues() const override;

    void addNewValue(std::string date, double value) override;

    double getLatestValue() const override;

};


#endif //ZENTRALE_ERZEUGER_H
