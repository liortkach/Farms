//
// Created by ise on 1/1/22.
//

#ifndef FARMS_MARKET_H
#define FARMS_MARKET_H
#include "Farm.h"
#include <iostream>


using namespace std;

class Market {
    int year;
    vector<Farm*> farms;
public:
    Market();
    void createNewFarms();
    void tradingDay();
    void nextYear();
    void fastForwardYears();
    void printMarketFarms();
    void notifyAll();               // Update all farms
    void growAnimals();             // Grow the animals
    int getYear() const;            // get and set for year var
    void SetYear(int num);
    void MarketProduce();           // All the farms produces
    ~Market();
};


#endif //FARMS_MARKET_H
