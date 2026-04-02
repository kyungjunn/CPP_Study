#pragma once
#include <string>

//#include "SDL.h"	
struct SDL_Surface;
struct SDL_Texture;

class AActor
{
public:
	AActor(int InX = 0, int InY = 0, char InMesh = ' ');
	virtual ~AActor();

	virtual void BeginPlay();

	virtual void Tick();

	virtual void Render();

	virtual void SetActorLocation(int NewX, int NewY);

	void Load(std::string Filename);

	inline const int GetZOrder() 
	{
		return ZOrder;
	}
	

protected:
	int X;
	int Y;

	int R;
	int G;
	int B;

	int ZOrder;
	char Mesh;

	SDL_Surface* Image;
	SDL_Texture* Texture;
};

