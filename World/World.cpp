#include "World.h"

UWorld::UWorld() 
	: PlayerCount(0), WildPigCount(0), SlimeCount(0), GoblinCount(0),
	Players(nullptr), WildPigs(nullptr), Slimes(nullptr), Goblins(nullptr)
	// 0으로 초기화 PlayerCount = 0; 이랑 같음 , 초기화 리스트
{

}

UWorld::~UWorld()
{
	delete[] Players;
	Players = nullptr;

	delete[] WildPigs;
	WildPigs = nullptr;

	delete[] Slimes;
	Slimes = nullptr;

	delete[] Goblins;
	Goblins = nullptr;
}
