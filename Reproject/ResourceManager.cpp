#include "ResourceManager.h"
#include "SDL.h"
#include "Engine.h"
	
UResourceManager::UResourceManager()
{
}

UResourceManager::~UResourceManager()
{
	for (auto Iter : Resources)
	{
		if (Iter.second.Image)
		{
			SDL_FreeSurface(Iter.second.Image);
		}
		if (Iter.second.Texture)
		{
			SDL_DestroyTexture(Iter.second.Texture);
		}
	}

	Resources.clear();
}

Resource& UResourceManager::LoadTexture(std::string Filename, bool bIsColorKey, Uint8 R, Uint8 G, Uint8 B)
{
	if (Resources.find(Filename) != Resources.end())
	{
		return Resources.find(Filename)->second;
	}
	
	Resource NewResource;
	NewResource.Image = SDL_LoadBMP(Filename.c_str());

	//// 픽셀 포맷 - RGB 값을 빼서 그리도록.
	if (bIsColorKey)
	{
		SDL_SetColorKey(NewResource.Image, SDL_TRUE, SDL_MapRGB(NewResource.Image->format, R, G, B));
	}

	// 수정한 Surface로부터 Texture를 만든다.
	NewResource.Texture = SDL_CreateTextureFromSurface(GEngine->GetRenderer()
		, NewResource.Image);

	// 그 리소스를 리소스 파일에 저장한다. 
	Resources[Filename] = NewResource;

	return Resources[Filename];
}

