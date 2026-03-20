#include "Player.h"
#include <iostream>

APlayer::APlayer()
{
}

APlayer::~APlayer()
{
}

void APlayer::Attack()
{
}

void APlayer::GetGold()
{
}

void APlayer::Move(int X, int Y)
{
	std::cout << "플레이어" << X << ", " << Y << "만큼 이동" << std::endl;
}
