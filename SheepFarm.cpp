//
// Created by ise on 1/1/22.
//

#include "SheepFarm.h"
#include "Sheep.h"
#include "iostream"

using namespace std;

SheepFarm::SheepFarm() {

    this->money = 10;
    this->farmID = Farm::GetStaticID();
    this->selfNumProducts = 0;
    this->purchasedNumProducts = 0;

    for (int i=0; i<3; i++)
    {
        Sheep *sheep = new Sheep();
        this->animals.push_back(sheep);
    }
}


void SheepFarm::FarmProduce() {

    for (int i=0; i<this->animals.size(); i++)
        this->selfNumProducts += animals[i]->GetAge();
}


int SheepFarm::GetFarmID() const{
    return this->farmID;
}

void SheepFarm::PrintFarm() {
    cout << "Farm Id: " << this->GetFarmID() << ", type: Sheep farm, Money: " << this->GetMoney() <<
         ", Animals: " << this->animals.size() << " sheep, Products: Milk[" << this->GetPurchasedNumProducts() <<
         "], Wool[" << this->GetSelfNumProducts() << "], Eggs[0]" << endl;
}


int SheepFarm::GetMoney() const{return this->money;}

void SheepFarm::SetMoney(int num) {this->money = num;}

int SheepFarm::GetSelfNumProducts() const{return this->selfNumProducts;}

void SheepFarm::SetSelfNumProducts(int num) {this->selfNumProducts = num;}

void SheepFarm::SetPurchasedNumProducts(int num) {this->purchasedNumProducts = num;}


int SheepFarm::GetPurchasedNumProducts() const{return this->purchasedNumProducts;}

vector<Farm*> SheepFarm::GetPotential() {return this->potentialFarms;}


vector<Animal*> SheepFarm::GetAnimals() {return this->animals;};

void SheepFarm::GrowAnimals(){

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

void SheepFarm::BuyAnimals() {

    int count = this->GetMoney() / 5;     // How many sheep I can buy
    for (int i=0; i<count; i++)
    {
        Sheep *sheep = new Sheep();
        this->animals.push_back(sheep);
        this->money -= 5;
    }

    if (count != 0) {
        cout << "Sheep farm(" << this->GetFarmID() << ") bought " << count
             << " sheeps for " << count * 5 << " dollars" << endl;
    }
}

void SheepFarm::AddObserver(Farm *chickenfarm) {        // Add to the right place

    if (this->potentialFarms.empty()) {
        this->potentialFarms.push_back(chickenfarm);
        cout << "Sheep Farm(" << this->GetFarmID() << ") Added Chicken farm("
             << chickenfarm->GetFarmID() <<") to his client list" << endl;
    }
    else
    {
        for (int i=0; i<this->potentialFarms.size(); i++)
        {
            if (*chickenfarm < *this->potentialFarms[i]) {
                this->potentialFarms.insert(this->potentialFarms.begin() + i, chickenfarm);
                cout << "Sheep Farm(" << this->GetFarmID() << ") Added Chicken farm("
                     << chickenfarm->GetFarmID() <<") to his client list" << endl;
                return;
            }
            if (*chickenfarm == *this->potentialFarms[i])      // If its already exists
                return;
        }
        this->potentialFarms.push_back(chickenfarm);       // ID bigger than everyone
        cout << "Sheep Farm(" << this->GetFarmID() << ") Added Chicken farm("
             << chickenfarm->GetFarmID() <<") to his client list" << endl;
    }
}

void SheepFarm::DeleteObserver(Farm *farm) {

    for (int i=0; i<this->potentialFarms.size(); i++)
    {
        if (*farm == *this->potentialFarms[i])
            this->potentialFarms.erase(this->potentialFarms.begin() + i);
    }
}

void SheepFarm::Update(Farm* farm) {         // Check from all farms who can be potential buyer

    if (farm == NULL)
        return;

    this->AddToFarmSheep(farm);
    this->AddToFarmChicken(farm);
    this->AddToFarmCow(farm);
    farm->AddToFarmCow(this);
    farm->AddToFarmChicken(this);
    farm->AddToFarmSheep(this);

}

void SheepFarm::AddToFarmCow(Farm *cowfarm) {}         // Add to the cow farm the right farm


void SheepFarm::AddToFarmChicken(Farm *sheepfarm) {}       // Add to the chicken farm the right farm

void SheepFarm::AddToFarmSheep(Farm *chickenfarm) {chickenfarm->AddMeChicken(this);}        // Add to the sheep farm the right farm

void SheepFarm::AddMeCow(Farm *sheepfarm) {}

void SheepFarm::AddMeChicken(Farm *cowfarm) {}

void SheepFarm::AddMeSheep(Farm *cowfarm) {cowfarm->AddObserver(this);}



SheepFarm::~SheepFarm() {}

void SheepFarm::DeleteAnimals() {

    for (auto it = this->animals.begin(); it != this->animals.end(); ++it)
    {
        delete *it;
    }
    this->animals.clear();
}


void SheepFarm::BuyProducts(Farm &cowfarm) {        // buy as much as you can

    int counter = 0;
    while (this->GetMoney() >= 3 && cowfarm.GetSelfNumProducts() > 0)
    {
        this->money -= 3;
        cowfarm.SetMoney(cowfarm.GetMoney() + 3);
        this->purchasedNumProducts += 1;
        cowfarm.SetSelfNumProducts(cowfarm.GetSelfNumProducts()-1);
        counter++;
    }

    if (counter != 0)
    {
        cout << "Sheep farm(" << this->GetFarmID() << ") bought " << counter << " milk for "
        << counter*3 << " dollars from Cow farm(" << cowfarm.GetFarmID() << ")" << endl;
    }
}


void SheepFarm::SellProducts() {            // Sell to your potential buyers

    if (this->potentialFarms.empty())
        return;

    for (int i=0; i<this->potentialFarms.size(); i++)
    {
        this->potentialFarms[i]->BuyProducts(*this);
        if (this->GetMoney() < 3)
            return;
    }
}