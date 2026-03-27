#pragma once
#include "Actor.h"
class AGoal : public AActor
{
public:
	AGoal(int InX = 9, int InY = 9, char InMesh = 'G');
	virtual ~AGoal();
};

