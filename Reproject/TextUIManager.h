#pragma once
#include <string>
#include "SDL.h"
#include "SDL_ttf.h"

class UTextUIManager
{
public:
    UTextUIManager(SDL_Renderer* InRenderer);
    virtual ~UTextUIManager();

    void ShowMessage(const std::string& InText); // 복사 X, 읽기 전용, 
    //ShowMessage("게임종료!"); -> 이건 타입이 char*  => 이걸 string 으로 암시적 변환.
    void Render();

private:
    SDL_Renderer* Renderer;
    TTF_Font* Font;
    SDL_Texture* MessageTexture;
    int MessageWidth;
    int MessageHeight;
};