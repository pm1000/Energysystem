//
// Created by philipp on 30.04.21.
//
#include "map"
#include "string"
#include "mutex"

#ifndef ZENTRALE_KOMPONENTE_H
#define ZENTRALE_KOMPONENTE_H


class Komponente {
protected:
    std::string type;
    std::string name;
    int id;
    std::map<unsigned long long,double> values;
    std::mutex mtx;
public:

    Komponente();
    virtual ~Komponente();

    virtual std::string getType() = 0;
    virtual const std::map<unsigned long long, double> &getValues() const;
    virtual void addNewValue(unsigned long long timestamp, double value);
    virtual double getLatestValue() const;
    const std::string &getName() const;
};


#endif //ZENTRALE_KOMPONENTE_H
