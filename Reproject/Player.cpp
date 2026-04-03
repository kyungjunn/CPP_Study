#include "Player.h"
#include "Engine.h"
#include "World.h"
#include "GameplayStatics.h"
#include "ResourceManager.h"
#include "SpriteAnimationComponent.h"
#include "CollisionComponent.h"
#include "Goal.h"
#include "MyGM.h"
#include "Monster.h"

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

	CollisionComponent = CreateDefaultSubobject<UCollisionComponent>("Collision");
	CollisionComponent->bIsGenerateHit = true;
	CollisionComponent->bIsGenerateOverlap = true;
	// 리소스 파일에 저장한 텍스처가 있으면 가져오고 없으면 만들어.
}

APlayer::~APlayer()
{
}

void APlayer::BeginPlay()
{
	__super::BeginPlay();

	OnActorBeginOverlap = [&](AActor* Other) -> void {
		AGoal* Goal = dynamic_cast<AGoal*>(Other);
		if (Goal)
		{
			AMyGM* GM = dynamic_cast<AMyGM*>(UGameplayStatics::GetGameMode());
			if (GM)
			{
				GM->GameComplete();
			}
		}

		AMonster* Monster = dynamic_cast<AMonster*>(Other);
		if (Monster)
		{
			AMyGM* GM = dynamic_cast<AMyGM*>(UGameplayStatics::GetGameMode());
			if (GM)
			{
				GM->GameOver();
			}
		}
	};

	//OnActorBeginOverlap = &APlayer::ProcessBeginOverlap;
}

void APlayer::Tick()
{
	__super::Tick();

	SDL_Event Event = GEngine->GetEvent();

	if (Event.type == SDL_KEYDOWN)
	{
		SDL_Keycode Keycode = Event.key.keysym.sym;

		if (Keycode == SDLK_w && PredictMove(X, Y - 1))
		{
			Y--;
			// callback
			// std::function<void>
			SpriteAnimationComponent->Direction = 2; // 위
			SpriteAnimationComponent->SpriteIndexX = 0;
		}
		if (Keycode == SDLK_s && PredictMove(X, Y + 1))
		{
			Y++;
			SpriteAnimationComponent->Direction = 3; // 아래
			SpriteAnimationComponent->SpriteIndexX = 0;
		}
		if (Keycode == SDLK_a && PredictMove(X - 1, Y))
		{
			X--;
			SpriteAnimationComponent->Direction = 0; // 왼쪽
			SpriteAnimationComponent->SpriteIndexX = 0;
		}
		if (Keycode == SDLK_d && PredictMove(X + 1, Y))
		{
			X++;
			SpriteAnimationComponent->Direction = 1; // 오른쪽
			SpriteAnimationComponent->SpriteIndexX = 0;
		}

		if (Keycode == SDLK_ESCAPE)
		{
			GEngine->Stop();
		}
	}


}
void APlayer::ReceiveHit(AActor* Other)
{

}

void APlayer::ProcessBeginOverlap(AActor* Other)
{
	SDL_Log("ProcessBeginOverlap");
}


