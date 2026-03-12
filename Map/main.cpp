#include <iostream>
#include <conio.h>
#define Max 10
using namespace std;

int Map[Max][Max] =
{
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

// 플레이어 초기 위치
int PlayerX = 1;
int PlayerY = 1;

// 플레이어 키 입력
int PlayerInput = 0;

// 맵 초기화
void Maps()
{
	// 이전 맵 지우기
	system("cls");

	for (int Y = 0; Y < Max; ++Y)
	{
		for (int X = 0; X < Max; ++X)
		{
			if (PlayerX == X && PlayerY == Y)
			{
				cout << 'P';
			}
			else if (Map[Y][X] == 1)
			{
				cout << '*';
			}
			else if (Map[Y][X] == 0)
			{
				cout << ' ';
			}
		}
		cout << '\n';
	}
}
void Input()
{
	PlayerInput = _getch();
}
void Process()
{
	int SavePointX = PlayerX;
	int SavePointY = PlayerY;

	// 플레이어 이동
	if (PlayerInput == 'W' || PlayerInput == 'w')
	{
		PlayerY--;
	}
	else if (PlayerInput == 'S' || PlayerInput == 's')
	{
		PlayerY++;
	}
	else if (PlayerInput == 'A' || PlayerInput == 'a')
	{
		PlayerX--;
	}
	else if (PlayerInput == 'D' || PlayerInput == 'd')
	{
		PlayerX++;
	}

	if (Map[PlayerY][PlayerX] == 1)
	{
		PlayerX == SavePointX;
		PlayerY == SavePointY;
	}
}
int main()
{
	
	Maps();
	
	
	while (1)
	{
		Input();
		Process();
		Maps();
	}

	return 0;
}