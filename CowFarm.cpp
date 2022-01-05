//
// Created by ise on 12/31/21.
//

#include "CowFarm.h"
#include "Cow.h"
#include <iostream>

using namespace std;

CowFarm::CowFarm() {

    this->money = 10;
    this->farmID = Farm::GetStaticID();
    this->selfNumProducts = 0;
    this->purchasedNumProducts = 0;

    for (int i=0; i<3; i++)
    {
        Cow *cow = new Cow();
        this->animals.push_back(cow);
    }
}

void CowFarm::FarmProduce() {

    for (int i=0; i<this->animals.size(); i++)
        this->selfNumProducts += animals[i]->GetAge();
}


void CowFarm::PrintFarm() {
    cout << "Farm Id: " << this->GetFarmID() << ", type: Cow farm, Money: " << this->GetMoney() <<
    ", Animals: " << this->animals.size() << " cows, Products: Milk[" << this->GetSelfNumProducts() <<
    "], Wool[0], Eggs[" << this->GetPurchasedNumProducts() << "]" << endl;
}


int CowFarm::GetFarmID() const{return this->farmID;}

int CowFarm::GetMoney() const{return this->money;}

void CowFarm::SetMoney(int num) {this->money = num;}

int CowFarm::GetSelfNumProducts() const {return this->selfNumProducts;}

int CowFarm::GetPurchasedNumProducts() const {return this->purchasedNumProducts;}


void CowFarm::SetSelfNumProducts(int num) {this->selfNumProducts = num;}

void CowFarm::SetPurchasedNumProducts(int num) {this->purchasedNumProducts = num;}


vector<Farm*> CowFarm::GetPotential() {return this->potentialFarms;}

vector<Animal*> CowFarm::GetAnimals() {return this->animals;}

void CowFarm::GrowAnimals(){

    for (int i=0; i<this->animals.size(); i++)
    {
        this->animals[i]->SetAge(this->animals[i]->GetAge() + 1);

        if (this->animals[i]->GetAge() == this->animals[i]->GetExpire())        // If the animal need to die :(
        {
            delete this->animals[i];
            this->animals.erase(this->animals.cbegin() + i);
            i--;
        }
    }
}

void CowFarm::BuyAnimals() {

    int count = this->GetMoney() / 10;     // How many cows I can buy
    for (int i=0; i<count; i++)
    {
        Cow *cow = new Cow();
        this->animals.push_back(cow);
        this->money -= 10;
    }

    if (count != 0) {
        cout << "Cow farm(" << this->GetFarmID() << ") bought " << count
             << " cows for " << count * 10 << " dollars" << endl;
    }
}

void CowFarm::AddObserver(Farm *sheepfarm) {        // Add to the right place

    if (this->potentialFarms.empty()) {
        this->potentialFarms.push_back(sheepfarm);
        cout << "Cow farm(" << this->GetFarmID() << ") Added Sheep farm("
             << sheepfarm->GetFarmID() << ") to his client list" << endl;
    }
    else
    {
        for (int i=0; i<this->potentialFarms.size(); i++)
        {
            if (*sheepfarm < *this->potentialFarms[i]) {
                this->potentialFarms.insert(this->potentialFarms.begin() + i, sheepfarm);
                cout << "Cow farm(" << this->GetFarmID() << ") Added Sheep farm("
                     << sheepfarm->GetFarmID() << ") to his client list" << endl;
                return;
            }
            if (*sheepfarm == *this->potentialFarms[i])        // ID already exists
                return;
        }
        this->potentialFarms.push_back(sheepfarm);     // ID bigger then everyone
        cout << "Cow farm(" << this->GetFarmID() << ") Added Sheep farm("
             << sheepfarm->GetFarmID() << ") to his client list" << endl;
    }
}

void CowFarm::DeleteObserver(Farm *farm) {

    for (int i=0; i<this->potentialFarms.size(); i++)
    {
        if (*farm == *this->potentialFarms[i])
            this->potentialFarms.erase(this->potentialFarms.begin() + i);
    }
}

void CowFarm::Update(Farm *farm) {         // Check from all farms who can be potential buyer

    if (farm == NULL)
        return;

    this->AddToFarmSheep(farm);
    this->AddToFarmChicken(farm);
    this->AddToFarmCow(farm);
    farm->AddToFarmCow(this);
    farm->AddToFarmChicken(this);
    farm->AddToFarmSheep(this);

}


void CowFarm::AddToFarmCow(Farm *sheepfarm) {         // Add to the cow farm the right farm

    sheepfarm->AddMeSheep(this);
}

void CowFarm::AddToFarmChicken(Farm *sheepfarm) {       // Add to the chicken farm the right farm

}

void CowFarm::AddToFarmSheep(Farm *cowfarm) {           // Add to the sheep farm the right farm

}


void CowFarm::AddMeCow(Farm *chickenfarm) {chickenfarm->AddObserver(this);}

void CowFarm::AddMeChicken(Farm *cowfarm) {

}

void CowFarm::AddMeSheep(Farm *chickenfarm) {

}


CowFarm::~CowFarm(){}


void CowFarm::DeleteAnimals() {

    for (auto it = this->animals.begin(); it != this->animals.end(); ++it)
    {
        delete *it;
    }
    this->animals.clear();
}


void CowFarm::BuyProducts(Farm &chickenfarm) {        // buy as much as you can

    int counter = 0;
    while (this->GetMoney() >= 1 && chickenfarm.GetSelfNumProducts() > 0)
    {
        this->money -= 1;
        chickenfarm.SetMoney(chickenfarm.GetMoney() + 1);
        this->purchasedNumProducts += 1;
        chickenfarm.SetSelfNumProducts(chickenfarm.GetSelfNumProducts()-1);

        counter++;
    }

    if (counter != 0)
    {
        cout << "Cow farm(" << this->GetFarmID() << ") bought " << counter << " eggs for "
             << counter*1 << " dollars from Chicken farm(" << chickenfarm.GetFarmID() << ")" << endl;
    }
}


void CowFarm::SellProducts() {            // Sell to your potential buyers

    if (this->potentialFarms.empty())
        return;

    for (int i = 0; i < this->potentialFarms.size(); i++) {
        this->potentialFarms[i]->BuyProducts(*this);
        if (this->GetMoney() < 1)
            return;
    }
}