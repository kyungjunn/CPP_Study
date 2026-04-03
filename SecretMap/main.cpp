#include <iostream>
#include <vector>
#include <string>

using namespace std;

void Solution(int N, std::vector<int> Arr1, std::vector<int> Arr2)
{
	for (int i = 0; i < N; ++i)
	{
        int ArrOR = Arr1[i] | Arr2[i];
        string row = "";

        // 맨 왼쪽 비트부터 검사
        // j는 N-1부터 0까지 감소하며 각 자리의 비트를 확인
        for (int j = N - 1; j >= 0; --j)
        {
            // ArrOR의 j번째 비트가 1인지 
            if ((ArrOR >> j) & 1)
            {
                row += "#";
            }
            else
            {
                row += " ";
            }
        }
        cout << row << endl;
	}
}
int main()
{
	int N = 5;

	std::vector<int> Arr1 = { 9, 20, 28, 18, 11 };
	std::vector<int> Arr2 = { 30, 1, 21, 17, 28 };

	Solution(N, Arr1, Arr2);

	return 0;
}