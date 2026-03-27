#include "Monster.h"

AMonster::AMonster(int InX, int InY, char InMesh)
{
	X = InX;
	Y = InY;
	Mesh = InMesh;
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

}

void AMonster::Render()
{
	__super::Render();

}
