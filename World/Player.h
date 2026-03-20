#pragma once
#include "Actor.h"
class APlayer : public AActor
{
public:
	APlayer();
	~APlayer();

	void Attack();
	void GetGold();
	void Move(int X, int Y);
};

