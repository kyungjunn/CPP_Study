#pragma once
#include "Character.h"

class USpriteComponent;
class AActor;

class AMonster : public ACharacter
{
public:
	AMonster(int InX = 4, int InY = 4, char InMesh = 'M');
	virtual ~AMonster();

	virtual void Tick() override;

	USpriteComponent* SpriteComponent;

protected:
	float ElapsedTime = 0;
	float ExecutionTime = 0.1f;
};

