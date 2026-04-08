#include "TextRenderComponent.h"
#include "SDL_ttf.h"
#include "Engine.h"
#include "Actor.h"

UTextRenderComponent::UTextRenderComponent()
{

}

UTextRenderComponent::~UTextRenderComponent()
{
	if (Surface)
	{
		SDL_FreeSurface(Surface);

	}
	if (Texture)
	{
		SDL_DestroyTexture(Texture);
	}
}

void UTextRenderComponent::BeginPlay()
{
}

void UTextRenderComponent::Tick()
{
}

void UTextRenderComponent::Render()
{
	// 없으면 return 
	if (!GEngine->GetRenderer() || !Texture)
	{
		return;
	}

	// 창 크기 구하기
	int WindowWidth = 0;
	int WindowHeight = 0;
	SDL_GetRendererOutputSize(GEngine->GetRenderer(), &WindowWidth, &WindowHeight); // 실제 그려지는 해상도

	// 창의 중앙 구하기
	SDL_Rect Rect;
	Rect.w = MessageWidth;
	Rect.h = MessageHeight;
	Rect.x = (WindowWidth - MessageWidth) / 2;
	Rect.y = (WindowHeight - MessageHeight) / 2;

	// 그리기
	SDL_RenderCopy(GEngine->GetRenderer(), Texture, nullptr, &Rect);
	//SDL_Rect DestinationRect{ Owner->GetX(), Owner->GetY(), Surface->w, Surface->h };
	//SDL_RenderCopy(GEngine->GetRenderer(), Texture, nullptr, &DestinationRect);
}

void UTextRenderComponent::SetText(std::string InText)
{
	// 없으면 return 
	if (!GEngine->GetRenderer() || !GEngine->Font)
	{
		return;
	}
	Text = InText;
	
	// TTF -> 메모리(BMP) -> Surface
	SDL_Color TextColor = { 255, 0, 0, 255 };
	Surface = TTF_RenderText_Solid(GEngine->Font, Text.c_str(), TextColor);
	Texture = SDL_CreateTextureFromSurface(GEngine->GetRenderer(), Surface);
	MessageWidth = Surface->w;
	MessageHeight = Surface->h;
}
