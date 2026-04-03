#pragma once
#include "Component.h"

class UCollisionComponent : public UComponent
{
public:
	UCollisionComponent();
	virtual ~UCollisionComponent();

	virtual void BeginPlay() override;

	virtual void Tick() override;

	int bIsGenerateOverlap : 1;
	int bIsGenerateHit : 1;
};

