#include "Monster.h"
#include "GameplayStatics.h"	
#include "Engine.h"
#include "ResourceManager.h"

AMonster::AMonster(int InX, int InY, char InMesh)
{
	X = InX;
	Y = InY;
	Mesh = InMesh;
	ZOrder = 50;

	R = 255;
	G = 255;
	B = 0;

	Resource TempResource = GEngine->GetResourceManager()->LoadTexture("Data/monster.bmp", true, 255, 255, 255);
	Image = TempResource.Image;
	Texture = TempResource.Texture;
}

AMonster::~AMonster()
{
}

void AMonster::BeginPlay()
{
	__super::BeginPlay();

}

void AMonster::Tick()
{
	__super::Tick();

	ElapsedTime += UGameplayStatics::GetWorldDeltaSeconds();
	if (ElapsedTime >= ExecutionTime)
	{
		ElapsedTime = 0;

		int Direction = rand() % 5;
		if (Direction == 0)
		{
			Y--;
		}
		if (Direction == 1)
		{
			Y++;
		}
		if (Direction == 2)
		{
			X--;
		}
		if (Direction == 3)
		{
			X++;
		}
	}
}

void AMonster::Render()
{
	__super::Render();

}
