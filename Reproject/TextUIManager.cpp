#include "TextUIManager.h"
#include <iostream>
#include <SDL.h>

UTextUIManager::UTextUIManager(SDL_Renderer* InRenderer)
    : Renderer(InRenderer), Font(nullptr), MessageTexture(nullptr)
    , MessageWidth(0), MessageHeight(0)
{
    if (TTF_Init() == -1)
    {
        SDL_Log("TTF_Init failed: %s", TTF_GetError());
        return;
    }

    Font = TTF_OpenFont("C:\\Windows\\Fonts\\malgun.ttf", 36);
    if (!Font)
    {
        SDL_Log("TTF_OpenFont failed: %s", TTF_GetError());
    }
}

UTextUIManager::~UTextUIManager()
{
    if (MessageTexture)
    {
        SDL_DestroyTexture(MessageTexture);
        MessageTexture = nullptr;
    }

    if (Font)
    {
        TTF_CloseFont(Font);
        Font = nullptr;
    }

    TTF_Quit();
}

void UTextUIManager::ShowMessage(const std::string& InText)
{
    if (!Renderer || !Font)
    {
        return;
    }

    if (MessageTexture)
    {
        SDL_DestroyTexture(MessageTexture);
        MessageTexture = nullptr;
    }

    SDL_Color Color = { 255, 255, 255, 255 };
    SDL_Surface* Surface = TTF_RenderUTF8_Blended(Font, InText.c_str(), Color);
    if (!Surface)
    {
        SDL_Log("TTF_RenderUTF8_Blended failed: %s", TTF_GetError());
        return;
    }

    MessageTexture = SDL_CreateTextureFromSurface(Renderer, Surface);
    MessageWidth = Surface->w;
    MessageHeight = Surface->h;

    SDL_FreeSurface(Surface);
}

void UTextUIManager::Render()
{
    if (!MessageTexture || !Renderer)
    {
        return;
    }

    int WindowWidth = 0;
    int WindowHeight = 0;
    SDL_GetRendererOutputSize(Renderer, &WindowWidth, &WindowHeight);

    SDL_Rect Rect;
    Rect.w = MessageWidth;
    Rect.h = MessageHeight;
    Rect.x = (WindowWidth - MessageWidth) / 2;
    Rect.y = (WindowHeight - MessageHeight) / 2;

    SDL_RenderCopy(Renderer, MessageTexture, nullptr, &Rect);
}