//
// Created by ise on 12/31/21.
//

#include "Chicken.h"

Chicken::Chicken() {

    this->age = 0;
    this->animalPrice = 3;
    this->expireYear = 3;
}

int Chicken::GetAge() const {return this->age;}

void Chicken::SetAge(int age) {this->age = age;}

int Chicken::GetExpire() {return this->expireYear;}

Chicken::~Chicken() {}