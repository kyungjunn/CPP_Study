#include <iostream>
#include "StringUtil.h"

using namespace std;

int main()
{
	// 숫자 입력받아서 그걸 크기로 숫자 배열을 만들어서 1부터 크기까지 초기화하고 출력하는 프로그램
	int Size;
	int* Number = nullptr; // 중간에 쓰면 헷갈리니까 선언할 때 비워놓고 채워넣는 느낌으로.
	cin >> Size;

	// heap 배열을 size 크기만큼 int, 시작 번지(int*)
	Number = new int[Size];
	
	if (!Number) // if (Number == nullptr)
	{
		return -1;
	}

	for (int i = 0; i < Size; ++i)
	{
		Number[i] = i + 1;
	}

	for (int i = 0; i < Size; ++i)
	{
		cout << Number[i] << ", ";
	}
	cout << endl;


	// heap에 있는 배열 반환
	delete[] Number;
	Number = nullptr;	// 유효한 값이 아니라고 전달

	return 0;
}