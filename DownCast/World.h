#pragma once
#include <string>
#include <vector>

class AActor;

class UWorld
{
public:
	UWorld();
	virtual ~UWorld();

	template<typename T> // T라는 임의의 타입
	AActor* SpawnActor() // 결과물로 AActor의 포인터(가리키는)를 반환하는 함수
	{	// Heap 메모리에 T 타입 객체를 생성하고 그 객체의 메모리 주소를
		// 부모 클래스인 AActor의 포인터 변수에 담음
		// -> 다형성(UpCasting)
		AActor* NewActor = new T;  
		Actors.push_back(NewActor); // 그 NewActor 포인터를 Actors 벡터 배열에 추가
		return NewActor;
	}

	void Load(std::string MapName);

	// inline -> define 처럼 이 함수는 내용이 짧으니까 
	// 함수 호출할 때 함수 있는 곳으로 점프하지말고 호출 자리에 이 코드를 
	// 그대로 복붙해줘
	inline std::vector<class AActor*>& GetActors()
	{ // & 참조를 사용해서 액터가 오천만개 있어도 배열로 직접 찍지 않고
		// 그 포인터의 주소값을 넘겨서 공유하겠다.
		return Actors;
	}

	void Tick();

	void Render();

protected:
	std::vector<class AActor*> Actors;
};

