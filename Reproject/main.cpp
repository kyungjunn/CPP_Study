#include <iostream>
#include "Engine.h"
#include "World.h"
#include <algorithm>

using namespace std;

void Sort(int* InData, int Length, int (*Compare)(int A, int B))
{
	for (int i = 0; i < Length; i++)
	{
		for (int j = 0; j < Length; j++)
		{
			if (Compare(InData[i] , InData[j]) == 1)
			{
				int Temp = InData[i];
				InData[i] = InData[j];
				InData[j] = Temp;
			}
		}
	}
}

bool bConnection = true;

int CompleteCallback()
{
	cout << "접속 완료" << endl;

	return 0;
}

void Connect(int (*Comlplete)())
{
	// callback
	if (bConnection) // 접속이 되면
	{
		Comlplete();
	}
}

int Ascending(int A, int B)
{
	if (A < B)
	{
		return 1;
	}
	else if (A == B)
	{
		return 0;
	}
	return -1;
}
int Decending(int A, int B)
{
	if (A < B)
	{
		return -1;
	}
	else if (A == B)
	{
		return 0;
	}
	return 1;
}
int main()
{
	// 네트워크 호출
	Connect(CompleteCallback);


	//GENGINE->GetInstance();
	//UEngine* MyEngine = UEngine::GetInstance();

	// 엔진을 먼저 키고 -> 월드를 받아와서 -> 맵 이름 파일로 맵을 로딩
	////GENGINE->GetWorld()->Load("level01.txt");

	// 그리고 실행
	////GENGINE->Run();
	
	// 함수 포인터
	/*int (*CompareFunction)();

	CompareFunction = Compare;

	CompareFunction();

	std::cout << Compare << CompareFunction;*/

	int Data[10] = { 9, 1, 3, 5, 4, 6, 7, 8, 2, 10 };
	// search and sort
	// selection and bubble

	// 람다 함수, 익명 함수
	int (*Compare)(int A, int B) = [](int A, int B) -> int {
		return 0;
		};

	Compare(1, 2);

	//람다 함수, 익명 함수, C++ 14 이상
	Sort(Data, 10, [](int A, int B) -> int {
		if (A < B)
		{
			return 1;
		}
		else if (A == B)
		{
			return 0;
		}

		return -1;
		}
	);


	// Sort(Data, 10, Ascending);

	for (int i = 0; i < 10; i++)
	{
		std::cout << Data[i] << " ";
	}

	return 0;
}