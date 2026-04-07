#include "GameMode.h"
#include "Engine.h"
#include "World.h"
#include "TextUIManager.h"



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

void AGameMode::EndGame(const std::string& InMessage)
{
	// 게임이 끝났으면 무시
	if (bGameEnded)
	{
		return;
	}

	bGameEnded = true;
	EndGameElapsedTime = 0.0f;

	SDL_Log("%s", InMessage.c_str());

	if (GEngine->GetTextUIManager())
	{
		GEngine->GetTextUIManager()->ShowMessage(InMessage);
	}

}
