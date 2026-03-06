#include <iostream>
#include <cstdlib>
using namespace std;

int MyCard[4];
int AICard[4];

int MySum = 0;
int AISum = 0;
int card = 0;

// 카드 뽑기
int DrawCard()
{
	int Randomcard = rand() % 10 + 1;
	return Randomcard;
}

int main()
{
	// srand() -> rand()함수를 초기화하는 함수.
	// 시간에 비례해서 숫자도 계속 초기화되도록.
	srand(time(NULL)); 

	cout << "플레이어 카드 : ";
	for (int i = 1; i <= 3; ++i)
	{
		card = DrawCard();
		MyCard[i] = card;
		MySum += card;

		cout << MyCard[i] << " ";	
	}
	cout << '\n';

	cout << "컴퓨터 카드 : ";
	for (int i = 1; i <= 3; ++i)
	{
		card = DrawCard();
		AICard[i] = card;
		AISum += card;

		cout << AICard[i] << " ";
	}
	cout << '\n';

	if (MySum > 21)
	{
		cout << "플레이어가 21 초과!! 패배..";
	}
	else if (AISum > 21)
	{
		cout << "컴퓨터가 21 초과!! 승리!!";
	}
	else if (MySum >= AISum)
	{
		cout << "플레이어가 승리!!";
	}
	else if (MySum < AISum)
	{
		cout << "플레이어가 패배..";
	}
	
	
	return 0;
}