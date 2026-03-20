#include <iostream>
#include "Engine.h"
#include "Player.h"


int main()
{
	APlayer* MyPlayer = new APlayer();

	MyPlayer->Move(1, 1);

	UEngine* MyEngine = new UEngine();
	MyEngine->Run();
	delete MyEngine;

	return 0;
}