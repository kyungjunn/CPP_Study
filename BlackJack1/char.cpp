#include <iostream>
#define Length 10
using namespace std;

// 문자열 갯수 세기
int CountString(char* String)
{
	for (int i = 0; i < Length; ++i)
	{
		if (String[i] == '\0')
		{
			return i;
		}
	}
	return Length;
}
// 문자열 중에서 특정 문자를 특정문자로 바꾸기
void ChangeString(char* String, char FChar, char CChar)
{
	for (int i = 0; i < Length; ++i)
	{
		if (String[i] == FChar)
		{
			String[i] = CChar;
		}
	}
	cout << "변경 후 : " << String << endl;
}
// 문자열 중에서 특정 문자 위치 찾기
int LocationString(char* String, char LChar)
{
	for (int i = 0; i < Length; ++i)
	{
		if (String[i] == LChar)
		{
			return i + 1;
		}
	}
	return -1;
}
int main()
{
	char String[Length];
	char FindChar;
	char ChangeChar;
	char LocationChar;

	cin >> String;

	// 문자열 길이 출력
	cout << "문자열 길이는: " << CountString(String) << endl;

	// 특정 문자를 특정 문자로 바꾸기 출력 
	cout << "문자열 중에서 문자를 바꿀 문자를 입력" << endl;
	cin >> FindChar >> ChangeChar;

	ChangeString(String, FindChar, ChangeChar);

	// 특정 문자 위치 출력
	cout << "위치를 찾을 특정 문자 입력 " << endl;
	cin >> LocationChar;
	int Location = LocationString(String, LocationChar);

	cout << LocationChar << "의 위치는 " << Location << " 번째 입니다." << endl;
	return 0;
}