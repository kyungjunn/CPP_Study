#pragma once

class UWall;
class UFloor;
class UPlayer;
class UMonster;
class UDestination;

class UWorld
{
public:
	UWorld();
	~UWorld();

	UWall* Walls;
	UFloor* Floors;

	UPlayer* Players;
	UMonster* Monsters;
	UDestination* Destinations;

	void Move();
	void Finish();
};

