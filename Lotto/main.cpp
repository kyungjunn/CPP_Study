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
void Shuffle(int* Balls, int* ShuffleBalls, int Size)
{
	int Temp = 0;
	int FirstIndex = 0;
	int SecondIndex = 0;

	for (int i = 0; i < 100; ++i)
	{
		FirstIndex = rand() % Size;
		SecondIndex = rand() % Size;

		Temp = ShuffleBalls[FirstIndex];
		ShuffleBalls[FirstIndex] = ShuffleBalls[SecondIndex];
		ShuffleBalls[SecondIndex] = Temp;
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
	int* ShuffleBalls = nullptr;

	Balls = new int[Size];
	ShuffleBalls = new int[Size];

	// 공초기화
	Init(Balls, ShuffleBalls, Size);

	// 공섞기
	Shuffle(Balls, ShuffleBalls, Size);

	// 공뽑기
	Output(ShuffleBalls, GoalSize);

	delete[] Balls;
	delete[] ShuffleBalls;
	Balls = nullptr;
	ShuffleBalls = nullptr;

	return 0;
}