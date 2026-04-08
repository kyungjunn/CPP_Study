#include "AudioComponent.h"
#include "SDL_mixer.h"

UAudioComponent::UAudioComponent()
{

}
UAudioComponent::~UAudioComponent()
{
	if (Music)
	{
		Mix_FreeMusic(Music);
	}
}

void UAudioComponent::BeginPlay()
{
	Play();
}
void UAudioComponent::Tick()
{

}
void UAudioComponent::Play()
{
	Mix_PlayMusic(Music, -1);
}
void UAudioComponent::Stop()
{
	Mix_HaltMusic(); // ¡ÔΩ√ ∏ÿ√„
}
void UAudioComponent::Load(std::string InFilename)
{
	Filename = InFilename;
	Music = Mix_LoadMUS(Filename.c_str());
}