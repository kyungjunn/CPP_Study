#include "Engine.h"
#include "World.h"

UEngine::UEngine()
{
	Init();
}

UEngine::~UEngine()
{
	Term();
}

void UEngine::Init()
{
	World = new UWorld();
	bIsRunning = true;
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

void UEngine::Term()
{
	delete World;
	World = nullptr;
}

void UEngine::Input()
{

}

void UEngine::Tick()
{

}

void UEngine::Render()
{

}
