#include <iostream>

using namespace std;

// 변수 선언
int Size = 0;
int PickSize = 0;

void Init(int* Balls, int Size);
void Shuffle(int* Balls, int Size);
void Output(int* Balls, int Size, int PickSize);

int main()
{
	cin >> Size >> PickSize;

	int* Balls = nullptr;
	Balls = new int[Size];
	// 공초기화
	Init(Balls, Size);

	// 공섞기
	Shuffle(Balls, Size);

	// 공뽑기
	Output(Balls, Size, PickSize);

	if (Balls)
	{
		delete[] Balls;
		Balls = nullptr;
	}

	return 0;
}
void Init(int* Balls, int Size)
{
	for (int i = 0; i < Size; ++i)
	{
		Balls[i] = i + 1;
	}
}
void Shuffle(int* Balls, int Size)
{
	srand((unsigned int)time(NULL));

	int Temp = 0;
	int FirstIndex = 0;
	int SecondIndex = 0;

	for (int i = 0; i < Size * 10; ++i)
	{
		FirstIndex = rand() % Size;
		SecondIndex = rand() % Size;

		Temp = Balls[FirstIndex];
		Balls[FirstIndex] = Balls[SecondIndex];
		Balls[SecondIndex] = Temp;
	}
}
void Output(int* Balls, int Size, int PickSize)
{
	for (int i = 0; i < PickSize; ++i)
	{
		cout << Balls[i] << ", ";
	}
}