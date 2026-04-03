#pragma once
#include <vector>
#include <string>

class AGameMode;
class AActor;

class UWorld
{
public:
	UWorld();
	virtual ~UWorld();

	void SetGameMode(AGameMode* NewGameMode);

	template<typename T> // T라는 임의의 자료형
	AActor* SpawnActor() // AActor를 가리키는 스폰 함수
	{
		AActor* NewActor = new T; // AActor를 가리키는 새로운 T 자료형 액터(Heap)
		Actors.push_back(NewActor); // Actors 라는 벡터 배열에 추가
		return NewActor;

	}

	template<typename T>
	AActor* GetActorOfClass()
	{
		for (auto Actor : Actors)
		{
			T* Target = dynamic_cast<T*>(Actor);
			if (Target)
			{
				return Target;
			}
		}

		return nullptr;
	}

	void Load(std::string MapName);

	inline std::vector<class AActor*>& GetActors() // &로 갯수가 늘어나도 빠르게
	{
		return Actors;
	}
	
	void BeginPlay();

	void Tick();

	void Render();
protected:
	std::vector<class AActor*> Actors; 

	void Sort();
};

