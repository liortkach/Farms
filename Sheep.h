//
// Created by ise on 12/31/21.
//

#ifndef FARMS_SHEEP_H
#define FARMS_SHEEP_H
#include "Animal.h"

class Sheep : public Animal{

    int age;
    int animalPrice;
    int expireYear;

public:
    Sheep();
    virtual int GetAge() const;
    virtual void SetAge(int age);
    virtual int GetExpire();
    virtual ~Sheep();
};


#endif //FARMS_SHEEP_H
