//
// Created by philipp on 02.06.21.
//

#ifndef ENERGIEVERSORGER_KOMPONENTE_H
#define ENERGIEVERSORGER_KOMPONENTE_H

#include "string"
#include "mutex"
#include "map"

using std::string;
using std::map;
using std::mutex;


class Komponente {
protected:
    string type;
    string name;
    int id;
    //timestamp, value
    map<time_t ,double> values;

protected:
    mutex mtx;
    string ip {};

public:

    Komponente();
    virtual ~Komponente();

    virtual std::string getType() = 0;
    const map<time_t, double> &getValues() const;
    virtual void addNewValue(time_t timestamp, double value);
    const string &getName() const;
    int getId() const;
};


#endif //ENERGIEVERSORGER_KOMPONENTE_H
