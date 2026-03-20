#include "World.h"

UWorld::UWorld()
{
}

UWorld::~UWorld()
{
	delete[] Players;
	Players = nullptr;

	delete[] Monsters;
	Monsters = nullptr;

	delete[] WildPigs;
	WildPigs = nullptr;

	delete[] Slimes;
	Slimes = nullptr;

	delete[] Goblins;
	Goblins = nullptr;
}
