//
// Created by philipp on 30.04.21.
//

#include "../../header/Komponenten/Komponente.h"

Komponente::Komponente() {}

Komponente::~Komponente() {

}

const std::map<unsigned long long, double> &Komponente::getValues() const {
    return values;
}

void Komponente::addNewValue(unsigned long long timestamp, double value) {
    mtx.lock();
    if (this->values.find(timestamp) == this->values.end())
        this->values.insert({timestamp,value});
    mtx.unlock();
}


double Komponente::getLatestValue() const {
    //todo
    return this->values.begin()->second;
}

const std::string &Komponente::getName() const {
    return name;
}

int Komponente::getId() const {
    return id;
}

bool Komponente::cmp(int i, int j) {
    return i > j;
}

std::vector<int> Komponente::checkMissingMsg(int msgID) {
    std::vector<int> missing;
    bool alreadyInserted = false;

    //maxheap is empty -> insert msgID
    if (maxHeap.size() == 0) {
        maxHeap.push_back(msgID);
        std::sort(maxHeap.begin(), maxHeap.end(), cmp);
    }
    else if (maxHeap.size() == 1){
        //1 element on maxheap, check if it is 1 smaller
        if (maxHeap.front() + 1 == msgID){
            //correct msg order, pop element and insert current
            maxHeap.pop_back();
            maxHeap.push_back(msgID);
            std::sort(maxHeap.begin(), maxHeap.end(), cmp);
        } else {
            //message missing / message arrived in the wrong order -> push on the max heap
            maxHeap.push_back(msgID);
            std::sort(maxHeap.begin(), maxHeap.end(), cmp);
            alreadyInserted = true;
        }
    }

    if (maxHeap.size() > 1){
        //incorrect order / missing messages -> push on the max heap
        if (!alreadyInserted) {
            maxHeap.push_back(msgID);
            std::sort(maxHeap.begin(), maxHeap.end(), cmp);
        }

        //fill vector with missing messages
        for (int i = 1; i < maxHeap.size(); ++i){
            for (int j = maxHeap[i-1] - 1; j > maxHeap[i]; j--)
                missing.push_back(j);
        }

        //remove elements that were ordered / are not missing anymore
        for (int i = maxHeap.size() - 1; i >= 1; --i) {
            if (maxHeap[i - 1] - 1 == maxHeap[i])
                maxHeap.erase(maxHeap.begin() + i);
            else
                break;
        }

        std::sort(maxHeap.begin(), maxHeap.end(), cmp);
    }

    return missing;
}

/**
 *
 */
std::string Komponente::getIp() const {
    return this->ip;
}



/**
 *
 */
void Komponente::setIp(std::string ip) {
    this->ip = ip;
}

