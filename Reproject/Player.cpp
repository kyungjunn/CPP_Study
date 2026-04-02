#include "Player.h"
#include "Engine.h"
#include "GameplayStatics.h"

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
			Direction = 2; // 위
		}
		if (Keycode == SDLK_s)
		{
			Y++;
			Direction = 3; // 아래
		}
		if (Keycode == SDLK_a)
		{
			X--;
			Direction = 0; // 왼쪽
		}
		if (Keycode == SDLK_d)
		{
			X++;
			Direction = 1; // 오른쪽
		}

		if (Keycode == SDLK_ESCAPE)
		{
			GEngine->Stop();
		}
	}

	ElapsedTime += UGameplayStatics::GetWorldDeltaSeconds();
	if (ElapsedTime >= ExecutionTime)
	{
		SpriteIndexX++;
		SpriteIndexX = SpriteIndexX % 5;
		ElapsedTime = 0;
	}
}

//void APlayer::Render()
//{
//	__super::Render();
//}


void APlayer::Load(std::string Filename)
{
	Image = SDL_LoadBMP(Filename.c_str());

	// 픽셀 포맷 - RGB 값을 빼서 그리도록.
	SDL_SetColorKey(Image, SDL_TRUE, SDL_MapRGB(Image->format, 255, 0, 255));

	Texture = SDL_CreateTextureFromSurface(GEngine->GetRenderer()
		, Image);
}

void APlayer::Render()
{
	int TileSize = 30;

	// 이미지의 한 칸 크기 계산
	int SpriteWidth = Image->w / 5;
	int SpriteHeight = Image->h / 5;	

	// 그리기
	SDL_Rect SourceRect = { SpriteIndexX * SpriteWidth, Direction * SpriteHeight, SpriteWidth , SpriteHeight };
	SDL_Rect DestinationRect = { X * TileSize, Y * TileSize, TileSize, TileSize };
	SDL_RenderCopy(GEngine->GetRenderer(), Texture, &SourceRect, &DestinationRect);

}
