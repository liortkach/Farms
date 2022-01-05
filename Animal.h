//
// Created by ise on 12/31/21.
//

#ifndef FARMS_ANIMAL_H
#define FARMS_ANIMAL_H


class Animal {

    int age;
    int animalPrice;
    int expireYear;
public:
    Animal();
    virtual int GetAge() const=0;
    virtual void SetAge(int age)=0;
    virtual int GetExpire()=0;
    virtual ~Animal();
};


#endif //FARMS_ANIMAL_H
