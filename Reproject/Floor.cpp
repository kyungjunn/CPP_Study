#include "Floor.h"
#include "Engine.h"
#include "ResourceManager.h"
AFloor::AFloor(int InX, int InY, char InMesh)
{
	X = InX;
	Y = InY;
	Mesh = InMesh;
	ZOrder = 0;

	R = 0;
	G = 0;
	B = 0;

	Resource TempResource = GEngine->GetResourceManager()->LoadTexture("Data/floor.bmp");
	Image = TempResource.Image;
	Texture = TempResource.Texture;
}

AFloor::~AFloor()
{
}
