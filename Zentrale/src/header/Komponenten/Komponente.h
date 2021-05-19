//
// Created by philipp on 30.04.21.
//
#include "map"
#include "string"
#include "mutex"
#include "queue"
#include <bits/stdc++.h>

#ifndef ZENTRALE_KOMPONENTE_H
#define ZENTRALE_KOMPONENTE_H


class Komponente {
protected:
    std::string type;
    std::string name;
    int id;
    //timestamp, value
    std::map<unsigned long long,double> values;
    //max heap for msgID
    std::vector<int> maxHeap;
    std::mutex mtx;
    std::string ip {};


    //helper function
    static bool cmp(int i, int j);

public:

    Komponente();
    virtual ~Komponente();

    virtual std::string getType() = 0;
    virtual const std::map<unsigned long long, double> &getValues() const;
    virtual void addNewValue(unsigned long long timestamp, double value);
    virtual double getLatestValue() const;
    const std::string &getName() const;
    int getId() const;
    std::vector<int> checkMissingMsg(int msgID);
    std::string getIp() const;
    void setIp(std::string ip);
};


#endif //ZENTRALE_KOMPONENTE_H
