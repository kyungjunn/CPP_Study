#include "World.h"
#include <iostream>
#include <conio.h>

UWorld::UWorld()
{
}

UWorld::~UWorld()
{
	delete[] Walls;
	Walls = nullptr;
	delete[] Floors;
	Floors = nullptr;
	delete[] Players;
	Players = nullptr;
	delete[] Monsters;
	Monsters = nullptr;
	delete[] Goals;
	Goals = nullptr;
}

