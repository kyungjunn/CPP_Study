#pragma once
#include "Engine.h"

class UGameplayStatics
{
public:
	UGameplayStatics();
	virtual ~UGameplayStatics();

	inline static float GetWorldDeltaSeconds() 
	{
		return GEngine->GetDeltaSeconds();
	}
};

