#include <iostream>
#include <fstream>
#include "World.h"
#include "Actor.h"
#include "Player.h"
#include "Monster.h"
#include "Wall.h"
#include "Goal.h"
#include "Floor.h"

UWorld::UWorld()
{
}

UWorld::~UWorld()
{
	for (auto Actor : Actors)
	{
		delete Actor;
	}
	Actors.clear();
}

void UWorld::Load(std::string MapName)
{
	std::ifstream MapStream(MapName);

	// char Data;

	int Y = 0;

	while (!MapStream.eof()) // end of file
	{
		std::string Line;
		std::getline(MapStream, Line);

		for (int X = 0; X < Line.length(); ++X)
		{
			if (Line[X] == '*')
			{
				SpawnActor<AWall>()->SetActorLocation(X, Y);
			}
			else if (Line[X] == ' ')
			{
				SpawnActor<AFloor>()->SetActorLocation(X, Y);
			}
			else if (Line[X] == 'P')
			{
				SpawnActor<APlayer>()->SetActorLocation(X, Y);
			}
			else if (Line[X] == 'M')
			{
				SpawnActor<AMonster>()->SetActorLocation(X, Y);
			}
			else if (Line[X] == 'G')
			{
				SpawnActor<AGoal>()->SetActorLocation(X, Y);
			}
		}
		// MapStream.read(&Data, 1); // 한 글자씩 가져옴

		Y++;
	}

}

void UWorld::Tick()
{
	for (auto Actor : Actors)
	{
		Actor->Tick();
	}
}

void UWorld::Render()
{
	for (auto Actor : Actors)
	{
		Actor->Render();
	}
}