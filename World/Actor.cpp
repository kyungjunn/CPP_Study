#include "Actor.h"
#include <iostream>

AActor::AActor()
{
}

AActor::~AActor()
{
}

int AActor::GetX()
{
	return 0;
}

int AActor::GetY()
{
	return 0;
}

void AActor::SetY(int InY)
{
}

void AActor::Move()
{
	std::cout << "Move()" << std::endl;
}
