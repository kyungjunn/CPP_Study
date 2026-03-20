#include <iostream>
#include "World.h"
#include "Player.h"


int main()
{
	APlayer* MyPlayer = new APlayer();

	MyPlayer->Move(1, 1);

	return 0;
}