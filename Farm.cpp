//
// Created by ise on 12/31/21.
//

#include "Farm.h"

int Farm::id = 0;

Farm::Farm() {Farm::id++;}

int Farm::GetStaticID() {return Farm::id;}

Farm::~Farm() {}


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