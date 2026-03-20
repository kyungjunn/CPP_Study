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

void APlayer::Collect()
{
}


void APlayer::Die()
{
}

void APlayer::Move()
{
	std::cout << "APlayer::";

	__super::Move();			
}
