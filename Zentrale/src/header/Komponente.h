//
// Created by philipp on 30.04.21.
//
#include <map>
#include "string"

#ifndef ZENTRALE_KOMPONENTE_H
#define ZENTRALE_KOMPONENTE_H


class Komponente {
protected:
    std::string type;
    std::string name;
public:
    const std::string &getName() const;

protected:
    std::map<std::string,double> values;

public:

    Komponente();
    virtual ~Komponente();

    virtual std::string getType() = 0;
    virtual const std::map<std::string, double> &getValues() const;
    virtual void addNewValue(std::string date, double value);
    virtual double getLatestValue() const;
};


#endif //ZENTRALE_KOMPONENTE_H
