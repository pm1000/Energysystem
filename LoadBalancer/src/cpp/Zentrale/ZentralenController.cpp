//
// Created by philipp on 05.07.21.
//

#include "../../header/Zentrale/ZentralenController.h"

shared_ptr<ZentralenController> ZentralenController::instance = nullptr;

ZentralenController::ZentralenController() {
    this->zentralenCount = 0;
}

ZentralenController::~ZentralenController() {

}

int ZentralenController::getZentralenCount() {
    return this->zentralenCount;
}

shared_ptr<ZentralenController> ZentralenController::getInstance() {
    if (instance == nullptr) {
        shared_ptr<ZentralenController> z( new ZentralenController());
        instance = z;
    }
    return instance;
}

void ZentralenController::addZentrale(shared_ptr<Zentrale> zentrale) {
    m.lock();
    ZentralenController::zentralenCount++;
    this->zentralen.push_back(zentrale);
    this->activeZentralen.push_back(zentrale);
    m.unlock();
}

void ZentralenController::zentraleNotActive(shared_ptr<Zentrale> zentrale) {
    m.lock();
    for (int i = 0; i < activeZentralen.size(); ++i) {
        if (zentrale == activeZentralen[i]) {
            activeZentralen.erase(activeZentralen.begin() + i);
            this->zentralenCount--;
            break;
        }
    }
    m.unlock();
}

shared_ptr<Zentrale> ZentralenController::getActiveZentraleAt(int loc) {
    shared_ptr<Zentrale> zentrale = nullptr;
    m.lock();
    if (loc <= this->zentralenCount) {
        zentrale = activeZentralen[loc];
    }
    m.unlock();

    return zentrale;
}
