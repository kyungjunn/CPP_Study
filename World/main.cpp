#include <iostream>
#include "World.h"
#include "Engine.h"
#include "Player.h"
#include "WildPig.h"
#include "Slime.h"
#include "Goblin.h"
#include <vector>

using namespace std;

int main()
{
	std::vector<AActor*> Actors;
		
	Actors.push_back(new ASlime());
	Actors.push_back(new AGoblin());
	Actors.push_back(new AWildPig());
	Actors.push_back(new APlayer());

	
	// 모든 액터 이동
	/*for (int i = 0; i < Actors.size(); ++i)
	{
		Actors[i]->Move();
	}*/

	// foreach 모든 거  auto -> 반복문에서만 사용.
	// 값 안바꾸고 복사 안하고(참조) Move만 출력하겠다. 레전드 성능\
	//for (AActor* Actor : Actors)
	for (const auto& Actor : Actors) 
	{
		Actor->Move();
	}

	// 만들었으면 지우기
	for (auto& Actor : Actors) 
	{
		delete Actor;
	}

	Actors.clear();
	return 0;
}