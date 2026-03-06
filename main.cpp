#include <iostream>
#include <string>

#define CARDSIZE	52

using namespace std;

//Heart
//0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
//Spade
//13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
//Diamond
//26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
//Clover
//39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51,

// 똑같은 카드가 나오면 안됨.

int Player[CARDSIZE];
int Cards[CARDSIZE] = { 0, };
string CardType[4] = { "Heart", "Spade", "Diamond", "Clover" };

int ComputerCard[3];
int PlayerCard[3];
//PreProcess
int ComputerScore[3] = { 0, };
int PlayerScore[3] = { 0, };

int TotalComputerScore;
int TotalPlayerScore;


string DrawShape(int CardNumber)
{
	int Shape = (CardNumber % 13 + 1);

	if (Shape == 11)
	{
		return "J";
	}
	else if (Shape == 12)
	{
		return "Q";
	}
	else if (Shape == 13)
	{
		return "K";
	}
	else if (Shape == 1)
	{
		return "A";
	}

	return to_string(Shape);
}


void Init()
{
	for (int i = 0; i < CARDSIZE; ++i)
	{
		Cards[i] = i;
	}

	srand((unsigned int)time(nullptr));
}

void Shuffle()
{
	//Random(난수) 두 개 선택해서 교환(swap)
	for (int i = 0; i < CARDSIZE * 10; ++i)
	{
		int FirstIndex = rand() % CARDSIZE;
		int SecondIndex = rand() % CARDSIZE;
		int Temp = Cards[FirstIndex];

		Cards[FirstIndex] = Cards[SecondIndex];
		Cards[SecondIndex] = Temp;
	}
}

void Deal()
{
	//Deal
	//0, 1
	//2, 3
	//4, 5
	for (int i = 0; i < 3; ++i)
	{
		ComputerCard[i] = Cards[i * 2];
		PlayerCard[i] = Cards[(i * 2) + 1];
	}
}

void PreProcess()
{
	for (int i = 0; i < 3; ++i)
	{
		ComputerScore[i] = (ComputerCard[i] % 13 + 1) > 10 ? 10 : (ComputerCard[i] % 13 + 1);

		PlayerScore[i] = PlayerCard[i] % 13 + 1;

		PlayerScore[i] = PlayerScore[i] > 10 ? 10 : PlayerScore[i];
	}

	TotalComputerScore = ComputerScore[0] + ComputerScore[1] + ComputerScore[2];
	TotalPlayerScore = PlayerScore[0] + PlayerScore[1] + PlayerScore[2];
}

void Draw()
{
	//Draw
	if (TotalComputerScore > 21)
	{
		cout << "Player Win" << endl;
	}
	else if (TotalPlayerScore > 21)
	{
		cout << "Player Lose" << endl;
	}
	else if (TotalComputerScore > TotalPlayerScore)
	{
		cout << "Player Lose" << endl;
	}
	else
	{
		cout << "Player Win" << endl;
	}

	cout << "\n==========================" << endl;
	cout << "Computer Deck" << endl;
	for (int i = 0; i < 3; ++i)
	{
		int CardTypeIndex = ComputerCard[i] / 13;

		cout << CardType[CardTypeIndex] << " " << DrawShape(ComputerCard[i]) << endl;
	}
	cout << "Total : " << TotalComputerScore << endl;
	cout << "==========================\n" << endl;

	cout << "==========================" << endl;
	cout << "Player Deck" << endl;
	for (int i = 0; i < 3; ++i)
	{
		int CardTypeIndex = PlayerCard[i] / 13;

		cout << CardType[CardTypeIndex] << " " << DrawShape(PlayerCard[i]) << endl;
	}
	cout << "Total : " << TotalPlayerScore << endl;
	cout << "==========================" << endl;

}

int main() //entry point
{
	// 절차지향 프로그래밍
	Init();
	Shuffle();
	Deal();
	PreProcess();
	Draw();

	return 0;
}