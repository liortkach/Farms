//
// Created by ise on 12/31/21.
//

#ifndef FARMS_COW_H
#define FARMS_COW_H
#include "Animal.h"

class Cow : public Animal{

    int age;
    int animalPrice;
    int expireYear;
public:
    Cow();
    virtual int GetAge() const;
    virtual void SetAge(int age);
    virtual int GetExpire();
    virtual ~Cow();
};


#endif //FARMS_COW_H
