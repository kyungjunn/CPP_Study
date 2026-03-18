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
	delete[] Destinations;
	Destinations = nullptr;

}

void UWorld::Move()
{
	int PlayerInput = _getch();

	int PlayerX = 1;
	int PlayerY = 1;

	if (PlayerInput == 'W' || PlayerInput == 'w')
	{
		PlayerY--;
	}
	if (PlayerInput == 'S' || PlayerInput == 's')
	{
		PlayerY++;
	}
	if (PlayerInput == 'A' || PlayerInput == 'a')
	{
		PlayerX--;
	}
	if (PlayerInput == 'D' || PlayerInput == 'd')
	{
		PlayerX++;
	}
}

void UWorld::Finish()
{ 

}
