//
// Created by ise on 1/1/22.
//

#include "ChickenFarm.h"
#include "Chicken.h"
#include "iostream"

using namespace std;

ChickenFarm::ChickenFarm() {

    this->money = 10;
    this->farmID = Farm::GetStaticID();
    this->selfNumProducts = 0;
    this->purchasedNumProducts = 0;
    for (int i=0; i<3; i++)
    {
        Chicken *chick = new Chicken();
        this->animals.push_back(chick);
    }
}

void ChickenFarm::FarmProduce() {

    for (int i=0; i<this->animals.size(); i++)
        this->selfNumProducts  += animals[i]->GetAge();          // Every animal produce as the age
}


int ChickenFarm::GetFarmID() const{return this->farmID;}

void ChickenFarm::PrintFarm() {
    cout << "Farm Id: " << this->GetFarmID() << ", type: Chicken farm, Money: " << this->GetMoney() <<
         ", Animals: " << this->animals.size() << " chickens, Products: "
         "Milk[0], Wool[" << this->GetPurchasedNumProducts() << "], Eggs[" << this->GetSelfNumProducts() << "]" << endl;
}

int ChickenFarm::GetMoney() const{return this->money;}

void ChickenFarm::SetMoney(int num) {this->money = num;}

int ChickenFarm::GetSelfNumProducts() const{return this->selfNumProducts;}

void ChickenFarm::SetPurchasedNumProducts(int num) {this->purchasedNumProducts = num;}

void ChickenFarm::SetSelfNumProducts(int num) {this->selfNumProducts = num;}

int ChickenFarm::GetPurchasedNumProducts() const{return this->purchasedNumProducts;}

vector<Animal*> ChickenFarm::GetAnimals() {return this->animals;}

void ChickenFarm::GrowAnimals() {

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


void ChickenFarm::AddObserver(Farm *cowfarm) {      // Add to the right place

    if (this->potentialFarms.empty()) {
        this->potentialFarms.push_back(cowfarm);
        cout << "Chicken farm(" << this->GetFarmID() << ") Added Cow farm("
             << cowfarm->GetFarmID() << ") to his client list" << endl;
    }
    else
    {
        for (int i=0; i<this->potentialFarms.size(); i++)
        {
            if (*cowfarm < *this->potentialFarms[i]) {
                this->potentialFarms.insert(this->potentialFarms.begin() + i, cowfarm);
                cout << "Chicken farm(" << this->GetFarmID() << ") Added Cow farm("
                     << cowfarm->GetFarmID() << ") to his client list" << endl;
                return;
            }
            if (*cowfarm == *this->potentialFarms[i])      // ID already exists
                return;
        }
        this->potentialFarms.push_back(cowfarm);       // ID bigger then everyone
        cout << "Chicken farm(" << this->GetFarmID() << ") Added Cow farm("
             << cowfarm->GetFarmID() << ") to his client list" << endl;
    }
}

void ChickenFarm::DeleteObserver(Farm *farm) {

    for (int i=0; i<this->potentialFarms.size(); i++)
    {
        if (*farm == *this->potentialFarms[i])
            this->potentialFarms.erase(this->potentialFarms.begin() + i);
    }
}

void ChickenFarm::Update(Farm *farm) {         // Check from all farms who can be potential buyer

    if (farm == nullptr)
        return;

    this->AddToFarmSheep(farm);
    this->AddToFarmChicken(farm);
    this->AddToFarmCow(farm);
    farm->AddToFarmCow(this);
    farm->AddToFarmChicken(this);
    farm->AddToFarmSheep(this);
}


void ChickenFarm::BuyAnimals() {

    int count = this->GetMoney() / 3;     // How many chickens I can buy
    for (int i=0; i<count; i++)
    {
        Chicken *chicken = new Chicken();
        this->animals.push_back(chicken);
        this->money -= 3;
    }

    if (count != 0) {
        cout << "Chicken farm(" << this->GetFarmID() << ") bought " << count
             << " chickens for " << count * 3 << " dollars" << endl;
    }
}

void ChickenFarm::AddToFarmCow(Farm *Chickenfarm) {}         // Add to the cow farm the right farm


void ChickenFarm::AddToFarmChicken(Farm *cowfarm) {cowfarm->AddMeCow(this);}     // Add to the chicken farm the right farms

void ChickenFarm::AddToFarmSheep(Farm *sheepfarm) {}           // Add to the sheep farm the right farm


void ChickenFarm::AddMeCow(Farm *chickenfarm) {}

void ChickenFarm::AddMeChicken(Farm *sheepfarm) {sheepfarm->AddObserver(this);}

void ChickenFarm::AddMeSheep(Farm *chickenfarm) {}



ChickenFarm::~ChickenFarm(){}


void ChickenFarm::DeleteAnimals() {

    for (auto it = this->animals.begin(); it != this->animals.end(); ++it)
    {
        delete *it;
    }
    this->animals.clear();

}



void ChickenFarm::BuyProducts(Farm &sheepfarm) {        // buy as much as you can

    int counter = 0;
    while (this->GetMoney() >= 2 && sheepfarm.GetSelfNumProducts() > 0)
    {
        this->money -= 2;
        sheepfarm.SetMoney(sheepfarm.GetMoney() + 2);
        this->purchasedNumProducts += 1;
        sheepfarm.SetSelfNumProducts(sheepfarm.GetSelfNumProducts()-1);

        counter++;
    }

    if (counter != 0)
    {
        cout << "Chicken farm(" << this->GetFarmID() << ") bought " << counter << " wool for "
             << counter*2 << " dollars from Sheep farm(" << sheepfarm.GetFarmID() << ")" << endl;
    }
}


vector<Farm*> ChickenFarm::GetPotential() {return this->potentialFarms;}


void ChickenFarm::SellProducts() {            // Sell to your potential buyers

    if (this->potentialFarms.empty())
        return;

    for (int i = 0; i < this->potentialFarms.size(); i++) {
        this->potentialFarms[i]->BuyProducts(*this);
        if (this->GetMoney() < 2)
            return;
    }
}