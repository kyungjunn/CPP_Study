#pragma once
#include "Actor.h"

class USpriteComponent;

class AFloor : public AActor
{
public:
	AFloor(int InX = 2, int InY = 2, char InMesh = ' ');
	virtual ~AFloor();

	USpriteComponent* SpriteComponent;
};

