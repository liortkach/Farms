//
// Created by ise on 1/1/22.
//

#include "Market.h"
#include "CowFarm.h"
#include "ChickenFarm.h"
#include "SheepFarm.h"

Market::Market() {

    this->year = 0;
}

int Market::getYear() const {return this->year;}

void Market::SetYear(int num) {this->year = num;}


void Market::MarketProduce() {

    for (int i=0; i<this->farms.size(); i++)
        this->farms[i]->FarmProduce();
}


void Market::createNewFarms() {             // TODO: Need to throw exeption instead of "Problem"

    int numCowsFarms;
    cout << "How many new cow farms will be added this year?" << endl;
    cin >> numCowsFarms;

    if (numCowsFarms < 0)
        cout << " Problem";

    int numSheepFarms;
    cout << "How many new sheep farms will be added this year?" << endl;
    cin >> numSheepFarms;

    if (numSheepFarms < 0)
        cout << "Problem";

    int numChickenFarms;
    cout << "How many new chicken farms will be added this year?" << endl;
    cin >> numChickenFarms;

    if (numChickenFarms <0)
        cout << "Problem";

    for (int i=0; i < numCowsFarms; i++)
    {
        CowFarm *cowFarm = new CowFarm();
        this->farms.push_back(cowFarm);
    }

    for (int i=0; i<numSheepFarms; i++)
    {
        SheepFarm *sheepFarm = new SheepFarm();
        this->farms.push_back(sheepFarm);
    }

    for (int i=0; i<numChickenFarms; i++)
    {
        ChickenFarm *chickenFarm = new ChickenFarm();
        this->farms.push_back(chickenFarm);
    }

    cout << "----Adding new farms to market----" << endl;
}


void Market::tradingDay()  {

    cout << "----Begin Market----" << endl;

    for (int i=0; i<this->farms.size(); i++)
    {
        this->farms[i]->SellProducts();              // Every Farmer Sells by the order
    }

    cout << "----Buy Animals----" << endl;
    for (int i=0; i<this->farms.size(); i++)
    {
        this->farms[i]->BuyAnimals();               // buy animals as much as you can
    }
}


void Market::notifyAll() {



    for (int i=0; i<this->farms.size(); i++)        // Add all the potential buyers to all the farms
    {
        for (int j = 0; j < i; j++)
        {
            this->farms[j]->Update(this->farms[i]);
        }
    }
}


void Market::growAnimals(){

    for (int i=0; i<this->farms.size(); i++)            // Grow animals in every farm
    {
        this->farms[i]->GrowAnimals();
    }
}


void Market::nextYear() {

    this->createNewFarms();         // Creates the new farms and print the messages

    this->notifyAll();               // Add all the potential buyers to all the farms

    this->MarketProduce();           // Every farm produces its products

    this->tradingDay();                       // Do the trading day

    this->growAnimals();            // Grow all the animals

    for (int i=0; i<this->farms.size(); i++)        // Give 10 dollars to the farms
        this->farms[i]->SetMoney(this->farms[i]->GetMoney() + 10);

    this->SetYear(this->getYear() + 1);
}


void Market::fastForwardYears()
{

    int countyears = 0;
    cout << "How many years to fast forward?" << endl;
    cin >> countyears;

    for (int i=0; i<countyears; i++)
    {
        this->MarketProduce();           // Every farm produces its products
        tradingDay();
        growAnimals();
        for (int i=0; i<this->farms.size(); i++)        // Give 10 dollars to the farms
            this->farms[i]->SetMoney(this->farms[i]->GetMoney() + 10);
    }

    this->SetYear(this->getYear() + countyears);
}



void Market::printMarketFarms() {               // Print all the farms

    cout << "----Market Farms----" << endl;

    for (int i=0; i<this->farms.size(); i++)
        this->farms[i]->PrintFarm();
}


Market::~Market() {

    /*
    for (int i=0; i<this->farms.size(); ++i)
    {
        this->farms[i]->DeleteAnimals();
    }
    */
    for (auto it = this->farms.begin(); it != this->farms.end(); ++it)
    {
        delete *it;
    }
    this->farms.clear();
}