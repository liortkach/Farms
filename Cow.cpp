//
// Created by ise on 12/31/21.
//

#include "Cow.h"

Cow::Cow() {

    this->age = 0;
    this->animalPrice = 10;
    this->expireYear = 10;
}

int Cow::GetAge() const {return this->age;}

void Cow::SetAge(int age) {this->age = age;}

int Cow::GetExpire() {return this->expireYear;}

Cow::~Cow() {}