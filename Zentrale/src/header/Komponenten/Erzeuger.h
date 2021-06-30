//
// Created by philipp on 30.04.21.
//
#ifndef ZENTRALE_ERZEUGER_H
#define ZENTRALE_ERZEUGER_H

#include "Komponente.h"

class Erzeuger : public Komponente{
private:
    bool status;


public:
    Erzeuger(std::string type, std::string name, int id, bool status);
    ~Erzeuger();

    virtual std::string getType() override;

    void setStatus(bool status);
    bool isStatus() const;

};


#endif //ZENTRALE_ERZEUGER_H
