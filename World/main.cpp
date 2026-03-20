#include <iostream>
#include "World.h"
#include "Engine.h"
#include "Player.h"
#include "WildPig.h"
#include "Slime.h"
#include "Goblin.h"

#define SAFE_DELETES(Object)		if(Object) { delete[] Object; } // 매크로 함수

#define MAX(A, B)		(A > B ? A : B) // 값만 가져올 때

int main()
{
	/*UEngine* MyEngine = new UEngine();
	MyEngine->Run();
	delete MyEngine;*/
	srand((unsigned)time(nullptr));

	// 멧돼지가 1~3 ,슬라임이 무조건 3~10마리 , 고블린이 2마리까지 
	// 랜덤으로
	UWorld World;
	World.WildPigCount = rand() % 3; // << 이놈은 0일 때는 만들면 안되니까 예외처리
	World.SlimeCount = rand() % 8 + 3;																										
	World.GoblinCount= rand() % 2 + 1;

	AWildPig* WildPigs = nullptr; 
	if (World.WildPigCount > 0)
	{
		WildPigs= new AWildPig[World.WildPigCount];
	}

	ASlime* Slimes = new ASlime[World.SlimeCount];

	AGoblin* Goblins = new AGoblin[World.GoblinCount];

	for (int i = 0; i < World.WildPigCount; i++)
	{
		WildPigs[i].Move();
	}
	for (int i = 0; i < World.SlimeCount; i++)
	{
		Slimes[i].Move();
	}
	for (int i = 0; i < World.GoblinCount; i++)
	{
		Goblins[i].Move();
	}

	SAFE_DELETES(WildPigs);

	delete[] Slimes;
	Slimes = nullptr;
																	
	delete[] Goblins;
	Goblins = nullptr;

	return 0;
}