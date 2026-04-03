#include "Player.h"
#include "Engine.h"
#include "GameplayStatics.h"
#include "ResourceManager.h"
#include "SpriteAnimationComponent.h"

APlayer::APlayer(int InX, int InY, char InMesh)
{
	X = InX;
	Y = InY;

	SpriteAnimationComponent = CreateDefaultSubobject<USpriteAnimationComponent>("Sprite");

	Resource TempResource = GEngine->GetResourceManager()->LoadTexture("Data/player.bmp", true, 255, 0, 255);
	SpriteAnimationComponent->Image = TempResource.Image;
	SpriteAnimationComponent->Texture = TempResource.Texture;
	SpriteAnimationComponent->ZOrder = 100;
	SpriteAnimationComponent->ExecutionTime = 0.15f;

	// 리소스 파일에 저장한 텍스처가 있으면 가져오고 없으면 만들어.
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
			SpriteAnimationComponent->Direction = 2; // 위
		}
		if (Keycode == SDLK_s)
		{
			Y++;
			SpriteAnimationComponent->Direction = 3; // 아래
		}
		if (Keycode == SDLK_a)
		{
			X--;
			SpriteAnimationComponent->Direction = 0; // 왼쪽
		}
		if (Keycode == SDLK_d)
		{
			X++;
			SpriteAnimationComponent->Direction = 1; // 오른쪽
		}

		if (Keycode == SDLK_ESCAPE)
		{
			GEngine->Stop();
		}
	}

	
}