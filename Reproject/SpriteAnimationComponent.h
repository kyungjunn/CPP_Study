#pragma once
#include "SpriteComponent.h"

class USpriteAnimationComponent : public USpriteComponent
{
public:
	USpriteAnimationComponent();
	virtual ~USpriteAnimationComponent();

	virtual void Tick() override;

	virtual void Render() override;

	int SpriteIndexX = 0;
	int Direction = 0;

	float ElapsedTime = 0;
	float ExecutionTime = 0.1f;
};

