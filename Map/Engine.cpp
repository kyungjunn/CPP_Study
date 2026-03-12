#include "Engine.h"
#include <conio.h>
#include <iostream>
#include <Windows.h>

// 플레이어 위치 초기화
FVector2i PlayerPosition = { 1, 1 };

bool bIsPlaying = true;

int Map[10][10] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

int Input()
{
	// _kbhit() : 눌렀을 때 true 아니면 안나오게
	return _getch();
}
void Process(int PlayerInput)
{
	int SavePointX = PlayerPosition.X;
	int SavePointY = PlayerPosition.Y;

	// 플레이어 이동
	if (PlayerInput == 'W' || PlayerInput == 'w')
	{
		AddPlayerOffset(0, -1);

	}
	if (PlayerInput == 'S' || PlayerInput == 's')
	{
		AddPlayerOffset(0, 1);
	}
	if (PlayerInput == 'A' || PlayerInput == 'a')
	{
		AddPlayerOffset(-1, 0);
	}
	if (PlayerInput == 'D' || PlayerInput == 'd')
	{
		AddPlayerOffset(1, 0);
	}

	if (Map[PlayerPosition.Y][PlayerPosition.X] == 1)
	{
		PlayerPosition.X = SavePointX;
		PlayerPosition.Y = SavePointY;
	}

	if (PlayerPosition.X == 8 && PlayerPosition.Y == 8)
	{
		bIsPlaying = false;
	}
}

void Clear()
{
	for (int Y = 0; Y < 10; ++Y)
	{
		for (int X = 0; X < 10; ++X)
		{
			Gotoxy(X, Y);
			std::cout << " ";
		}
	}
}

void Render()
{
	Clear();

	for (int Y = 0; Y < 10; ++Y)
	{
		for (int X = 0; X < 10; ++X)
		{
			Gotoxy(X, Y);

			if (PlayerPosition.X == X && PlayerPosition.Y == Y)
			{
				std::cout << "P";
			}
			else if (Map[Y][X] == 1)
			{
				std::cout << "#";
			}
			else if (Map[Y][X] == 0)
			{
				std::cout << " ";
			}
		}
	}
}

void Gotoxy(int x, int y)
{
	COORD Pos = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void AddPlayerOffset(FVector2i DeltaPosition)
{
	PlayerPosition.X += DeltaPosition.X;
	PlayerPosition.Y += DeltaPosition.Y;
}

void AddPlayerOffset(int DeltaX, int DeltaY)
{
	PlayerPosition.X += DeltaX;
	PlayerPosition.Y += DeltaY;
}