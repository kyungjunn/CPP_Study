#include "GameMode.h"
#include "Engine.h"
#include "World.h"

AGameMode::AGameMode() : bGameEnded(false), EndGameElapsedTime(0.0f), EndGameDelay(2.0f)
{
}

AGameMode::~AGameMode()
{
}

void AGameMode::Tick()
{
	__super::Tick();	

	if (bGameEnded)
	{
		EndGameElapsedTime += GEngine->GetDeltaSeconds();

		if (EndGameElapsedTime >= EndGameDelay)
		{
			GEngine->Stop();
		}

		return;
	}
}

void AGameMode::EndGame(const std::string& InText)
{
	

}
