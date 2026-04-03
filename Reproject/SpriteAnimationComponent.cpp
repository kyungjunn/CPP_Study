#include "SpriteAnimationComponent.h"
#include "GameplayStatics.h"
#include "SDL.h"
#include "Actor.h"

USpriteAnimationComponent::USpriteAnimationComponent()
{
}

USpriteAnimationComponent::~USpriteAnimationComponent()
{
}

void USpriteAnimationComponent::Tick()
{
	__super::Tick();
	// 시간을 받아와 누적시킴
	ElapsedTime += UGameplayStatics::GetWorldDeltaSeconds();

	// 누적 시킨 시간이 한 프레임당 유지 시간을 넘었는지
	if (ElapsedTime >= ExecutionTime)
	{
		SpriteIndexX++; // 다음 칸 이동
		SpriteIndexX = SpriteIndexX % 5; // 인덱스가 5가 되면 0으로 초기화
		ElapsedTime = 0; // 시간도 초기화
	}
}

void USpriteAnimationComponent::Render()
{
	int TileSize = 30;
	
	// 이미지의 한 칸 크기 계산
	int SpriteWidth = Image->w / 5;
	int SpriteHeight = Image->h / 5;	
	
	// 그리기
	SDL_Rect SourceRect = { SpriteIndexX * SpriteWidth, Direction * SpriteHeight, SpriteWidth , SpriteHeight };
	SDL_Rect DestinationRect = {Owner->GetX() * TileSize, Owner->GetY() * TileSize, TileSize, TileSize };
	SDL_RenderCopy(GEngine->GetRenderer(), Texture, &SourceRect, &DestinationRect);
}
