//
// Created by ise on 12/31/21.
//

#ifndef FARMS_CHICKEN_H
#define FARMS_CHICKEN_H
#include "Animal.h"

class Chicken : public Animal{

    int age;
    int animalPrice;
    int expireYear;
public:
    Chicken();
    virtual int GetAge() const;
    virtual void SetAge(int age);
    virtual int GetExpire();
    virtual ~Chicken();
};


#endif //FARMS_CHICKEN_H
