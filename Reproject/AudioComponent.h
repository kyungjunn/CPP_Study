#pragma once
#include "Component.h"
#include <string>

struct Mix_Music;

class UAudioComponent : public UComponent
{
public:
	UAudioComponent();
	virtual ~UAudioComponent();

	// pure virtual function
	virtual void BeginPlay() override;

	virtual void Tick() override;

	void Play();

	void Stop();

	void Load(std::string InFilename);

protected:
	std::string Filename;

	Mix_Music* Music;
};

