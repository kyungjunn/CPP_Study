#include "Player.h"
#include "Engine.h"

APlayer::APlayer(int InX, int InY, char InMesh)
{
	X = InX;
	Y = InY;
	Mesh = InMesh;
	ZOrder = 10;

	R = 255;
	G = 0;
	B = 0;

	Load("Data/player.bmp");
}

APlayer::~APlayer()
{
}

void APlayer::BeginPlay()
{
	__super::BeginPlay();
}

void APlayer::Tick()
{
	__super::Tick();

	SDL_Event Event = GEngine->GetEvent();

	if (Event.type == SDL_KEYDOWN)
	{
		SDL_Keycode Keycode = Event.key.keysym.sym;

		if (Keycode == SDLK_w)
		{
			Y--;
			// callback
			// std::function<void>
		}
		if (Keycode == SDLK_s)
		{
			Y++;
		}
		if (Keycode == SDLK_a)
		{
			X--;
		}
		if (Keycode == SDLK_d)
		{
			X++;
		}
		
		if (Keycode == SDLK_ESCAPE)
		{
			GEngine->Stop();
		}
	}
}

void APlayer::Render()
{
	__super::Render();
}

void APlayer::Load(std::string Filename)
{
	Image = SDL_LoadBMP(Filename.c_str());

	// 픽셀 포맷 - RGB 값을 빼서 그리도록.
	SDL_SetColorKey(Image, SDL_TRUE, SDL_MapRGB(Image->format, 255, 0, 255));

	Texture = SDL_CreateTextureFromSurface(GEngine->GetRenderer()
		, Image);
}
