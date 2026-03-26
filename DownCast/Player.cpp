#include "Player.h"
#include <iostream>

APlayer::APlayer(int InX, int InY, char InMesh) 
{
	X = InX;
	Y = InY;
	Mesh = InMesh;
}

APlayer::~APlayer()
{
}

void APlayer::BeginPlay()
{
	__super::Render();

}

void APlayer::Tick()
{
	__super::Render();

}

void APlayer::Render()
{
	__super::Render();
}