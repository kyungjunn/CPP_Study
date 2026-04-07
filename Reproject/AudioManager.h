#pragma once
#include <string>
#include "SDL_mixer.h"

class UAudioManager
{
public:
    UAudioManager();
    virtual ~UAudioManager();

    void PlayBGM();

private:
    Mix_Music* BackgroundMusic;
};