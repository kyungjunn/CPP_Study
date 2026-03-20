#include "Slime.h"
#include <iostream>

ASlime::ASlime()
{
}

ASlime::~ASlime()
{
}

void ASlime::Move()
{
	std::cout << "ASlime::";
	__super::Move();
}
