#include <iostream>

using namespace std;

int main()
{
	srand(time(NULL));
	int Size = 45;
	int GoalSize = 6;
	int* Balls = nullptr;
	int* SuffleBalls = nullptr;

	Balls = new int[Size];
	SuffleBalls = new int[Size];

	// 공초기화
	for (int i = 0; i < Size; ++i)
	{
		Balls[i] = i + 1;
		SuffleBalls[i] = Balls[i];
	}

	// 공섞기
	int Temp = 0;
	int FirstIndex = 0;
	int SecondIndex = 0;

	for (int i = 0; i < 100; ++i)
	{
		FirstIndex = rand() % Size;
		SecondIndex = rand() % Size;

		Temp = SuffleBalls[FirstIndex];
		SuffleBalls[FirstIndex] = SuffleBalls[SecondIndex];
		SuffleBalls[SecondIndex] = Temp;
	}

	// 공뽑기
	for (int i = 0; i < GoalSize; ++i)
	{
		cout << SuffleBalls[i] << ", ";
	}

	delete[] Balls;
	delete[] SuffleBalls;
	Balls = nullptr;
	SuffleBalls = nullptr;

	return 0;
}