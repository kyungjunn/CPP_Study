#pragma once
#include "Actor.h"

class USpriteComponent;
class UCollisionComponent;

class AWall : public AActor
{
public:
	AWall(int InX = 7, int InY = 7, char InMesh = '*');
	virtual ~AWall();

	USpriteComponent* SpriteComponent;
	UCollisionComponent* CollisionComponent;

};

