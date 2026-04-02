#include "Goal.h"
#include "Engine.h"
#include "ResourceManager.h"

AGoal::AGoal(int InX, int InY, char InMesh)
{
	X = InX;
	Y = InY;
	Mesh = InMesh;
	ZOrder = 100;

	R = 0;
	G = 0;
	B = 255;

	Resource TempResource = GEngine->GetResourceManager()->LoadTexture("Data/goal.bmp", true, 255, 255, 255);
	Image = TempResource.Image;
	Texture = TempResource.Texture;
}

AGoal::~AGoal()
{
}
