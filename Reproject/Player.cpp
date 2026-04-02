#include "Player.h"
#include "Engine.h"
#include "GameplayStatics.h"
#include "ResourceManager.h"

APlayer::APlayer(int InX, int InY, char InMesh)
{
	X = InX;
	Y = InY;
	Mesh = InMesh;
	ZOrder = 10;

	R = 255;
	G = 0;
	B = 0;

	// 리소스 파일에 저장한 텍스처가 있으면 가져오고 없으면 만들어.
	Resource TempResource = GEngine->GetResourceManager()->LoadTexture("Data/player.bmp", true, 255, 0, 255);
	Image = TempResource.Image;
	Texture = TempResource.Texture;
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

//void APlayer::Render()
//{
//	__super::Render();
//}

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
