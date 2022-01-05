CPP_FARM:farmMarket.o Market.o CowFarm.o SheepFarm.o ChickenFarm.o Farm.o Sheep.o Cow.o Chicken.o Animal.o
	g++ farmMarket.o Market.o CowFarm.o SheepFarm.o ChickenFarm.o Farm.o Sheep.o Cow.o Chicken.o Animal.o -o CPP_FARM
farmMarket.o:farmMarket.cpp Farm.h Animal.h
	g++ -c farmMarket.cpp

Market.o:Market.cpp Market.h Farm.h Animal.h CowFarm.h ChickenFarm.h SheepFarm.h
	g++ -c Market.cpp Market.h

CowFarm.o:CowFarm.cpp CowFarm.h Farm.h Animal.h Sheep.h
	g++ -c CowFarm.cpp CowFarm.h

SheepFarm.o:SheepFarm.cpp SheepFarm.h Farm.h Animal.h Sheep.h
	g++ -c SheepFarm.cpp SheepFarm.h

ChickenFarm.o:ChickenFarm.cpp ChickenFarm.h Farm.h Animal.h Chicken.h
	g++ -c ChickenFarm.cpp ChickenFarm.h

Farm.o:Farm.cpp Farm.h Animal.h
	g++ -c Farm.cpp Farm.h

Sheep.o:Sheep.cpp Sheep.h Animal.h
	g++ -c Sheep.cpp Sheep.h

Cow.o:Cow.cpp Cow.h Animal.h
	g++ -c Cow.cpp Cow.h

Chicken.o:Chicken.cpp Chicken.h Animal.h
	g++ -c Chicken.cpp Chicken.h

Animal.o:Animal.cpp Animal.h
	g++ -c Animal.h Animal.cpp
