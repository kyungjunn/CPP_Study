#pragma once
#include <string>
#include <vector>
#include "Actor.h"
#include <functional>

// 반환형 없고 겹친 애 액터 전방선언
using FActorBeginOverlapSignature = std::function<void(class AActor* OtherActor)>;

//#include "SDL.h"
struct SDL_Surface;
struct SDL_Texture;

class UComponent;

class AActor
{
public:
	AActor(int InX = 0, int InY = 0, char InMesh = ' ');
	virtual ~AActor();

	virtual void BeginPlay();

	virtual void Tick();

	//virtual void Render();

	virtual void SetActorLocation(int NewX, int NewY);

	/*inline const int GetZOrder() 
	{
		return ZOrder;
	}*/

	std::vector<UComponent*> Components;

	inline int GetX() const
	{
		return X;
	}
	inline int GetY() const
	{
		return Y;
	}

	// 무슨 컴포넌트가 부딪혔을 때 호출
	FActorBeginOverlapSignature OnActorBeginOverlap;

	virtual void ReceiveHit(class AActor* Other);

protected:
	int X;
	int Y;

	template<typename T>
	T* CreateDefaultSubobject(std::string ComponentName)
	{
		T* Temp = new T;
		Temp->Owner = this;
		Components.push_back(Temp);

		return Temp;
	}
	/*int R;
	int G;
	int B;

	int ZOrder;
	char Mesh;*/

	//SDL_Surface* Image;
	//SDL_Texture* Texture;
};

