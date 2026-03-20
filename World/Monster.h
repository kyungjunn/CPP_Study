#pragma once
#include "Actor.h"
class AWildPig;
class ASlime;
class AGoblin;

class AMonster : public AActor
{
public:
	AMonster();
	~AMonster();

	AWildPig* WildPigs;
	ASlime* Slimes;
	AGoblin* Goblins;

	void Attack();
	void DropGold();
};

