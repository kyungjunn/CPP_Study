#include "WildPig.h"
#include <iostream>

AWildPig::AWildPig()
{
}

AWildPig::~AWildPig()
{
}

void AWildPig::Move()
{
	std::cout << "AWildPig::";
	__super::Move();
}
