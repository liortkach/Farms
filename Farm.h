//
// Created by ise on 12/31/21.
//

#ifndef FARMS_FARM_H
#define FARMS_FARM_H
#include "Animal.h"
#include <vector>

using namespace std;

class Farm {
    static int id;
    int farmID;
    int money;
    int selfNumProducts;
    int purchasedProducts;
    vector<Animal*> animals;
    vector<Farm*> potentialFarms;

public:
    Farm();
    virtual void FarmProduce()=0;                   // Add the self products for every animal
    virtual void BuyProducts(Farm &farm)=0;
    virtual void SellProducts()=0;
    virtual void BuyAnimals()=0;
    virtual void PrintFarm()=0;
    static int GetStaticID();                    // A lot of getters and setter for vars of the farm
    virtual int GetFarmID() const=0;
    virtual int GetMoney() const=0;
    virtual void SetMoney(int num)=0;
    virtual int GetSelfNumProducts() const=0;
    virtual void SetSelfNumProducts(int num)=0;
    virtual int GetPurchasedNumProducts() const=0;
    virtual void SetPurchasedNumProducts(int num)=0;
    virtual ~Farm();
    virtual bool operator== (const Farm &farm);
    virtual bool operator< (const Farm &farm);
    virtual vector<Farm*> GetPotential()=0;
    virtual vector<Animal*> GetAnimals()=0;
    virtual void GrowAnimals()=0;

    virtual void AddObserver(Farm *farm)=0;
    virtual void DeleteObserver(Farm *farm)=0;

    virtual void Update(Farm *farm)=0;

    virtual void AddToFarmCow(Farm *sheepfarm)=0;   // Add to the cow farm the right farm
    virtual void AddToFarmSheep(Farm *chickenfarm)=0;     // Add to the chicken farm the right farm
    virtual void AddToFarmChicken(Farm *cowfarm)=0; // Add to the sheep farm the right farm

    virtual  void AddMeCow(Farm *chickenfarm)=0;        // Cow farm adds sheep farm
    virtual  void AddMeSheep(Farm *cowfarm)=0;    // Sheep farm adds chicken farm
    virtual  void AddMeChicken(Farm *sheepfarm)=0;      // Chicken farm adds cow farm

};


#endif //FARMS_FARM_H
