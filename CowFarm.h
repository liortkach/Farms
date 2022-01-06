//
// Created by ise on 12/31/21.
//

#ifndef FARMS_COWFARM_H
#define FARMS_COWFARM_H
#include "Farm.h"

class CowFarm : public Farm{

    int farmID;
    int money;
    int selfNumProducts;
    int purchasedNumProducts;
    vector<Animal*> animals;
    vector<Farm*> potentialFarms;

public:
    CowFarm();
    virtual void FarmProduce();     // Add the self products for every animal
    virtual void BuyProducts(Farm &chickenfarm);
    virtual void SellProducts();
    virtual void BuyAnimals();
    virtual void PrintFarm();
    virtual int GetFarmID() const;       // A lot of getters and setter for vars of the farm
    virtual int GetMoney() const;
    virtual void SetMoney(int num);
    virtual int GetSelfNumProducts() const;
    virtual void SetSelfNumProducts(int num);
    virtual int GetPurchasedNumProducts() const;
    virtual void SetPurchasedNumProducts(int num);
    virtual vector<Farm*> GetPotential();
    virtual vector<Animal*> GetAnimals();
    virtual void GrowAnimals();

    virtual ~CowFarm();
    //virtual void DeleteAnimals();

    virtual void Update(Farm *farm);

    virtual void AddObserver(Farm *farm);
    virtual void DeleteObserver(Farm *farm);

    virtual void AddToFarmCow(Farm *sheepfarm);   // Add to the cow farm the right farm
    virtual void AddToFarmSheep(Farm *chickenfarm);     // Add to the chicken farm the right farm
    virtual void AddToFarmChicken(Farm *cowfarm); // Add to the sheep farm the right farm

    virtual  void AddMeCow(Farm *chickenfarm);        // Cow farm adds sheep farm
    virtual  void AddMeSheep(Farm *cowfarm);    // Sheep farm adds chicken farm
    virtual  void AddMeChicken(Farm *sheepfarm);      // Chicken farm adds cow farm
};


#endif //FARMS_COWFARM_H
