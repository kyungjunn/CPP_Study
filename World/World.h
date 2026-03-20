#pragma once

class APlayer;
class AMonster;

class UWorld
{
public:
	UWorld();
	~UWorld();

	APlayer* Players;
	AMonster* Monsters;

	int X;
	int Y;
};

