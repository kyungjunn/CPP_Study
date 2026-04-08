#include "AudioManager.h"
#include "SDL.h"
#include <iostream>

UAudioManager::UAudioManager() : BackgroundMusic(nullptr)
{
    if ((Mix_Init(MIX_INIT_MP3) & MIX_INIT_MP3) != MIX_INIT_MP3)
    {
        SDL_Log("Mix_Init failed: %s", Mix_GetError());
        return;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        SDL_Log("Mix_OpenAudio failed: %s", Mix_GetError());
        return;
    }

    BackgroundMusic = Mix_LoadMUS("Data/bgm.mp3");
    if (!BackgroundMusic)
    {
        SDL_Log("Mix_LoadMUS failed: %s", Mix_GetError());
        return;
    }
}

UAudioManager::~UAudioManager()
{
    if (BackgroundMusic)
    {
        Mix_FreeMusic(BackgroundMusic);
        BackgroundMusic = nullptr;
    }

    Mix_CloseAudio();
    Mix_Quit();
}

void UAudioManager::PlayBGM()
{
    if (BackgroundMusic)
    {
        Mix_PlayMusic(BackgroundMusic, -1); // 무한 반복
    }
}

