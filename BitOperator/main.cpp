#include <iostream>

using namespace std;

using uint64 = unsigned long long;

int main()
{
	uint64 X;
	int N;
	int Result = 0;

	// 개수 입력
	cin >> N;

	//int A = 1;  // 0000 0001
	//A << 1; // -> 2
	//A << 2; // -> 4
	//A << 3; // -> 8

	for (int i = 0; i < N; ++i)
	{
		// 숫자 입력
		cin >> X;

		for (int j = 0; j < 63; ++j)
		{
			uint64 NPOT = (1 << j); // -> 이게 pow 보다 더 빠름.
			if (X <= NPOT) 
			{
				// 처음에 0과 NPOT을 XOR했을 때 무조건 NPOT가 나옴
				Result = Result ^ NPOT; 
				break;
			}
		}
	}
	
	cout << Result;

	return 0;
}