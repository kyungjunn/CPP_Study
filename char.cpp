#include <iostream>
#define Length 10
using namespace std;

int main()
{
	char String[Length];

	cin >> String;

	// 문자열 갯수 세기
	for (int i = 0; i < Length; ++i)
	{
		if (String[i] == '\0')
		{
			cout << "문자열 개수는 " << i << endl;
			break;
		}
	}

	// 문자열 중에서 특정 문자를 특정문자로 바꾸기
	char FindChar;
	char ChangeChar;

	cout << "문자열 중에서 문자를 바꿀 문자를 입력" << endl;
	cin >> FindChar;

	for (int i = 0; i < Length; ++i)
	{
		if (String[i] == FindChar)
		{
			cout << "뭘로 바꿁래" << endl;
			cin >> ChangeChar;

			String[i] = ChangeChar;
			cout << String << endl;
		}
	}

	// 문자열 중에서 특정 문자 위치 찾기
	char LocationChar;

	cout << "위치를 찾을 특정 문자 입력 " << endl;
	cin >> LocationChar;

	for (int i = 0; i < Length; ++i)
	{
		if (String[i] == LocationChar)
		{
			cout << LocationChar << "의 위치는 " << i + 1 << " 번째 입니다." << endl;
		}
	}
	return 0;
}