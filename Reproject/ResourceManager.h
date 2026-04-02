#pragma once
#include <string>
#include <map>
#include <SDL.h>

struct Resource
{
	SDL_Surface* Image;
	SDL_Texture* Texture;
};

class UResourceManager
{
public:
	UResourceManager();
	virtual ~UResourceManager();

	Resource& LoadTexture(std::string Filename, bool bIsColorKey = false, Uint8 R = 255, Uint8 G = 255, Uint8 B = 255);

protected:
	std::map<std::string, Resource> Resources;
};

