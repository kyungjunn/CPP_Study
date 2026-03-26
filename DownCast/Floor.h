#pragma once
#include "Actor.h"
class AFloor : public AActor
{
public:
	AFloor(int InX = 5, int InY = 5, char InMesh = ' ');
	virtual ~AFloor();
};

