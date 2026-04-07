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
    SDL_DestroyTexture(MessageTexture);
    MessageTexture = nullptr;
    
    TTF_CloseFont(Font);
    Font = nullptr;

    TTF_Quit();
}

void UTextUIManager::ShowMessage(const std::string& InText)
{
    // 없으면 return 
    if (!Renderer || !Font)
    {
        return;
    }

    // 글자 -> 그림 -> 텍스처
    SDL_Color TextColor = { 255, 255, 255, 255 };
    SDL_Surface* Surface = TTF_RenderText_Blended(Font, InText.c_str(), TextColor); // c_str : SDL은 char* 만 받기에 string을 char*로 변환해야함.
    MessageTexture = SDL_CreateTextureFromSurface(Renderer, Surface);
    MessageWidth = Surface->w;
    MessageHeight = Surface->h;

    SDL_FreeSurface(Surface); // Surface 는 해제
}

void UTextUIManager::Render()
{
    // 없으면 return 
    if (!MessageTexture || !Renderer)
    {
        return;
    }

    // 창 크기 구하기
    int WindowWidth = 0;
    int WindowHeight = 0;
    SDL_GetRendererOutputSize(Renderer, &WindowWidth, &WindowHeight); // 실제 그려지는 해상도

    // 창의 중앙 구하기
    SDL_Rect Rect;
    Rect.w = MessageWidth;
    Rect.h = MessageHeight;
    Rect.x = (WindowWidth - MessageWidth) / 2;
    Rect.y = (WindowHeight - MessageHeight) / 2;

    // 그리기
    SDL_RenderCopy(Renderer, MessageTexture, nullptr, &Rect);
}