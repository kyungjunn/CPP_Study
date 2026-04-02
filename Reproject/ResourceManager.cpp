#include "ResourceManager.h"
#include "SDL.h"

UResourceManager::UResourceManager()
{
}

UResourceManager::~UResourceManager()
{
}
SDL_Texture* UResourceManager::LoadTexture(std::string Filename)
{
	//Image = SDL_LoadBMP(Filename.c_str());

	//// 픽셀 포맷 - RGB 값을 빼서 그리도록.
	//SDL_SetColorKey(Image, SDL_TRUE, SDL_MapRGB(Image->format, 255, 255, 255));
	////SDL_SetColorKey(Image, SDL_TRUE, SDL_MapRGB(Image->format, 255, 0, 255));

	//Texture = SDL_CreateTextureFromSurface(GEngine->GetRenderer()
	//	, Image);
	return nullptr;
}
