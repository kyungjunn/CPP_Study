#pragma once
#include "Actor.h"
class USpriteComponent;

class AMonster : public AActor
{
public:
	AMonster(int InX = 4, int InY = 4, char InMesh = 'M');
	virtual ~AMonster();

	virtual void BeginPlay() override;

	virtual void Tick() override;

	USpriteComponent* SpriteComponent;

	//virtual void Render() override;	

protected:
	float ElapsedTime = 0;
	float ExecutionTime = 0.1f;
};

