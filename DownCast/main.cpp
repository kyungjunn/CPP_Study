#include <iostream>
#include "Engine.h"
#include "World.h"
#include <fstream> // 파일 읽고 쓰기

using namespace std;

//gloabl variable, 전역 변수
int Value = 1;

class Static
{
public:
	Static()
	{
		Static::Count++;
	}

	virtual ~Static()
	{
		Static::Count--;
	}

	//예외
	//정적 변수
	static int Count;

	int Value;

	//정적 함수
	static void Display()
	{
		//		Value = 1; X
		cout << Count << endl;
	}
};

int Static::Count = 0;

int main()
{
	Static::Count++;

	Static* D = new Static();

	Static::Display();

	delete D;

	Static::Display();


	/*UEngine* MyEngine = new UEngine();
	
	MyEngine->GetWorld()->Load("level01.umap");

	MyEngine->Run();

	delete MyEngine;*/
	return 0;
}