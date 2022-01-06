//
// Created by ise on 12/31/21.
//

#include "Farm.h"

int Farm::id = 0;

Farm::Farm() {Farm::id++;}

int Farm::GetStaticID() {return Farm::id;}

Farm::~Farm() {

    for (auto it = this->animals.begin(); it != this->animals.end(); ++it)
    {
        delete *it;
    }
    this->animals.clear();
}


bool Farm::operator==(const Farm &farm) {

    if (this->GetFarmID() == farm.GetFarmID())
        return true;

    return false;
}

bool Farm::operator<(const Farm &farm) {

    if (this->GetFarmID() < farm.GetFarmID())
        return true;

    return false;
}