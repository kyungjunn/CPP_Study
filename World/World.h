#pragma once

class APlayer;
class AWildPig;
class ASlime;
class AGoblin;

class UWorld
{
public:
	UWorld();
	~UWorld();

	APlayer* Players;
	AWildPig* WildPigs;
	ASlime* Slimes;
	AGoblin* Goblins;

	int PlayerCount = 0;
	int WildPigCount = 0;
	int GoblinCount = 0;
	int SlimeCount = 0;
};

