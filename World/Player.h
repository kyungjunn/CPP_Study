#pragma once
#include "Actor.h"
class APlayer : public AActor
{
public:
	APlayer();
	~APlayer();

	void Attack();
	void Collect();
	void Die();

	int Gold;
};

