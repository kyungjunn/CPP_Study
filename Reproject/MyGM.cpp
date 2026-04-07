#include "MyGM.h"
#include "SDL.h"

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
		SDL_Log("Game Over"); // 로그
		EndGame("You Die ..."); // 텍스트 UI
		bGameOver = true;
	}
}

void AMyGM::GameComplete()
{
	static bool bGameComplte = false;

	if (!bGameComplte)
	{
		SDL_Log("Game Complete"); // 로그
		EndGame("Game Complete !!"); // 텍스트 UI
		bGameComplte = true;
	}
}