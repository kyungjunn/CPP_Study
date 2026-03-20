#include "Goblin.h"
#include <iostream>

AGoblin::AGoblin()
{
}

AGoblin::~AGoblin()
{
}

void AGoblin::Move()
{
	std::cout << "AGoblin::";
	__super::Move();
}

