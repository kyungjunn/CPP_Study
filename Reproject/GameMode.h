#pragma once
#include "Actor.h"
#include <string>

class AGameMode : public AActor
{
public:
	AGameMode();
	virtual ~AGameMode();

	virtual void Tick() override;
	
	void EndGame(const std::string& InMessage);

protected:
	bool bGameEnded;
	float EndGameElapsedTime;
	float EndGameDelay;
};

