#pragma once

class AWall;
class AFloor;
class APlayer;
class AMonster;
class AGoal;

class UWorld
{
public:
	UWorld();
	~UWorld();

	AWall* Walls;
	AFloor* Floors;
	APlayer* Players;
	AMonster* Monsters;
	AGoal* Goals;
};

