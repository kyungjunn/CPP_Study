#pragma once
#include <string>
#include <map>

struct SDL_Texture;

class UResourceManager
{
public:
	UResourceManager();
	virtual ~UResourceManager();

	SDL_Texture* LoadTexture(std::string Filename);
};

