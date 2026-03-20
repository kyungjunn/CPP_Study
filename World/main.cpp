#include <iostream>
#include "World.h"
#include "Engine.h"
#include "Player.h"
#include "WildPig.h"
#include "Slime.h"
#include "Goblin.h"

int main()
{
	/*UEngine* MyEngine = new UEngine();
	MyEngine->Run();
	delete MyEngine;*/
	srand((unsigned)time(nullptr));

	// 멧돼지가 1~3 ,슬라임이 무조건 3~10마리 , 고블린이 2마리까지 
	// 랜덤으로
	UWorld World;
	World.WildPigCount = rand() % 3 + 1;
	World.SlimeCount = rand() % 8 + 3;																										
	World.GoblinCount= rand() % 2 + 1;

	AWildPig* WildPig = new AWildPig[World.WildPigCount];

	ASlime* Slime = new ASlime[World.SlimeCount];

	AGoblin* Goblin = new AGoblin[World.GoblinCount];

	for (int i = 0; i < World.WildPigCount; i++)
	{
		WildPig[i].Move();
	}
	for (int i = 0; i < World.SlimeCount; i++)
	{
		Slime[i].Move();
	}
	for (int i = 0; i < World.GoblinCount; i++)
	{
		Goblin[i].Move();
	}
	return 0;
}