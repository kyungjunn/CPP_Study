#pragma once

class APlayer;
class AMonster;
class AWildPig;
class ASlime;
class AGoblin;

class UWorld
{
public:
	UWorld();
	~UWorld();

	APlayer* Players;
	AMonster* Monsters;
	AWildPig* WildPigs;
	ASlime* Slimes;
	AGoblin* Goblins;

	int X;
	int Y;
};

