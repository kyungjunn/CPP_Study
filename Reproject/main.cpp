#include <iostream>
#include "Engine.h"
#include "World.h"
#include <functional>

using namespace std;
																			
int SDL_main(int argc, char* argv[])
{
	GEngine->GetWorld()->Load("level01.txt");

	GEngine->Run();

	delete GEngine;

	return 0;
}