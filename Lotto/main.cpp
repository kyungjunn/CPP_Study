#include <iostream>

using namespace std;
void Init(int* Balls, int* SuffleBalls, int Size)
{
	for (int i = 0; i < Size; ++i)
	{
		Balls[i] = i + 1;
		SuffleBalls[i] = Balls[i];
	}
}
void Suffle(int* Balls, int* SuffleBalls, int Size)
{
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
}
void Output(int* SuffleBalls, int GoalSize)
{
	for (int i = 0; i < GoalSize; ++i)
	{
		cout << SuffleBalls[i] << ", ";
	}
}
int main()
{
	srand(time(NULL));

	// 변수 선언
	int Size = 45;
	int GoalSize = 6;
	int* Balls = nullptr;
	int* SuffleBalls = nullptr;

	Balls = new int[Size];
	SuffleBalls = new int[Size];

	// 공초기화
	Init(Balls, SuffleBalls, Size);

	// 공섞기
	Suffle(Balls, SuffleBalls, Size);

	// 공뽑기
	Output(SuffleBalls, GoalSize);

	delete[] Balls;
	delete[] SuffleBalls;
	Balls = nullptr;
	SuffleBalls = nullptr;

	return 0;
}