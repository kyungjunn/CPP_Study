#pragma once
#include <string>
#include "SDL.h"
#include "SDL_ttf.h"

class UTextUIManager
{
public:
    UTextUIManager(SDL_Renderer* InRenderer);
    virtual ~UTextUIManager();

    void ShowMessage(const std::string& InText);
    void Render();

private:
    SDL_Renderer* Renderer;
    TTF_Font* Font;
    SDL_Texture* MessageTexture;
    int MessageWidth;
    int MessageHeight;
};