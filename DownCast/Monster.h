#pragma once
#include "Actor.h"

class AMonster : public AActor
{
public:
	AMonster(int InX = 5, int InY = 5, char InMesh = 'M');
	virtual ~AMonster();

	virtual void BeginPlay() override;

	virtual void Tick() override;

	virtual void Render() override;
};

