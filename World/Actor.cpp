#include "Actor.h"
#include <iostream>

AActor::AActor()
{
}

AActor::~AActor()
{
}

void AActor::Move(int X, int Y)
{
	std::cout << "플레이어" << X << ", " << Y << "만큼 이동" << std::endl;
}
