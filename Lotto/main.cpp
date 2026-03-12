#include <iostream>

using namespace std;

void Init(int* Balls, int Size)
{
	for (int i = 0; i < Size; ++i)
	{
		Balls[i] = i + 1;
	}
}
void Shuffle(int* Balls, int Size)
{
	int Temp = 0;
	int FirstIndex = 0;
	int SecondIndex = 0;

	for (int i = 0; i < 45 * 10; ++i)
	{
		FirstIndex = rand() % Size;
		SecondIndex = rand() % Size;

		Temp = Balls[FirstIndex];
		Balls[FirstIndex] = Balls[SecondIndex];
		Balls[SecondIndex] = Temp;
	}
}
void Output(int* Balls, int GoalSize)
{
	for (int i = 0; i < GoalSize; ++i)
	{
		cout << Balls[i] << ", ";
	}
}
int main()
{
	srand(time(NULL));

	// 변수 선언
	int Size = 45;
	int GoalSize = 6;
	int* Balls = nullptr;
	
	Balls = new int[Size];

	// 공초기화
	Init(Balls, Size);

	// 공섞기
	Shuffle(Balls, Size);

	// 공뽑기
	Output(Balls, GoalSize);

	delete[] Balls;
	Balls = nullptr;

	return 0;
}