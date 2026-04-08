#pragma once
#include "Actor.h"

class UAudioComponent;

class ABGActor : public AActor
{
public:
	ABGActor();
	virtual ~ABGActor();

	virtual void BeginPlay() override;
	UAudioComponent* Audio;
};

