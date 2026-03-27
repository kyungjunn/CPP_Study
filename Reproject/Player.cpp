#include "Player.h"
#include "Engine.h"

APlayer::APlayer(int InX, int InY, char InMesh)
{
	X = InX;
	Y = InY;
	Mesh = InMesh;
	ZOrder = 10;
}

APlayer::~APlayer()
{
}

void APlayer::BeginPlay()
{
	__super::BeginPlay();
}

void APlayer::Tick()
{
	__super::Tick();

	if (UEngine::KeyCode == 'w' || UEngine::KeyCode == 'W')
	{
		Y--;
	}
	if (UEngine::KeyCode == 's' || UEngine::KeyCode == 'S')
	{
		Y++;
	}
	if (UEngine::KeyCode == 'a' || UEngine::KeyCode == 'A')
	{
		X--;
	}
	if (UEngine::KeyCode == 'd' || UEngine::KeyCode == 'D')
	{
		X++;
	}

	UEngine::KeyCode = 0;
}

void APlayer::Render()
{
	__super::Render();
}
