#include "MyGM.h"
#include "SDL.h"
#include "World.h"
#include "Engine.h"
#include "YoudieActor.h"
#include "Component.h"
#include "RenderableComponent.h"
#include "TextRenderComponent.h"

AMyGM::AMyGM()
{
}

AMyGM::~AMyGM()
{
}

void AMyGM::GameOver()
{
	static bool bGameOver = false;

	if (!bGameOver)
	{
		AYoudieActor* TextActor = dynamic_cast<AYoudieActor*>(GEngine->GetWorld()->GetActorOfClass<AYoudieActor>());
		if (TextActor)
		{
			TextActor->TextRenderComponent->bIsVisible = true;
		}

		SDL_Log("Game Over"); // 로그
		bGameOver = true;
	}
}

void AMyGM::GameComplete()
{
	static bool bGameComplte = false;

	if (!bGameComplte)
	{
		SDL_Log("Game Complete"); // 로그
		bGameComplte = true;
	}
}