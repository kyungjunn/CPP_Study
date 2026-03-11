#include <iostream>
#include "StringUtil.h"

using namespace std;

int main()
{
	// 숫자 입력받아서 그걸 크기로 숫자 배열을 만들어서 1부터 크기까지 초기화하고 출력하는 프로그램

	int Number;
	cin >> Number;

	int* NumberArray = new int[Number];
	
	for (int i = 0; i < Number; ++i)
	{
		NumberArray[i] = i + 1;
	}

	
	if (NumberArray)
	{
		for (int i = 0; i < Number; ++i)
		{
			cout << NumberArray[i];
		}
	}

	delete[] NumberArray;
	NumberArray = nullptr;

	return 0;
}