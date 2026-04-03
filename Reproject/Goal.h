#pragma once
#include "Actor.h"

class USpriteComponent;
class AActor;

class AGoal : public AActor
{
public:
	AGoal(int InX = 9, int InY = 9, char InMesh = 'G');
	virtual ~AGoal();

	USpriteComponent* SpriteComponent;
	class UCollisionComponent* CollisionComponent;

protected:
};

