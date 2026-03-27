#include "Engine.h"
#include "World.h"
#include <conio.h>

UEngine* UEngine::Instance = nullptr;

int UEngine::KeyCode = 0;

UEngine::UEngine()
{
	Init();
}

UEngine::~UEngine()
{
}

void UEngine::Init()
{
	bool bIsRunning = true;

	World = new UWorld();
}

void UEngine::Term()
{
	delete World;
	World = nullptr;
}

void UEngine::Run()
{
	while (bIsRunning)
	{
		Input();
		Tick();
		Render();
	}
}

void UEngine::Input()
{
	KeyCode = _getch();
}

void UEngine::Tick()
{
	World->Tick();
}

void UEngine::Render()
{
	World->Render();
}
