#include <iostream>
#include "Engine.h"
#include "World.h"
#include <fstream> // 파일 읽고 쓰기

using namespace std;

// 디자인 패턴 다른 클래스에서 재사용
// 이 싱글톤 객체가 하나만 존재하게 함.
class Singleton 
{
private:
	Singleton()
	{

	}

	static Singleton* Instance;

public:
	static Singleton* GetInstance()
	{
		if (Instance == nullptr)
		{
			Instance = new Singleton();
		}
		return Instance;					
	}
};

Singleton* Singleton::Instance = nullptr;

int main()
{

	Singleton::GetInstance();	

	/*UEngine* MyEngine = new UEngine();
	
	MyEngine->GetWorld()->Load("level01.umap");

	MyEngine->Run();

	delete MyEngine;*/
	return 0;
}