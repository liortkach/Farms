//
// Created by ise on 12/31/21.
//

#include "Sheep.h"

Sheep::Sheep() {

    this->age = 0;
    this->animalPrice = 5;
    this->expireYear = 5;
}

int Sheep::GetAge() const {return this->age;}

void Sheep::SetAge(int age) {this->age = age;}

int Sheep::GetExpire() {return this->expireYear;}

Sheep::~Sheep() {}