#include "World.h"
#include "Engine.h"
#include "Actor.h"
#include "Player.h"
#include "Monster.h"
#include "Floor.h"
#include "Wall.h"
#include "Goal.h"
#include "RenderableComponent.h"
#include "SpriteComponent.h"
#include "GameMode.h"

#include <fstream> // 파일 읽고쓰는 헤더
#include <string>
#include <algorithm>

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
	Actors.push_back(new AGameMode());

	std::ifstream File(MapName); // 파일 열기

	int Y = 0;

	int MaxX = -1;
	int MaxY = -1;

	while (!File.eof()) // 파일이 끝나지 않을 때까지
	{
		std::string Line; // 한 줄씩 읽기
		std::getline(File, Line); // 파일 끝까지 한 줄씩

		for (int X = 0; X < Line.length(); ++X)
		{
			char C = Line[X];

			if (C == ' ')
			{
				SpawnActor<AFloor>()->SetActorLocation(X, Y);
			}
			else if (C == '*')
			{
				SpawnActor<AWall>()->SetActorLocation(X, Y);
				SpawnActor<AFloor>()->SetActorLocation(X, Y);
			}
			else if (C == 'P')
			{
				SpawnActor<APlayer>()->SetActorLocation(X, Y);
				SpawnActor<AFloor>()->SetActorLocation(X, Y);
			}
			else if (C == 'M')
			{
				SpawnActor<AMonster>()->SetActorLocation(X, Y);
				SpawnActor<AFloor>()->SetActorLocation(X, Y);
			}
			else if (C == 'G')
			{
				SpawnActor<AGoal>()->SetActorLocation(X, Y);
				SpawnActor<AFloor>()->SetActorLocation(X, Y);
			}

			if (MaxX < X + 1)
			{
				MaxX = X + 1;
			}
		}
		Y++;
	}

	MaxY = Y;

	SDL_SetWindowSize(GEngine->GetWindow(), (MaxX) * 30, MaxY * 30);

	//Sort(); 

	// 이게 더 빠르긴 함.
	std::sort(Actors.begin(), Actors.end(), 
		[](AActor* First, AActor* Second) -> int {

			USpriteComponent* FirstRenderComponent = nullptr;
			for (auto Component : First->Components)
			{
				FirstRenderComponent = dynamic_cast<USpriteComponent*>(Component);
				if (FirstRenderComponent)
				{
					break;
				}
			}

			if (!FirstRenderComponent)
			{
				return 0;
			}

			USpriteComponent* SecondRenderComponent = nullptr ;
			for (auto Component : Second->Components)
			{
				SecondRenderComponent = dynamic_cast<USpriteComponent*>(Component);
				if (SecondRenderComponent)
				{
					break;
				}
			}

			if (!SecondRenderComponent)
			{
				return 0;
			}

			return (FirstRenderComponent->ZOrder < SecondRenderComponent->ZOrder ? 1 : 0);
			// First->GetZOrder() < Second->GetZOrder() ? 1 : 0;
		});
}

//void UWorld::Sort()
//{
//	for (int i = 0; i < Actors.size(); i++)
//	{
//		for (int j = 0; j < Actors.size(); j++)
//		{
//			if (Actors[i]->GetZOrder() < Actors[j]->GetZOrder())
//			{
//				auto Temp = Actors[i];
//				Actors[i] = Actors[j];
//				Actors[j] = Temp;
//			}
//		}
//	}
//}

void UWorld::Tick()
{
	// 전체 액터 Tick 실행
	for (auto Actor : Actors)
	{
		Actor->Tick();
	}
}

void UWorld::Render()
{
	// system("cls");
	// 정렬 사용해서 액터의 우선순위를 줘야함.
	
	// 그리기 전에 지움
	GEngine->Clear();

	// 전체 액터 Render 실행
	for (auto Actor : Actors)
	{
		// 모든 액터중에 Render 가능한 컴포넌트가 있으면 렌더 실행
		//Actor->Render();
		for (auto Component : Actor->Components)
		{
			IRenderableComponent* RenderComponent = dynamic_cast<IRenderableComponent*>(Component);
			if (RenderComponent)
			{
				RenderComponent->Render();
			}
		}
	}

	GEngine->Flip();
}

